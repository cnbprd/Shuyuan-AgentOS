/*
 * Copyright (c) 2026 枢元智能体操作系统 (Shuyuan AgentOS)
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef SHUYUAN_JIANGUAN_SERVICE_H
#define SHUYUAN_JIANGUAN_SERVICE_H

#include "jianguan_service_stub.h"
#include "system_ability.h"
#include <mutex>
#include <string>

namespace OHOS {
namespace Shuyuan {

/**
 * 监观服务实现类。
 * 第一版为内存态采样计数；真实系统状态采集（进程、内存、任务上下文）后续接入。
 */
class JianguanService : public SystemAbility, public JianguanServiceStub {
    DECLARE_SYSTEM_ABILITY(JianguanService);

public:
    explicit JianguanService(int32_t saId, bool runOnCreate);
    ~JianguanService() override = default;

    void OnStart() override;
    void OnStop() override;

    int32_t GetSnapshot(std::string& snapshot) override;
    int32_t IsReady(bool& ready) override;

private:
    std::mutex mutex_;
    int32_t sampleCount_ = 0;
    bool ready_ = false;
};

} // namespace Shuyuan
} // namespace OHOS

#endif // SHUYUAN_JIANGUAN_SERVICE_H
