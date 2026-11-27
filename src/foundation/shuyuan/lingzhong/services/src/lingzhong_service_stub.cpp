/*
 * Copyright (c) 2026 枢元智能体操作系统 (Shuyuan Agent OS)
 * SPDX-License-Identifier: Apache-2.0
 */
#include "lingzhong_service_stub.h"
#include "message_parcel.h"
#include "message_option.h"

namespace OHOS {
namespace Shuyuan {

int32_t LingzhongServiceStub::OnRemoteRequest(uint32_t code, MessageParcel& data,
    MessageParcel& reply, MessageOption& option)
{
    if (data.ReadInterfaceToken() != GetDescriptor()) {
        return SHUYUAN_ERR_IPC;
    }

    switch (code) {
        case ATTACH_TASK: {
            std::string taskId = data.ReadString();
            int32_t err = AttachTask(taskId);
            reply.WriteInt32(err);
            return SHUYUAN_OK;
        }
        case FINISH_TASK: {
            std::string taskId = data.ReadString();
            std::string result = data.ReadString();
            std::string finalState;
            int32_t err = FinishTask(taskId, result, finalState);
            reply.WriteInt32(err);
            if (err == SHUYUAN_OK) {
                reply.WriteString(finalState);
            }
            return SHUYUAN_OK;
        }
        case GET_FINAL_STATE: {
            std::string taskId = data.ReadString();
            std::string state;
            int32_t err = GetTaskFinalState(taskId, state);
            reply.WriteInt32(err);
            if (err == SHUYUAN_OK) {
                reply.WriteString(state);
            }
            return SHUYUAN_OK;
        }
        case IS_READY: {
            bool ready = false;
            int32_t err = IsReady(ready);
            reply.WriteInt32(err);
            if (err == SHUYUAN_OK) {
                reply.WriteInt32(ready ? 1 : 0);
            }
            return SHUYUAN_OK;
        }
        default:
            return IPCObjectStub::OnRemoteRequest(code, data, reply, option);
    }
}

} // namespace Shuyuan
} // namespace OHOS
