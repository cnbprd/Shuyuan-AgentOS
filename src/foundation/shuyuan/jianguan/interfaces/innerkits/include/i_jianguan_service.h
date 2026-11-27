/*
 * Copyright (c) 2026 枢元智能体操作系统 (Shuyuan AgentOS)
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef SHUYUAN_JIANGUAN_I_JIANGUAN_SERVICE_H
#define SHUYUAN_JIANGUAN_I_JIANGUAN_SERVICE_H

#include "iremote_broker.h"
#include "shuyuan_common.h"
#include <string>

namespace OHOS {
namespace Shuyuan {

// 监观（感知层）SA ID，与 sa_profile/9902.xml 的 <name> 严格一致。
constexpr int32_t JIANGUAN_SA_ID = 9902;

/**
 * 监观对外 IPC 接口。
 * 只采集上报、不下发指令；快照供灵台规划使用。
 */
class IJianguanService : public IRemoteBroker {
public:
    enum {
        GET_SNAPSHOT = 1,
        IS_READY = 2,
    };

    /** 获取当前环境与任务状态快照（第一版为文本/简易 JSON）。 */
    virtual int32_t GetSnapshot(std::string& snapshot) = 0;

    /** 查询本层是否就绪（IPC 可响应）。进程启动 ≠ 服务就绪。 */
    virtual int32_t IsReady(bool& ready) = 0;

    DECLARE_INTERFACE_DESCRIPTOR(u"OHOS.shuyuan.IJianguanService");
};

} // namespace Shuyuan
} // namespace OHOS

#endif // SHUYUAN_JIANGUAN_I_JIANGUAN_SERVICE_H
