# 枢元 SELinux 策略骨架

> 定位：这是**待进树填充的骨架**，不是可直接编入 `system/sepolicy` 的成品。
> 原因：OHOS 的宏名（`init_daemon_domain` 一类）、属性名（如传言的 `sa_service_attr`）与 `service_contexts` 的真实格式，均需以目标源码树原文为准；仓库侧无源码树，无法离线验证，故所有宏调用一律留作 TODO，不凭空写死。

## 1. 为什么必须有这一层

`Publish(this)` 返回 `true` 不代表 SA 真的可用。三处缺失都会造成「注册看起来成功、跨进程拿不到」：

| 缺失项 | 后果 | 表现 |
| :--- | :--- | :--- |
| `service_contexts` 无 9901 映射 | 落到 `u:object_r:default_service:s0`，被 neverallow 禁止 | `hidumper -s 9901` 空、`GetSystemAbility(9901)` 返回空，hilog 无异常 |
| `cfg` 的 `secon` 与 `type.te` 的 type 不同名 | 进程无合法域 | `init` 拉起失败，日志只报启动失败，不指向 SELinux |
| 服务标签不携带 SA 访问属性 | 即使映射存在，跨进程 IPC 授权仍被拒 | 客户端 `SendRequest` 返回错误码，`avc: denied` 指向 binder |

## 2. 落地位置（进树时按实际版本选一处）

- 平台公共策略：`system/sepolicy/public/`（域声明）、`system/sepolicy/public/service_contexts`
- 产品/厂商策略：`vendor/<厂商>/<产品>/sepolicy/`（自有域的域声明与上下文）

规则的归属以 sample SA 的策略放置方式为准；**不要**把自定义域写进 `system/sepolicy/private/`。

## 3. 本目录文件

| 文件 | 内容 | 状态 |
| :--- | :--- | :--- |
| `service_contexts` | 9901–9905 的标签映射草稿 | 键格式待核对 |
| `file_contexts` | 库与 profile 的文件标签草稿 | 类型声明待补 |
| `te/<层>_service.te` | 五个域的 type 声明 + 待补授权清单 | 宏调用待填充 |

## 4. 开发期策略：先 permissive

1. 进树后先只声明五个 `type`，不加任何 allow，直接编进镜像；
2. 把五个域置 permissive（写法以源码树 `permissive` / `permissive_or_unconfined` 宏为准）；
3. 启动后抓全量拒绝：

```sh
dmesg | grep "avc: denied"
hilog | grep -i "avc"
```

4. 按 `avc: denied { perm } for scontext=... tcontext=... tclass=...` 逐条补 `allow`，补完一条复测一次；
5. 全链路（`shuyuan_demo_client` 八步）跑通后再切 enforcing。

第一次启动不追求 enforcing——enforcing 下缺一条规则就是静默失败，排查成本远高于逐条补。

## 5. 首次启动只验三件事

```sh
ls /system/profile/ | grep 9901          # profile 进了镜像
hilog | grep -i "lingtai.*Publish"       # Publish 有明确结果
hidumper -s 9901                         # samgr 真能拿到 SA
```

三条同时通过，才说明「存在性」成立；任一失败先去查 SELinux 与配置，不要调业务接口。

## 6. 未核实项（禁止当事实用）

- `sa_service_attr` 这一属性名：公开检索无佐证，需在 `system/sepolicy/public/attributes` 原文确认；
- `service_contexts` 是否以数字 SA ID 为键：需对照目标版本 samgr 相关策略；
- 服务对象标签是否复用进程域 type，还是需独立的 `<层>_service_service` 类型：以 sample 为准。
