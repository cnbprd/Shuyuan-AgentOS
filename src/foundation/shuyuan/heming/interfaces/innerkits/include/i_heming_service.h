/*
 * Copyright (c) 2026 枢元智能体操作系统 (Shuyuan Agent OS)
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef SHUYUAN_HEMING_I_HEMING_SERVICE_H
#define SHUYUAN_HEMING_I_HEMING_SERVICE_H

#include "iremote_broker.h"
#include "shuyuan_common.h"
#include <string>

namespace OHOS {
namespace Shuyuan {

// 和鸣（协作机制）SA ID，与 sa_profile/9903.xml 的 <name> 严格一致。
constexpr int32_t HEMING_SA_ID = 9903;

/**
 * 和鸣对外 IPC 接口。
 * 按灵台规划完成多 Agent / Skill 编排与消息中转；不持有业务规则与审批权。
 */
class IHemingService : public IRemoteBroker {
public:
    enum {
        DISPATCH_PLAN = 1,
        GET_COLLAB_STATUS = 2,
        IS_READY = 3,
    };

    /**
     * 下发协作规划。
     * @param planId 灵台规划标识。
     * @param steps 协作步骤描述（第一版为文本，后续结构化）。
     * @param collabId 输出：和鸣侧协作实例标识。
     */
    virtual int32_t DispatchPlan(const std::string& planId, const std::string& steps,
        std::string& collabId) = 0;

    /** 查询协作实例状态（dispatched / running / done / failed）。 */
    virtual int32_t GetCollabStatus(const std::string& collabId, std::string& status) = 0;

    /** 查询本层是否就绪（IPC 可响应）。进程启动 ≠ 服务就绪。 */
    virtual int32_t IsReady(bool& ready) = 0;

    DECLARE_INTERFACE_DESCRIPTOR(u"OHOS.shuyuan.IHemingService");
};

} // namespace Shuyuan
} // namespace OHOS

#endif // SHUYUAN_HEMING_I_HEMING_SERVICE_H
