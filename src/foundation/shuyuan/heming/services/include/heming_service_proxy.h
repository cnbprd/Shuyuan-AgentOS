/*
 * Copyright (c) 2026 枢元智能体操作系统 (Shuyuan Agent OS)
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef SHUYUAN_HEMING_SERVICE_PROXY_H
#define SHUYUAN_HEMING_SERVICE_PROXY_H

#include "i_heming_service.h"
#include "iremote_proxy.h"

namespace OHOS {
namespace Shuyuan {

class HemingServiceProxy : public IRemoteProxy<IHemingService> {
public:
    explicit HemingServiceProxy(const sptr<IRemoteObject>& impl);
    ~HemingServiceProxy() override = default;

    int32_t DispatchPlan(const std::string& planId, const std::string& steps,
        std::string& collabId) override;
    int32_t GetCollabStatus(const std::string& collabId, std::string& status) override;
    int32_t IsReady(bool& ready) override;

private:
    static inline BrokerDelegator<HemingServiceProxy> delegator_;
};

} // namespace Shuyuan
} // namespace OHOS

#endif // SHUYUAN_HEMING_SERVICE_PROXY_H
