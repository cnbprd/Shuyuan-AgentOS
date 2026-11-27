/*
 * Copyright (c) 2026 枢元智能体操作系统 (Shuyuan Agent OS)
 * SPDX-License-Identifier: Apache-2.0
 */
#include "jianguan_service_proxy.h"
#include "message_parcel.h"
#include "message_option.h"

namespace OHOS {
namespace Shuyuan {

JianguanServiceProxy::JianguanServiceProxy(const sptr<IRemoteObject>& impl)
    : IRemoteProxy<IJianguanService>(impl)
{
}

int32_t JianguanServiceProxy::GetSnapshot(std::string& snapshot)
{
    MessageParcel data;
    MessageParcel reply;
    MessageOption option;
    if (!data.WriteInterfaceToken(GetDescriptor())) {
        return SHUYUAN_ERR_IPC;
    }

    int32_t error = Remote()->SendRequest(GET_SNAPSHOT, data, reply, option);
    if (error != ERR_NONE) {
        return SHUYUAN_ERR_IPC;
    }
    int32_t err = reply.ReadInt32();
    if (err == SHUYUAN_OK) {
        snapshot = reply.ReadString();
    }
    return err;
}

int32_t JianguanServiceProxy::IsReady(bool& ready)
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
