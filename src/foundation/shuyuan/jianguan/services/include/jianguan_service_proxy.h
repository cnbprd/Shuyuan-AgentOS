/*
 * Copyright (c) 2026 枢元智能体操作系统 (Shuyuan AgentOS)
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef SHUYUAN_JIANGUAN_SERVICE_PROXY_H
#define SHUYUAN_JIANGUAN_SERVICE_PROXY_H

#include "i_jianguan_service.h"
#include "iremote_proxy.h"

namespace OHOS {
namespace Shuyuan {

class JianguanServiceProxy : public IRemoteProxy<IJianguanService> {
public:
    explicit JianguanServiceProxy(const sptr<IRemoteObject>& impl);
    ~JianguanServiceProxy() override = default;

    int32_t GetSnapshot(std::string& snapshot) override;
    int32_t IsReady(bool& ready) override;

private:
    static inline BrokerDelegator<JianguanServiceProxy> delegator_;
};

} // namespace Shuyuan
} // namespace OHOS

#endif // SHUYUAN_JIANGUAN_SERVICE_PROXY_H
