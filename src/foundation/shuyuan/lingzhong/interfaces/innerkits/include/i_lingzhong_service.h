/*
 * Copyright (c) 2026 枢元智能体操作系统 (Shuyuan AgentOS)
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef SHUYUAN_LINGZHONG_I_LINGZHONG_SERVICE_H
#define SHUYUAN_LINGZHONG_I_LINGZHONG_SERVICE_H

#include "iremote_broker.h"
#include "shuyuan_common.h"
#include <string>

namespace OHOS {
namespace Shuyuan {

// 令终（任务闭环）SA ID，与 sa_profile/9904.xml 的 <name> 严格一致。
constexpr int32_t LINGZHONG_SA_ID = 9904;

/**
 * 令终对外 IPC 接口。
 * 负责任务状态机收口、结果回写与终结；不修改任务目标，不重复编排协作过程。
 */
class ILingzhongService : public IRemoteBroker {
public:
    enum {
        ATTACH_TASK = 1,
        FINISH_TASK = 2,
        GET_FINAL_STATE = 3,
        IS_READY = 4,
    };

    /** 挂接一个任务实例，纳入闭环管理。 */
    virtual int32_t AttachTask(const std::string& taskId) = 0;

    /**
     * 收口任务并写入结果。
     * @param taskId 任务标识。
     * @param result 结果摘要。
     * @param finalState 输出：终态（done / closed / rejected）。
     */
    virtual int32_t FinishTask(const std::string& taskId, const std::string& result,
        std::string& finalState) = 0;

    /** 查询任务终态。 */
    virtual int32_t GetTaskFinalState(const std::string& taskId, std::string& state) = 0;

    /** 查询本层是否就绪（IPC 可响应）。进程启动 ≠ 服务就绪。 */
    virtual int32_t IsReady(bool& ready) = 0;

    DECLARE_INTERFACE_DESCRIPTOR(u"OHOS.shuyuan.ILingzhongService");
};

} // namespace Shuyuan
} // namespace OHOS

#endif // SHUYUAN_LINGZHONG_I_LINGZHONG_SERVICE_H
