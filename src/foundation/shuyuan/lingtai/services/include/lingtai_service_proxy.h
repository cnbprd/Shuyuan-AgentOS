/*
 * Copyright (c) 2026 枢元智能体操作系统 (Shuyuan AgentOS)
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef SHUYUAN_LINGTAI_SERVICE_PROXY_H
#define SHUYUAN_LINGTAI_SERVICE_PROXY_H

#include "i_lingtai_service.h"
#include "iremote_proxy.h"

namespace OHOS {
namespace Shuyuan {

/**
 * Proxy：客户端侧代理。通过 Remote()->SendRequest() 向 Stub 发起同步 IPC，
 * 调用方经 samgr GetSystemAbility 拿到 remote 对象后用 iface_cast 转换为本类型。
 */
class LingtaiServiceProxy : public IRemoteProxy<ILingtaiService> {
public:
    explicit LingtaiServiceProxy(const sptr<IRemoteObject>& impl);
    ~LingtaiServiceProxy() override = default;

    int32_t RegisterAgent(const std::string& name, const std::string& capabilities,
        std::string& agentId) override;
    int32_t UnregisterAgent(const std::string& agentId) override;
    int32_t SubmitIntent(const std::string& intent, const std::string& contextRef,
        std::string& taskId) override;
    int32_t GetTaskStatus(const std::string& taskId, std::string& status) override;
    int32_t IsReady(bool& ready) override;
    int32_t GetBootStatus(std::string& status) override;

private:
    static inline BrokerDelegator<LingtaiServiceProxy> delegator_;
};

} // namespace Shuyuan
} // namespace OHOS

#endif // SHUYUAN_LINGTAI_SERVICE_PROXY_H
