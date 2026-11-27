/*
 * Copyright (c) 2026 枢元智能体操作系统 (Shuyuan Agent OS)
 * SPDX-License-Identifier: Apache-2.0
 */
#include "jingzhi_service_proxy.h"
#include "message_parcel.h"
#include "message_option.h"

namespace OHOS {
namespace Shuyuan {

JingzhiServiceProxy::JingzhiServiceProxy(const sptr<IRemoteObject>& impl)
    : IRemoteProxy<IJingzhiService>(impl)
{
}

int32_t JingzhiServiceProxy::PreAuthorize(const std::string& subject, const std::string& action,
    int32_t& verdict, std::string& reason)
{
    MessageParcel data;
    MessageParcel reply;
    MessageOption option;
    if (!data.WriteInterfaceToken(GetDescriptor())) {
        return SHUYUAN_ERR_IPC;
    }
    data.WriteString(subject);
    data.WriteString(action);

    int32_t error = Remote()->SendRequest(PRE_AUTHORIZE, data, reply, option);
    if (error != ERR_NONE) {
        return SHUYUAN_ERR_IPC;
    }
    int32_t err = reply.ReadInt32();
    if (err == SHUYUAN_OK) {
        verdict = reply.ReadInt32();
        reason = reply.ReadString();
    }
    return err;
}

int32_t JingzhiServiceProxy::Audit(const std::string& record)
{
    MessageParcel data;
    MessageParcel reply;
    MessageOption option;
    if (!data.WriteInterfaceToken(GetDescriptor())) {
        return SHUYUAN_ERR_IPC;
    }
    data.WriteString(record);

    int32_t error = Remote()->SendRequest(AUDIT, data, reply, option);
    if (error != ERR_NONE) {
        return SHUYUAN_ERR_IPC;
    }
    return reply.ReadInt32();
}

int32_t JingzhiServiceProxy::IsReady(bool& ready)
{
    MessageParcel data;
    MessageParcel reply;
    MessageOption option;
    if (!data.WriteInterfaceToken(GetDescriptor())) {
        return SHUYUAN_ERR_IPC;
    }

    int32_t error = Remote()->SendRequest(IS_READY, data, reply, option);
    if (error != ERR_NONE) {
        return SHUYUAN_ERR_IPC;
    }
    int32_t err = reply.ReadInt32();
    if (err == SHUYUAN_OK) {
        int32_t readyVal = reply.ReadInt32();
        ready = (readyVal != 0);
    }
    return err;
}

} // namespace Shuyuan
} // namespace OHOS
