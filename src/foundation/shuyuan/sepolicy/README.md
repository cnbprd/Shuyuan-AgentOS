# 枢元 SELinux 策略骨架

> 依据：`security_selinux` 仓库（OpenHarmony 主干）实证，2026-11-27 逐行核对。
> 本目录可作 vendor policy 模板，但**类型名、放置位置、客户端域名仍需进树核对**。

## 1. 实证到的关键规则

| 事实 | 出处 |
| :--- | :--- |
| `sa_service_attr` 属性存在 | `sepolicy/base/public/attributes:82` |
| `sadomain` 属性存在 | `sepolicy/base/public/attributes:108` |
| 无 `sa_service_attr` 的服务不得进入 samgr | `domain.te:160` `neverallow * ~sa_service_attr:samgr_class ~list;` |
| `default_service` 被彻底禁止 | `domain.te:171` `neverallow domain default_service:samgr_class *;` |
| 进程域写法 | `type.te:49` `type hidumper_service, sadomain, domain;` |
| 服务标签写法 | `service.te:220` `type sa_dfx_sys_hidumper_ability, sa_service_attr;` |
| 映射写法（数字 SA ID） | `service_contexts` `1215 u:object_r:sa_dfx_sys_hidumper_ability:s0` |
| init 以 secon 拉起 | `init.te:123` `allow init accesstoken_service:process { rlimitinh siginh transition };` |
| `sadomain` 自带能力 | `sadomain.te`：`samain_exec` 的 entrypoint/execute、`samgr:binder { call transfer }`、`system_profile_file` 读 |

三点结论：

1. **进程域**必须 `type <层>_service, sadomain, domain;`——只写 `domain` 会被 `neverallow` 挡在 SAMGR 之外。
2. **服务标签**是**另一个** type，带 `sa_service_attr`（命名惯例 `sa_<名字>`）；`service_contexts` 指向它，而不是进程域。
3. **init 拉起**要显式 `allow init <层>_service:process { rlimitinh siginh transition }`；`sa_main` 作为 entrypoint 的 execute 权限由 `sadomain` 与 `.te` 共同覆盖。

## 2. 本目录文件

| 文件 | 作用 |
| :--- | :--- |
| `service_contexts` | 9901–9905 → `sa_<层>` 映射 |
| `te/<层>_service.te` | 进程域、服务标签、init 转换、samgr 注册、测试客户端访问 |

**不再提供 `file_contexts`**：基础策略已覆盖本项目所需路径——`sepolicy/base/system/file_contexts` 把 `/system/lib64(/.*)?` 标为 `system_lib_file`、`/system/profile(/.*)?` 标为 `system_profile_file`，`sadomain` 已有读权限。此前草稿里自造的 `<层>_service_file` 类型是错的，已删除。

## 3. 关键前提：当前产品根本不构建 SELinux

`build/config/BUILDCONFIG.gn:194-197`：

```
if (defined(product_build_config.build_selinux)) {
  build_selinux = product_build_config.build_selinux
} else {
  build_selinux = false
}
```

即**未显式声明就是 false**。实测：`ls3a5000` 写死 `false`，`qemu-loongarch64-linux-min` 未声明（等价 false）。

由此推出两条：

- QEMU 首启如果 `hidumper -s 9901` 为空，**先不要怀疑 SELinux**——镜像里没有策略；
- 要验证本目录的策略，必须把产品 `config.json` 的 `build_selinux` 置 `true`，并确认 `selinux_adapter` 部件仍在 subsystems 中。验证 SELinux 是**第二轮**上机，不是首轮。

## 4. 落地位置

- 平台公共策略（type 声明）：`system/sepolicy` 对应的 `public/` 目录；
- 自有域与映射：产品/厂商策略目录（`vendor/<厂商>/<产品>/sepolicy/`），随产品 `config.json` 的策略构建开关生效。

## 5. 验证顺序

1. 首轮：`build_selinux=false`，只验「进程起得来、SA 能注册、IPC 通」——此时无策略拦截；
2. 第二轮：`build_selinux=true`，重编镜像；
3. 若启动失败，先看 `dmesg | grep avc` 与 `hilog | grep -i avc`，按 `scontext/tcontext/tclass` 逐条补；
4. 开发期可先给五个域加 permissive，跑通后切 enforcing；
5. 首轮三验仍是：`ls /system/profile/ | grep 990X`、`hilog | grep -i "Publish"`、`hidumper -s 990X`。

## 6. 尚未核实

- `sa_<层>` 这类服务标签能否定义在 vendor 策略（部分版本对 `sa_service_attr` 的声明位置有限制）；
- 测试客户端跑在 `sh` 域这一假设（`demo_client` 由 hdc shell 启动时成立，装成独立可执行则需自己的域）；
- 9901–9905 是否落在厂商 SA ID 保留段、与目标版本原生服务是否撞号（需在源码树 `sa_profile` 全量比对）。
