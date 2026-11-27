# 12 · QEMU 验证线（开发板未到货阶段）

> 目标：把灵台 9901 从「文档样板」推进到「在 `qemu-loongarch64-linux-min` 里被 `samgr` 注册、`hidumper` 可查、IPC 能往返」。
> 边界：真机 SELinux enforcing、性能基线、LASX / GPU / DRM、长时间稳定性，全部留到板子到货后的 B 线，不在本阶段下结论。

## 1. 对上传草案的五处修正（均已实证）

| # | 草案写法 | 实际 | 后果 |
| :--- | :--- | :--- | :--- |
| 1 | `repo init -u https://gitee.com/openharmony/manifest.git -b master -m loongarch.xml` | `loongarch.xml` 在 `openharmony-loongarch/manifest` 的 `ohos-main` 分支；`openharmony/manifest` 的 master 下该文件 **404** | 阶段 1 直接失败，白等一两天 |
| 2 | `wsl --import ... F:\WSL\...` | 环境已迁到项目内 `F:\ShuyuanAgent OS\wsl` | 路径不存在，导入失败 |
| 3 | 阶段 3 失败「优先查 SELinux」；阶段 5 做 permissive 调试 | `build/config/BUILDCONFIG.gn:194-197` 未声明即 `build_selinux=false`；`qemu_loongarch64_linux_min/config.json` 未声明，且 `subsystems` 里**没有 `selinux_adapter`** | QEMU 镜像根本没有策略：`hidumper` 失败不能归因 SELinux；阶段 5 的 permissive 也无从执行 |
| 4 | 阶段 2 只做 8 项代码/配置核对 | 还缺**产品登记**：qemu 产品 `subsystems` 现有 13 项，无 `shuyuan` | 部件不进编译/安装，产物不会出现在镜像 |
| 5 | 期望 `liblingtai.z.so`、`/system/profile/9901.xml`（cfg 却写 `<进程名>.xml`） | 目标是 `liblingtai_service.z.so`；profile 安装保持源文件名 `990X.xml`（`sa_profile.gni` 按 basename 归档） | 核对判据写错会误判；cfg 路径错会让 `init` 找不到 profile |

## 2. 时间线（约 6–10 个工作日，从重启后起算）

| 阶段 | 时间 | 目标 | 通过标准 |
| :--- | :--- | :--- | :--- |
| 0. 环境收尾 | 0.5–1 天 | WSL 导入、bootstrap | `wsl --version`、`repo --version`、`ccache -s`、`java -version` 正常 |
| 1. 拉源码树 | 1–2 天 | repo init/sync 走 Gitee | `vendor/ohemu/qemu_loongarch64_linux_min/` 存在；`device/board/loongson/ls3a5000/` 存在 |
| 2. 9901 进树 + 登记 + 编译 | 2–4 天 | 灵台挂到 `foundation/shuyuan/lingtai`，产品补登，逐项核对 | GN 解析通过并进链接；三个产物真实存在 |
| 3. QEMU 启动 + 存在性 | 1–2 天 | 镜像启动、`hdc tconn`、三验 | profile 在、`Publish` 成功、`hidumper -s 9901` 有返回 |
| 4. IPC 与并发 | 2–3 天 | `RegisterAgent`/`SubmitIntent`/`GetTaskStatus` 往返 | IPC 成功；锁覆盖有明确结论 |
| 5. 静态收口 | 0.5–1 天 | 策略草案整理、文档标注两类结论 | 手册明确「QEMU 已验证 / 真机待验证」 |

> SELinux 实测**不在本阶段**：要么等板子，要么另开一轮把 qemu 产品 `build_selinux` 置 `true` 并补 `selinux_adapter` 组件后重编。

## 3. 阶段 0：环境收尾

```powershell
wsl --status
wsl --import Ubuntu-22.04 "F:\ShuyuanAgent OS\wsl\Ubuntu-22.04" "F:\ShuyuanAgent OS\wsl\dl\ubuntu-base-22.04-amd64.tar.gz" --version 2
wsl --shutdown
wsl -d Ubuntu-22.04 -u root -- bash "/mnt/f/ShuyuanAgent OS/wsl/bootstrap.sh"
```

`wsl --update` 在本机不可靠：Store / GitHub 链路受阻，内核已用 `wsl_update_x64.msi` 离线装好，不必再走更新。

## 4. 阶段 1：拉源码树

```bash
mkdir -p /root/oh && cd /root/oh
repo init -u https://gitee.com/openharmony-loongarch/manifest.git \
    -b ohos-main -m loongarch.xml --no-repo-verify \
    --repo-url=https://gitee.com/oschina/repo.git --repo-rev=main
repo sync -c -j4
```

