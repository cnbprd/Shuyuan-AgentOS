# 变更记录

格式参考 Keep a Changelog，版本遵循 SemVer；预发布阶段用 `-dev` 后缀。日期为北京时间。

## [Unreleased]

### 变更

- 工程命名空间统一为 `shuyuan`：源码目录、C++ 命名空间、接口描述符、日志标签、参数前缀、`bundle.json` 的 `subsystem`、`destPath`、`inner_kits` 与 init/客户端目标全部同步；中文名保持「枢元智能体操作系统」，英文名保持「Shuyuan AgentOS」。

### 修复

- 五层 SA profile 由 XML 改为 JSON（`990X.json`），同步 cfg/rc、`sa_profile/BUILD.gn`、接口注释与 03/07/10/12 文档。
- 五层 `bundle.json` 的 `inner_kits` 由字符串改为带 `header`/`name` 的对象；`*_interfaces` 改为带 Proxy 实现与 `public_configs` 的共享库。
- Proxy 头与实现从 `services/` 移到 `interfaces/innerkits/`，客户端显式包含 Proxy 头并链接 `*_interfaces`，修复 `iface_cast` 无 creator 的根因。
- 五层 `OnStop` 补 `ready_ = false`；灵台增加 `UpdateTaskStatus`，令终保存 result、提供 `GetTaskResult` 并在收口后回写灵台状态。
- 敬止改为显式前缀 + 默认拒绝，审计队列与单条记录加容量上限；接口注释明确当前不构成安全边界。

### 新增

- 社区健康文件：`CONTRIBUTING.md`、`CODE_OF_CONDUCT.md`、`SECURITY.md`、`DCO`、Issue/PR 模板。
- 合规检查脚本：`scripts/check-compliance.sh` / `scripts/check-compliance.ps1`，并接入 GitHub Actions。
- `CITATION.cff`、`AUTHORS`、`CHANGELOG.md`。

## [0.1.0-dev] - 2026-11-27

### 新增

- 开源声明：`NOTICE`、`THIRD_PARTY_NOTICES.md`，README 重写许可与自研边界。
- 67 个源码、脚本、策略与 rc 文件补 `SPDX-License-Identifier: Apache-2.0` 头。
- 开发板到货前的 QEMU 验证线文档 `12-QEMU验证线.md`，含产品登记与 12 项进树核对。

### 修复

- 五层 `cfg` / `rc` 中 `sa_main` 的 profile 路径由 `/system/profile/<进程名>.xml` 统一为 `/system/profile/990X.xml`（该版仍为 XML；Unreleased 已改为 JSON）。

### 文档

- `07-阶段一自研手册.md` 核实 profile 安装命名，`10-进树核对清单.md` A5 打勾并补产品登记项。

## 初始阶段 - 2026-11

- 七层命名体系与架构文档 01–09。
- 五层 SA 骨架（灵台 9901、监观 9902、和鸣 9903、令终 9904、敬止 9905），每层 14 文件。
- SELinux 策略骨架按 `security_selinux` 实证重写。
- WSL 环境迁入项目 `wsl/`，准备重启后导入与拉取源码树。
