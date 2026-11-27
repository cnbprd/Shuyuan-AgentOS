# 安全政策

## 支持范围

本项目当前为预发布阶段，仅维护 `main` 分支。尚未发布正式版本，不承诺旧版本的安全维护。

## 报告漏洞

**不要开公开 Issue 披露漏洞细节、利用步骤或未脱敏日志。**

请使用 GitHub 仓库的私密漏洞报告入口：

<https://github.com/cnbprd/Shuyuan-AgentOS/security/advisories/new>

若该入口不可用，请通过 GitHub 联系维护者 [@cnbprd](https://github.com/cnbprd)，先只说明“需要私密渠道”，不要附带利用细节。

## 报告应包含

- 受影响组件（如 `lingtai`、`init`、构建脚本）与 commit/分支。
- 复现步骤、期望结果、实际结果。
- 影响判断（提权、拒绝服务、信息泄露、供应链等）。
- 可选的最小 PoC；请勿包含真实密钥、个人信息或生产数据。

## 处理方式

维护者会尽快确认并评估；修复完成后再与你协商披露时间。修复前请勿公开细节。当前为个人维护项目，无法承诺固定 SLA。

## 范围外

- OpenHarmony 上游组件漏洞：请报告给 OpenHarmony 安全团队。
- QEMU、Ubuntu Base 等第三方工具漏洞：请报告给对应上游。
- 仅影响本地开发环境、且不进入分发产物的配置问题：按普通 Issue 处理。

## 安全基线

- 仓库不得提交密钥、token、私钥、内网地址与未脱敏日志。
- CI 仅使用只读权限；新增 Action 需固定版本并说明用途。
- 引入第三方代码前核对许可证与供应链来源，并更新 [`THIRD_PARTY_NOTICES.md`](THIRD_PARTY_NOTICES.md)。
