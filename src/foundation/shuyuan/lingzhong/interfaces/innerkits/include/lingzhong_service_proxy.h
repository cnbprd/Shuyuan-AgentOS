/*
 * Copyright (c) 2026 枢元智能体操作系统 (Shuyuan AgentOS)
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef SHUYUAN_LINGZHONG_SERVICE_PROXY_H
#define SHUYUAN_LINGZHONG_SERVICE_PROXY_H

#include "i_lingzhong_service.h"
#include "iremote_proxy.h"

namespace OHOS {
namespace Shuyuan {

class LingzhongServiceProxy : public IRemoteProxy<ILingzhongService> {
public:
    explicit LingzhongServiceProxy(const sptr<IRemoteObject>& impl);
    ~LingzhongServiceProxy() override = default;

    int32_t AttachTask(const std::string& taskId) override;
    int32_t FinishTask(const std::string& taskId, const std::string& result,
        std::string& finalState) override;
    int32_t GetTaskFinalState(const std::string& taskId, std::string& state) override;
    int32_t GetTaskResult(const std::string& taskId, std::string& result) override;
    int32_t IsReady(bool& ready) override;

private:
    static inline BrokerDelegator<LingzhongServiceProxy> delegator_;
};

} // namespace Shuyuan
} // namespace OHOS

#endif // SHUYUAN_LINGZHONG_SERVICE_PROXY_H
