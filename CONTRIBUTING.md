# 贡献指南

感谢参与枢元智能体操作系统。本项目当前处于**预发布阶段**（源码骨架与 QEMU 验证线），提交前请先读 [`README.md`](README.md)、[`10-进树核对清单.md`](10-进树核对清单.md) 与 [`12-QEMU验证线.md`](12-QEMU验证线.md)。

## 1. 可贡献的内容

- 五层 SA 骨架的编译期/运行期缺陷修复。
- QEMU 验证线的脚本、日志分析与文档修订。
- SELinux 策略、构建配置、产品登记的事实核验（必须附来源）。
- 文档纠错、术语统一、链接修复。
- 测试客户端与并发/异常路径的测试补充。

**暂不接受**：未经核实的“优化”、大规模重构、引入 GPL/AGPL 等强 copyleft 依赖、把上游代码改头换面后声称为自研。

## 2. 开发环境

- Windows：PowerShell 7.6+；仓库位于 `F:\ShuyuanAgent OS`（路径含空格，命令用引号）。
- Linux / WSL：Ubuntu 22.04，`repo`、`ccache`、`ninja`、OpenJDK 17。
- 当前源码树尚未拉取、未编译；涉及编译的 PR 必须说明所用产品与命令。

## 3. 提交流程

1. Fork 仓库，从 `main` 建分支：`feat/<topic>`、`fix/<topic>`、`docs/<topic>`。
2. 一个 PR 只做一件事；标题用 `type(scope): 摘要`（如 `fix(lingtai): 修正 profile 路径`）。
3. 提交必须带 DCO 签署：

   ```bash
   git commit -s -m "fix(lingtai): 修正 profile 路径"
   ```

   `-s` 会在提交信息末尾追加 `Signed-off-by: 你的名字 <邮箱>`，表示你同意 [`DCO`](DCO)。
4. 推送后在 GitHub 发起 PR，填写 PR 模板，关联 Issue。

## 4. 代码与文档要求

- 新增 `.h/.cpp/.gn/.sh/.te/.rc` 文件必须带：

  ```text
  Copyright (c) 2026 枢元智能体操作系统 (Shuyuan AgentOS)
  SPDX-License-Identifier: Apache-2.0
  ```

- 不删除既有版权头；修改上游来源文件时保留原版权并标注改动。
- 新增第三方代码/文本/图片前，先确认许可证兼容，并更新 [`THIRD_PARTY_NOTICES.md`](THIRD_PARTY_NOTICES.md)。
- 不提交密钥、token、个人隐私、内网地址与未脱敏日志。
- 文档中的数字、版本号、外部事实必须给出来源；不确定的写“待核实”，不要猜。

## 5. 提交前自检

Windows：

```powershell
pwsh scripts/check-compliance.ps1
```

Linux / macOS：

```bash
bash scripts/check-compliance.sh
```

检查内容：必需文件、SPDX 头、JSON 可解析、`bundle.json` 许可证字段、冲突标记。

## 6. 评审与合并

- 至少 1 名维护者批准；CI `compliance` 通过。
- 涉及架构、SA ID、SELinux 域、产品登记的改动，需在 PR 中附证据链接或实测日志。
- 维护者保留拒绝不符合项目边界的 PR 的权利。

## 7. 行为与安全

- 参与即表示同意遵守 [`CODE_OF_CONDUCT.md`](CODE_OF_CONDUCT.md)。
- 安全漏洞不要开公开 Issue，按 [`SECURITY.md`](SECURITY.md) 私下报告。

## 8. 许可

提交贡献即视为同意以 **Apache License 2.0** 授权（Apache-2.0 第 5 条），并同意通过 DCO 声明来源合法。贡献不改变本项目对上游 OpenHarmony 组件的既有许可安排。
