# 第三方出处与许可证声明

> 核验日期：2026-11-27。核验方式：对下列 Gitee 仓库做浅克隆，读取根目录 `LICENSE` / `NOTICE`；未克隆或未读取的条目在「核验状态」中明确标注。
> 本文件记录的是**借鉴出处与许可证状态**，不构成法律意见。

## 1. 自研边界

- **自研**：七层命名与架构、五层 SA 的接口定义与实现、调度/治理逻辑、`init` 启动编排、测试客户端、全部项目文档与脚本。
- **借鉴**：OpenHarmony 的 SA 接口范式、SELinux 策略范式、产品配置与构建规则；只借鉴结构、接口用法与公开事实，**未整段复制上游源文件**。
- **底座**：OpenHarmony 本体按上游许可证使用，不属于本项目自研范围。
- **工具**：QEMU、Ubuntu Base 只用于本地开发/验证，不随本仓库分发。

## 2. 逐项清单

| 来源 | 许可证 | 本项目借鉴内容 | 是否复制源文件 | 核验状态 |
| :--- | :--- | :--- | :--- | :--- |
| [`systemabilitymgr_safwk`](https://gitee.com/openharmony/systemabilitymgr_safwk) | Apache-2.0 | SA 框架接口、目录组织、README 与 `interfaces/` 的接口说明 | 否，范式参考、自研实现 | 已核对 `LICENSE`；仓库无 `NOTICE` |
| [`systemabilitymgr_samgr`](https://gitee.com/openharmony/systemabilitymgr_samgr) | Apache-2.0 | SA 注册/查询、IPC 调用与 `samgr` 交互范式 | 否 | 已核对 `LICENSE`；仓库无 `NOTICE` |
| [`security_selinux`](https://gitee.com/openharmony/security_selinux) | Apache-2.0 | `sa_service_attr` / `sadomain` 属性、`service_contexts` 数字 SAID 格式、`samain_exec` 与 `samgr` 授权范式 | 否，策略骨架按范式重写 | 已核对 `LICENSE`；仓库无 `NOTICE` |
| [`build`](https://gitee.com/openharmony/build) | Apache-2.0 + BSD-3-Clause（含 Chromium 派生部分） | `sa_profile.gni` 的 profile 安装规则、`BUILDCONFIG.gn` 的 `build_selinux` 默认值 | 否，仅事实核验 | 已核对 `LICENSE`（46 行复合文本）；仓库无 `NOTICE` |
| [`openharmony-loongarch/manifest`](https://gitee.com/openharmony-loongarch/manifest) | Apache-2.0 | `loongarch.xml` 清单、`ohos-main` 分支与同步入口 | 否 | 已核对 `LICENSE`；仓库无 `NOTICE` |
| [`vendor_ohemu`](https://gitee.com/openharmony-loongarch/vendor_ohemu) | Apache-2.0 | `qemu_loongarch64_linux_min` 产品名与 `config.json` 字段 | 否，仅事实核验 | 已核对 `LICENSE`；仓库无 `NOTICE` |
| [`vendor_loongson`](https://gitee.com/openharmony-loongarch/vendor_loongson) | **仓库未附 `LICENSE` 文件** | `ls3a5000` 产品名、`device/board/loongson/ls3a5000` 路径 | 否，仅名称/路径引用 | 已确认根目录无 `LICENSE` / `NOTICE`；若后续复制其配置，须先向上游确认许可 |
| [`device_board_loongson`](https://gitee.com/openharmony-loongarch/device_board_loongson) | **仓库未附 `LICENSE` 文件** | 板级目录名与产品归属 | 否，仅名称引用 | 已确认根目录无 `LICENSE` / `NOTICE` |
| [`device_soc_loongson`](https://gitee.com/openharmony-loongarch/device_soc_loongson) | **仓库未附 `LICENSE` 文件** | SOC 目录名与板级归属 | 否，仅名称引用 | 已确认根目录无 `LICENSE` / `NOTICE` |
| OpenHarmony 官方文档（docs.openharmony.cn） | 未核实 | API、构建与 SA 开发说明 | 否，仅意译参考 | **未逐页核对许可证** |
| [QEMU](https://www.qemu.org/license.html) | GPL-2.0 | 本地启动/验证工具 | 不适用，不随仓库分发 | 已核对 QEMU 官方许可证页 |
| Ubuntu Base 22.04 | 内含组件各自许可 | WSL 开发环境基础镜像 | 不适用，不随仓库分发 | 未逐包核对；不对外分发 |
| 《诗经》 | 公有领域 | 七层命名语源（《崧高》《七月》《灵台》《皇矣》《有瞽》《既醉》《文王》） | 引用原文 | 篇目与用字已在 `01-命名体系.md` 逐字复核 |
| [Contributor Covenant 2.1](https://www.contributor-covenant.org/version/2/1/code_of_conduct/) | CC BY 4.0 | 社区行为准则（`CODE_OF_CONDUCT.md`） | 是，改编并注明出处与修改 | 已核对官网版本号与许可说明 |

## 3. 许可证文本位置

- 本项目：根目录 [`LICENSE`](LICENSE)（Apache License 2.0 全文）、[`NOTICE`](NOTICE)。
- 上游：上表各仓库根目录的 `LICENSE`。`safwk`、`samgr`、`security_selinux`、`manifest`、`vendor_ohemu` 实测均为 Apache-2.0 全文；`build` 为 46 行复合文本（Apache-2.0 + Chromium 的 BSD-3-Clause 派生条款）；上述六仓**均未提供 `NOTICE` 文件**。`vendor_loongson`、`device_board_loongson`、`device_soc_loongson` 根目录无 `LICENSE` / `NOTICE`。
- 行为准则：`CODE_OF_CONDUCT.md` 改编自 Contributor Covenant 2.1，按 [CC BY 4.0](https://creativecommons.org/licenses/by/4.0/) 使用；该文本不适用本项目的 Apache-2.0，再分发时保留出处与许可证说明。
- 若上游后续补充 `NOTICE`，再分发时应一并保留。

## 4. 分发与贡献要求

1. 再分发本仓库时，保留 `LICENSE`、`NOTICE`、本文件，不得删除或改写版权与许可声明。
2. 修改本仓库文件时，按 Apache-2.0 第 4(b) 条在文件中显著标注改动。
3. 未来若引入上游源文件（而非仅借鉴范式）：在文件头保留原版权与 SPDX 标识，更新本文件，并在提交说明中注明来源与提交号；不得再声称该部分为自研。
4. 新增第三方依赖时，先核对许可证兼容性，再更新本文件；GPL 等强 copyleft 代码不得进入本仓库代码树。
5. 提交贡献即视为同意以 Apache-2.0 授权（Apache-2.0 第 5 条）。

## 5. 核验记录与辅助证据

- 加 SPDX 头之前，对本仓库 `src/`、`scripts/` 共 83 个文件检索 `Copyright` 与 `SPDX`：命中均为 0，未发现上游版权头，作为「未整段复制」的辅助证据（不等同法律结论）。本轮已为 69 个源码/脚本/策略/rc 文件补 `SPDX-License-Identifier: Apache-2.0` 头。
- 上游 `vendor_loongson` 根目录仅 4 个文件（`common-config/rich-la.json`、`ls3a5000/config.json`、`ls3a5000/ohos.build`、`ls3a5000/product.gni`），无 `LICENSE`。
- `device_board_loongson` 根目录仅 `CODEOWNERS`、`ls3a5000/`、`OAT.xml`、`README_zh.md`，无 `LICENSE`。
- `device_soc_loongson` 根目录仅 `CODEOWNERS`、`ls3a5000/`、`OAT.xml`、`README.md`，无 `LICENSE`。

## 6. 待核实与更正

- OpenHarmony 官方文档的许可证未逐项核对；本项目只作 API/构建说明的意译参考，未整段复制文档文字。
- `build` 的复合 `LICENSE` 已读取，但其中 Chromium 派生条款的适用范围未逐文件核对（本项目仅引用两处构建规则事实，未复制其代码）。
- 若发现遗漏或错误，请在本仓库提 Issue，注明来源文件与许可证链接。
