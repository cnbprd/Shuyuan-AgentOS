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

## 产品选择（2026-11-27 已实证）

- `qemu-loongarch64-linux-min`：最小虚拟机镜像（`vendor/ohemu`），**先在其上验证五层 SA 软件逻辑贯通**。
- `ls3a5000@loongson`：3A5000/3A6000 7A 系列主板 PC 镜像（`vendor/loongson`，`product_name=ls3a5000`），硬件调试阶段使用。
- **不存在 `loongpc` 产品**，公开仓也没有 3A6000 独立板级目录。

## 构建环境位置

WSL 发行版、安装包与虚拟磁盘统一放在项目内 `wsl/`（`F:\ShuyuanAgent OS\wsl`），已加入 `.gitignore`，不入库：

```
wsl/
├── dl/                     # wsl_update_x64.msi、ubuntu-base-22.04-amd64.tar.gz
├── Ubuntu-22.04/           # 导入后的发行版，ext4.vhdx 在此
├── bootstrap.sh            # 发行版内依赖安装（阿里云源）
├── setup-wsl.ps1           # 启用 WSL/虚拟机平台并装内核的提权脚本
└── after-reboot.ps1        # 重启后一键：导入发行版 + 装依赖 + repo init
```

重启后执行（普通权限）：

```powershell
powershell -ExecutionPolicy Bypass -File "F:\ShuyuanAgent OS\wsl\after-reboot.ps1"
```

导入命令（管理员启用功能并重启后执行）：

```powershell
wsl --import Ubuntu-22.04 "F:\ShuyuanAgent OS\wsl\Ubuntu-22.04" "F:\ShuyuanAgent OS\wsl\dl\ubuntu-base-22.04-amd64.tar.gz" --version 2
```

> `repo init` 务必带 `--repo-url=https://gitee.com/oschina/repo.git --repo-rev=main`：默认会去 `gerrit.googlesource.com` 拉 repo 自身源码，国内网络实测 504。脚本已内置该参数。

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
