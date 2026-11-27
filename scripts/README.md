# 阶段零环境脚本说明

本目录脚本用于在 **Ubuntu 22.04 / WSL2** 宿主上准备编译环境、同步源码并触发编译。
当前项目骨架位于 Windows 目录 `F:\ShuyuanAgent OS`，脚本仅产出命令与流程，
真正的 OpenHarmony 源码树与编译必须在 Linux 环境完成。

## 执行顺序

| 步骤 | 脚本 | 作用 | 前置条件 |
| :--- | :--- | :--- | :--- |
| 1 | `00-prepare-env.sh` | 安装编译基础依赖、git-lfs | 有 sudo 权限 |
| 2 | `01-sync-source.sh [目录]` | repo 同步 `loongarch.xml` 源码、拉 LFS、下载预编译 | 已完成步骤 1 |
| 3 | `02-build.sh [产品] [目标]` | 编译整包或指定部件 | 已完成步骤 2 |

示例（WSL2 内）：

```bash
chmod +x scripts/*.sh
./scripts/00-prepare-env.sh
./scripts/01-sync-source.sh ~/openharmony_loongarch
cd ~/openharmony_loongarch
./scripts/02-build.sh qemu-loongarch64-linux-min
```

## 产品选择

- `qemu-loongarch64-linux-min`：最小虚拟机镜像，**先在其上验证五层 SA 软件逻辑贯通**。
- `ls3a5000@loongson`：3A5000/3A6000 7A 系列主板 PC 镜像，硬件调试阶段使用。

## 待核实项（与 07 手册第 7 节一致）

以下内容脚本未写死，进入真实源码树后逐项核对：

1. 宿主编译依赖的完整清单与版本（含 OpenJDK 版本、Python 版本）。
2. `hb` 构建工具的独立安装方式与命令名。
3. 预编译二进制下载脚本是否存在、参数是否变化。
4. 产品配置中 `subsystems` / 部件登记的实际字段写法。
5. 板级目录与产品名是否随移植分支更新。

## 红线提醒

- 本阶段只做环境与编译链路，**不在脚本内加入任何模型调用、Prompt 拼接或推理逻辑**。
- 开发初期建议先将 SELinux 置为 permissive 跑通全链路，再补自定义域规则切回 enforcing（见 07 手册 SELinux 三类授权）。
