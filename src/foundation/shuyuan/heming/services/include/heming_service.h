/*
 * Copyright (c) 2026 枢元智能体操作系统 (Shuyuan AgentOS)
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef SHUYUAN_HEMING_SERVICE_H
#define SHUYUAN_HEMING_SERVICE_H

#include "heming_service_stub.h"
#include "system_ability.h"
#include <map>
#include <mutex>
#include <string>

namespace OHOS {
namespace Shuyuan {

/**
 * 和鸣服务实现类。
 * 第一版登记协作实例与状态；真实多 Agent/Skill 编排下发后续接入。
 */
class HemingService : public SystemAbility, public HemingServiceStub {
    DECLARE_SYSTEM_ABILITY(HemingService);

public:
    explicit HemingService(int32_t saId, bool runOnCreate);
    ~HemingService() override = default;

    void OnStart() override;
    void OnStop() override;

    int32_t DispatchPlan(const std::string& planId, const std::string& steps,
        std::string& collabId) override;
    int32_t GetCollabStatus(const std::string& collabId, std::string& status) override;
    int32_t IsReady(bool& ready) override;

private:
    std::mutex mutex_;
    std::map<std::string, std::string> collabStatus_;
    int32_t collabSeq_ = 0;
    bool ready_ = false;
};

} // namespace Shuyuan
} // namespace OHOS

#endif // SHUYUAN_HEMING_SERVICE_H
