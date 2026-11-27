/*
 * Copyright (c) 2026 枢元智能体操作系统 (Shuyuan AgentOS)
 * SPDX-License-Identifier: Apache-2.0
 */
#include "lingtai_service_proxy.h"
#include "message_parcel.h"
#include "message_option.h"

namespace OHOS {
namespace Shuyuan {

LingtaiServiceProxy::LingtaiServiceProxy(const sptr<IRemoteObject>& impl)
    : IRemoteProxy<ILingtaiService>(impl)
{
}

int32_t LingtaiServiceProxy::RegisterAgent(const std::string& name, const std::string& capabilities,
    std::string& agentId)
{
    MessageParcel data;
    MessageParcel reply;
    MessageOption option;
    if (!data.WriteInterfaceToken(GetDescriptor())) {
        return SHUYUAN_ERR_IPC;
    }
    data.WriteString(name);
    data.WriteString(capabilities);

    int32_t error = Remote()->SendRequest(REGISTER_AGENT, data, reply, option);
    if (error != ERR_NONE) {
        return SHUYUAN_ERR_IPC;
    }
    int32_t err = reply.ReadInt32();
    if (err == SHUYUAN_OK) {
        agentId = reply.ReadString();
    }
    return err;
}

int32_t LingtaiServiceProxy::UnregisterAgent(const std::string& agentId)
{
    MessageParcel data;
    MessageParcel reply;
    MessageOption option;
    if (!data.WriteInterfaceToken(GetDescriptor())) {
        return SHUYUAN_ERR_IPC;
    }
    data.WriteString(agentId);

    int32_t error = Remote()->SendRequest(UNREGISTER_AGENT, data, reply, option);
    if (error != ERR_NONE) {
        return SHUYUAN_ERR_IPC;
    }
    return reply.ReadInt32();
}

int32_t LingtaiServiceProxy::SubmitIntent(const std::string& intent, const std::string& contextRef,
    std::string& taskId)
{
    MessageParcel data;
    MessageParcel reply;
    MessageOption option;
    if (!data.WriteInterfaceToken(GetDescriptor())) {
        return SHUYUAN_ERR_IPC;
    }
    data.WriteString(intent);
    data.WriteString(contextRef);

    int32_t error = Remote()->SendRequest(SUBMIT_INTENT, data, reply, option);
    if (error != ERR_NONE) {
        return SHUYUAN_ERR_IPC;
    }
    int32_t err = reply.ReadInt32();
    if (err == SHUYUAN_OK) {
        taskId = reply.ReadString();
    }
    return err;
}

int32_t LingtaiServiceProxy::GetTaskStatus(const std::string& taskId, std::string& status)
{
    MessageParcel data;
    MessageParcel reply;
    MessageOption option;
    if (!data.WriteInterfaceToken(GetDescriptor())) {
        return SHUYUAN_ERR_IPC;
    }
    data.WriteString(taskId);

    int32_t error = Remote()->SendRequest(GET_TASK_STATUS, data, reply, option);
    if (error != ERR_NONE) {
        return SHUYUAN_ERR_IPC;
    }
    int32_t err = reply.ReadInt32();
    if (err == SHUYUAN_OK) {
        status = reply.ReadString();
    }
    return err;
}

int32_t LingtaiServiceProxy::IsReady(bool& ready)
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

int32_t LingtaiServiceProxy::GetBootStatus(std::string& status)
{
    MessageParcel data;
    MessageParcel reply;
    MessageOption option;
    if (!data.WriteInterfaceToken(GetDescriptor())) {
        return SHUYUAN_ERR_IPC;
    }

    int32_t error = Remote()->SendRequest(GET_BOOT_STATUS, data, reply, option);
    if (error != ERR_NONE) {
        return SHUYUAN_ERR_IPC;
    }
    int32_t err = reply.ReadInt32();
    if (err == SHUYUAN_OK) {
        status = reply.ReadString();
    }
    return err;
}

} // namespace Shuyuan
} // namespace OHOS
