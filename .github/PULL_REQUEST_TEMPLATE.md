## 变更类型

- [ ] fix：缺陷修复
- [ ] feat：新增能力
- [ ] docs：文档
- [ ] build：构建/配置
- [ ] refactor：重构（不改变行为）
- [ ] chore：杂项

## 关联 Issue

Closes #

## 变更说明

<!-- 说明改了什么、为什么改；涉及 SA ID / SELinux / 产品登记时给出依据链接。 -->

## 验证方式

- [ ] `pwsh scripts/check-compliance.ps1`（Windows）或 `bash scripts/check-compliance.sh`（Linux）
- [ ] JSON / GN 配置可解析
- [ ] 编译通过（如适用，注明产品与命令）
- [ ] QEMU/真机验证（如适用，附关键日志）

## 合规确认

- [ ] 新增源码/脚本/策略/rc 文件已带 SPDX 头
- [ ] 未引入不兼容许可证的第三方代码；如有，已更新 `THIRD_PARTY_NOTICES.md`
- [ ] 提交带 DCO 签署（`git commit -s`）
- [ ] 未提交密钥、个人信息、内网地址或未脱敏日志

## 备注

<!-- 截图、日志、待核实项。 -->
