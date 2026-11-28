/*
 * Copyright (c) 2026 枢元智能体操作系统 (Shuyuan AgentOS)
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef SHUYUAN_LINGZHONG_SERVICE_H
#define SHUYUAN_LINGZHONG_SERVICE_H

#include "lingzhong_service_stub.h"
#include "system_ability.h"
#include <map>
#include <mutex>
#include <string>

namespace OHOS {
namespace Shuyuan {

/**
 * 令终服务实现类。
 * 第一版为内存态任务状态机；结果持久化与超时收口后续接入。
 */
class LingzhongService : public SystemAbility, public LingzhongServiceStub {
    DECLARE_SYSTEM_ABILITY(LingzhongService);

public:
    explicit LingzhongService(int32_t saId, bool runOnCreate);
    ~LingzhongService() override = default;

    void OnStart() override;
    void OnStop() override;

    int32_t AttachTask(const std::string& taskId) override;
    int32_t FinishTask(const std::string& taskId, const std::string& result,
        std::string& finalState) override;
    int32_t GetTaskFinalState(const std::string& taskId, std::string& state) override;
    int32_t GetTaskResult(const std::string& taskId, std::string& result) override;
    int32_t IsReady(bool& ready) override;

private:
    int32_t NotifyLingtaiStatus(const std::string& taskId, const std::string& state);

    std::mutex mutex_;
    std::map<std::string, std::string> taskState_;
    std::map<std::string, std::string> taskResult_;
    bool ready_ = false;
};

} // namespace Shuyuan
} // namespace OHOS

#endif // SHUYUAN_LINGZHONG_SERVICE_H
