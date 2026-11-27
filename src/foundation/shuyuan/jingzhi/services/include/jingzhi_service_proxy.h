/*
 * Copyright (c) 2026 枢元智能体操作系统 (Shuyuan Agent OS)
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef SHUYUAN_JINGZHI_SERVICE_PROXY_H
#define SHUYUAN_JINGZHI_SERVICE_PROXY_H

#include "i_jingzhi_service.h"
#include "iremote_proxy.h"

namespace OHOS {
namespace Shuyuan {

class JingzhiServiceProxy : public IRemoteProxy<IJingzhiService> {
public:
    explicit JingzhiServiceProxy(const sptr<IRemoteObject>& impl);
    ~JingzhiServiceProxy() override = default;

    int32_t PreAuthorize(const std::string& subject, const std::string& action,
        int32_t& verdict, std::string& reason) override;
    int32_t Audit(const std::string& record) override;
    int32_t IsReady(bool& ready) override;

private:
    static inline BrokerDelegator<JingzhiServiceProxy> delegator_;
};

} // namespace Shuyuan
} // namespace OHOS

#endif // SHUYUAN_JINGZHI_SERVICE_PROXY_H
