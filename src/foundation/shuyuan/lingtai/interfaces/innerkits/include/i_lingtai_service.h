/*
 * Copyright (c) 2026 枢元智能体操作系统 (Shuyuan Agent OS)
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef SHUYUAN_LINGTAI_I_LINGTAI_SERVICE_H
#define SHUYUAN_LINGTAI_I_LINGTAI_SERVICE_H

#include "iremote_broker.h"
#include "shuyuan_common.h"
#include <string>

namespace OHOS {
namespace Shuyuan {

// 灵台（调度中枢）SA ID，与 sa_profile/9901.xml 的 <name> 严格一致。
constexpr int32_t LINGTAI_SA_ID = 9901;

/**
 * 灵台对外 IPC 接口。
 * 职责边界：只做注册发现、意图接收与状态查询；不做推理循环，不直接放行高风险动作。
 * 推理由外部 Agent 运行时进程承载，本接口仅作为调度与治理入口。
 */
class ILingtaiService : public IRemoteBroker {
public:
    // IPC 消息码，按方法顺序分配，从 1 开始。
    enum {
        REGISTER_AGENT = 1,
        UNREGISTER_AGENT = 2,
        SUBMIT_INTENT = 3,
        GET_TASK_STATUS = 4,
        IS_READY = 5,
        GET_BOOT_STATUS = 6,
    };

    /**
     * 注册一个可被调度的 Agent。
     * @param name Agent 名称（可读标识）。
     * @param capabilities 能力描述（逗号分隔的能力标签）。
     * @param agentId 输出：中枢分配的 Agent 标识。
     * @return SHUYUAN_OK 成功；否则为错误码。
     */
    virtual int32_t RegisterAgent(const std::string& name, const std::string& capabilities,
        std::string& agentId) = 0;

    /** 注销已注册 Agent。 */
    virtual int32_t UnregisterAgent(const std::string& agentId) = 0;

    /**
     * 提交任务意图，创建任务实例。
     * @param intent 原始意图文本。
     * @param contextRef 上下文引用（可空）。
     * @param taskId 输出：中枢分配的任务标识。
     */
    virtual int32_t SubmitIntent(const std::string& intent, const std::string& contextRef,
        std::string& taskId) = 0;

    /** 查询任务状态（状态文本：pending / running / done / closed / rejected）。 */
    virtual int32_t GetTaskStatus(const std::string& taskId, std::string& status) = 0;

    /** 查询本层是否就绪（IPC 可响应）。进程启动 ≠ 服务就绪。 */
    virtual int32_t IsReady(bool& ready) = 0;

    /** 汇总枢元各层就绪状态（第一版返回中枢自身状态占位，跨层汇总后续接入）。 */
    virtual int32_t GetBootStatus(std::string& status) = 0;

    DECLARE_INTERFACE_DESCRIPTOR(u"OHOS.shuyuan.ILingtaiService");
};

} // namespace Shuyuan
} // namespace OHOS

#endif // SHUYUAN_LINGTAI_I_LINGTAI_SERVICE_H
