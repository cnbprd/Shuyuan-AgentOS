/*
 * Copyright (c) 2026 枢元智能体操作系统 (Shuyuan AgentOS)
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef SHUYUAN_JINGZHI_I_JINGZHI_SERVICE_H
#define SHUYUAN_JINGZHI_I_JINGZHI_SERVICE_H

#include "iremote_broker.h"
#include "shuyuan_common.h"
#include <string>

namespace OHOS {
namespace Shuyuan {

// 敬止（治理/审批层）SA ID，与 sa_profile/9905.json 的 name 字段严格一致。
constexpr int32_t JINGZHI_SA_ID = 9905;

// 授权结论：放行 / 拦截 / 转审批。
constexpr int32_t VERDICT_ALLOW = 0;
constexpr int32_t VERDICT_DENY = 1;
constexpr int32_t VERDICT_PENDING = 2;

/**
 * 敬止对外 IPC 接口。
 * 动作出口前请求授权，行为发生后写审计。
 * 当前为骨架静态策略：默认拒绝 + 显式 allow/deny/pending 前缀；
 * 尚无调用方身份、授权令牌或下游强制校验，因此不能把本接口当作安全边界。
 */
class IJingzhiService : public IRemoteBroker {
public:
    enum {
        PRE_AUTHORIZE = 1,
        AUDIT = 2,
        IS_READY = 3,
    };

    /**
     * 动作出口前授权校验。
     * @param subject 行为主体（Agent / Skill 标识）。
     * @param action 待执行动作描述。
     * @param verdict 输出：VERDICT_ALLOW / DENY / PENDING。
     * @param reason 输出：结论原因或策略命中说明。
     */
    virtual int32_t PreAuthorize(const std::string& subject, const std::string& action,
        int32_t& verdict, std::string& reason) = 0;

    /** 写一条审计记录（主体、动作、时间、结论由调用方拼装为文本）。 */
    virtual int32_t Audit(const std::string& record) = 0;

    /** 查询本层是否就绪（IPC 可响应）。进程启动 ≠ 服务就绪。 */
    virtual int32_t IsReady(bool& ready) = 0;

    DECLARE_INTERFACE_DESCRIPTOR(u"OHOS.shuyuan.IJingzhiService");
};

} // namespace Shuyuan
} // namespace OHOS

#endif // SHUYUAN_JINGZHI_I_JINGZHI_SERVICE_H
