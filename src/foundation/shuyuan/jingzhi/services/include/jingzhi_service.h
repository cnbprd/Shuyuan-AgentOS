/*
 * Copyright (c) 2026 枢元智能体操作系统 (Shuyuan AgentOS)
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef SHUYUAN_JINGZHI_SERVICE_H
#define SHUYUAN_JINGZHI_SERVICE_H

#include "jingzhi_service_stub.h"
#include "system_ability.h"
#include <deque>
#include <mutex>
#include <string>

namespace OHOS {
namespace Shuyuan {

/**
 * 敬止服务实现类。
 * 第一版为静态策略 + 内存审计队列；策略配置化与远程审批流留待后续版本。
 */
class JingzhiService : public SystemAbility, public JingzhiServiceStub {
    DECLARE_SYSTEM_ABILITY(JingzhiService);

public:
    explicit JingzhiService(int32_t saId, bool runOnCreate);
    ~JingzhiService() override = default;

    void OnStart() override;
    void OnStop() override;

    int32_t PreAuthorize(const std::string& subject, const std::string& action,
        int32_t& verdict, std::string& reason) override;
    int32_t Audit(const std::string& record) override;
    int32_t IsReady(bool& ready) override;

private:
    std::mutex mutex_;
    std::deque<std::string> auditQueue_;
    int32_t auditCount_ = 0;
    bool ready_ = false;
};

} // namespace Shuyuan
} // namespace OHOS

#endif // SHUYUAN_JINGZHI_SERVICE_H
