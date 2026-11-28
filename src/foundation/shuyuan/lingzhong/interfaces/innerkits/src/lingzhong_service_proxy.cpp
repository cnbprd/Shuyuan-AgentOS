/*
 * Copyright (c) 2026 枢元智能体操作系统 (Shuyuan AgentOS)
 * SPDX-License-Identifier: Apache-2.0
 */
#include "lingzhong_service_proxy.h"
#include "message_parcel.h"
#include "message_option.h"

namespace OHOS {
namespace Shuyuan {

LingzhongServiceProxy::LingzhongServiceProxy(const sptr<IRemoteObject>& impl)
    : IRemoteProxy<ILingzhongService>(impl)
{
}

int32_t LingzhongServiceProxy::AttachTask(const std::string& taskId)
{
    MessageParcel data;
    MessageParcel reply;
    MessageOption option;
    if (!data.WriteInterfaceToken(GetDescriptor())) {
        return SHUYUAN_ERR_IPC;
    }
    data.WriteString(taskId);

    int32_t error = Remote()->SendRequest(ATTACH_TASK, data, reply, option);
    if (error != ERR_NONE) {
        return SHUYUAN_ERR_IPC;
    }
    return reply.ReadInt32();
}

int32_t LingzhongServiceProxy::FinishTask(const std::string& taskId, const std::string& result,
    std::string& finalState)
{
    MessageParcel data;
    MessageParcel reply;
    MessageOption option;
    if (!data.WriteInterfaceToken(GetDescriptor())) {
        return SHUYUAN_ERR_IPC;
    }
    data.WriteString(taskId);
    data.WriteString(result);

    int32_t error = Remote()->SendRequest(FINISH_TASK, data, reply, option);
    if (error != ERR_NONE) {
        return SHUYUAN_ERR_IPC;
    }
    int32_t err = reply.ReadInt32();
    if (err == SHUYUAN_OK) {
        finalState = reply.ReadString();
    }
    return err;
}

int32_t LingzhongServiceProxy::GetTaskFinalState(const std::string& taskId, std::string& state)
{
    MessageParcel data;
    MessageParcel reply;
    MessageOption option;
    if (!data.WriteInterfaceToken(GetDescriptor())) {
        return SHUYUAN_ERR_IPC;
    }
    data.WriteString(taskId);

    int32_t error = Remote()->SendRequest(GET_FINAL_STATE, data, reply, option);
    if (error != ERR_NONE) {
        return SHUYUAN_ERR_IPC;
    }
    int32_t err = reply.ReadInt32();
    if (err == SHUYUAN_OK) {
        state = reply.ReadString();
    }
    return err;
}

int32_t LingzhongServiceProxy::GetTaskResult(const std::string& taskId, std::string& result)
{
    MessageParcel data;
    MessageParcel reply;
    MessageOption option;
    if (!data.WriteInterfaceToken(GetDescriptor())) {
        return SHUYUAN_ERR_IPC;
    }
    data.WriteString(taskId);

    int32_t error = Remote()->SendRequest(GET_TASK_RESULT, data, reply, option);
    if (error != ERR_NONE) {
        return SHUYUAN_ERR_IPC;
    }
    int32_t err = reply.ReadInt32();
    if (err == SHUYUAN_OK) {
        result = reply.ReadString();
    }
    return err;
}

int32_t LingzhongServiceProxy::IsReady(bool& ready)
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