不要把 `-u` 换成 `openharmony/manifest`：那份清单里没有 `loongarch.xml`。网络不稳时分批 sync，但优先保证 `vendor/ohemu`、`device/board/loongson`、`build`、`base/security` 到位。

## 5. 阶段 2：进树、登记、编译

1. 复制 `src/foundation/shuyuan/lingtai/` 到源码树 `foundation/shuyuan/lingtai/`（先只放 9901）。
2. **产品登记**（缺这步产物不进镜像）：在 `vendor/ohemu/qemu_loongarch64_linux_min/config.json` 的 `subsystems` 里补：

```json
{
  "subsystem": "shuyuan",
  "components": [
    { "component": "lingtai", "features": [] }
  ]
},
```

3. 核对项（在草案 8 项基础上补 4 项）：

| # | 核对项 | 判据 |
| :--- | :--- | :--- |
| 1 | GN target 名与 `bundle.json` `sub_component` 逐字符一致 | 不一致 GN 阶段失败 |
| 2 | 每个 GN 目标有 `part_name` | 缺失可能不报错但产物被丢弃 |
| 3 | `ohos_sa_profile` 的 `sources` + `part_name` 齐全 | 缺一不可 |
| 4 | `ReadString/WriteString` 在当前树可用 | 查头文件与 sample |
| 5 | `OnDump` 签名与基类匹配 | 查 `system_ability.h` |
| 6 | 属性写入 API 与版本一致 | 查 sample |
| 7 | **profile 安装名** | 镜像内是 `9901.xml`，cfg/rc 必须指向它 |
| 8 | `cfg` 的 `secon` 与 `.te` 进程域 type 一致 | 不一致启动被拦 |
| 9 | **`part_name` 与产品登记的 component 名一致** | `lingtai` 对 `lingtai`；`init/` 与 `demo_client/` 当前写 `shuyuan`，无对应 component，首轮不编这两个目标 |
| 10 | **`init/` 子系统 cfg 与客户端先不进首轮镜像** | 首轮只验 9901，避免多一个未登记 part 干扰 |
| 11 | **产物名** | `liblingtai_service.z.so`，不是 `liblingtai.z.so` |
| 12 | **`bundle.json` 的 `inner_kits` 指向部件根目标** | 指向 `//foundation/shuyuan/lingtai:lingtai_interfaces` |

4. 编译：

```bash
./build.sh --product-name qemu-loongarch64-linux-min --ccache --no-prebuilt-sdk
```

`--no-prebuilt-sdk` 在 `build_scripts/build.sh:214` 有定义，可用。

**判据**（不以「无报错」为准，必须看到文件）：

- `out/.../system/lib64/liblingtai_service.z.so`
- `out/.../system/profile/9901.xml`
- `out/.../system/etc/init/lingtai_service.cfg`

## 6. 阶段 3：QEMU 启动 + 三验

用 `vendor_ohemu` 的 `qemu_run.sh` 起镜像，`hdc tconn <IP>:<PORT>` 连接。按序验，前一条不过不进下一条：

1. `ls /system/profile/ | grep 9901`
2. `hilog | grep -i "lingtai.*Publish"`
3. `hidumper -s 9901`

第 3 条失败时：**先查 profile 路径与 SA ID 一致性，不要查 SELinux**——该产品 `build_selinux=false`，镜像无策略。若三条全过，再进 IPC。

## 7. 阶段 4：IPC 与并发

- 客户端经 `hdc shell` 跑：`RegisterAgent` → `SubmitIntent` → `GetTaskStatus`，确认 Stub 分发与返回值。
- 服务侧注册表/任务表全部读写路径同锁；`OnStart` 不做耗时操作。
- `GetSystemAbility(9901)` 与 `iface_cast` 结果逐处判空。

## 8. 阶段 5：静态收口

- 策略只做**静态**整理：`src/foundation/shuyuan/sepolicy/` 已按上游模板写好（`sadomain` 进程域 + `sa_<层>` 标签 + 数字映射）；不宣称「已验证」。
- 手册区分「QEMU 已验证」与「真机/二轮待验证」。
- 记录 12 项核对结果与三个产物路径。

## 9. 不做的事

- **不复制 9901 去生成 9902–9905**：9901 未编译通过、未在 samgr 注册前，复制只会放大同一批隐患。
- 不在 QEMU 阶段下 SELinux enforcing 结论。
- 不把 `init/` 与 `demo_client/` 塞进首轮镜像（part 未登记）。

## 10. 边界

QEMU 能验：SA 注册、IPC 序列化/分发、配置一致性、启动时序逻辑。
QEMU 不能验：3A6000 性能、LASX、GPU/DRM、龙芯 SELinux enforcing、长时间稳定性。
