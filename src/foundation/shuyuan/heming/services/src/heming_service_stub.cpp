/*
 * Copyright (c) 2026 枢元智能体操作系统 (Shuyuan Agent OS)
 * SPDX-License-Identifier: Apache-2.0
 */
#include "heming_service_stub.h"
#include "message_parcel.h"
#include "message_option.h"

namespace OHOS {
namespace Shuyuan {

int32_t HemingServiceStub::OnRemoteRequest(uint32_t code, MessageParcel& data,
    MessageParcel& reply, MessageOption& option)
{
    if (data.ReadInterfaceToken() != GetDescriptor()) {
        return SHUYUAN_ERR_IPC;
    }

    switch (code) {
        case DISPATCH_PLAN: {
            std::string planId = data.ReadString();
            std::string steps = data.ReadString();
            std::string collabId;
            int32_t err = DispatchPlan(planId, steps, collabId);
            reply.WriteInt32(err);
            if (err == SHUYUAN_OK) {
                reply.WriteString(collabId);
            }
            return SHUYUAN_OK;
        }
        case GET_COLLAB_STATUS: {
            std::string collabId = data.ReadString();
            std::string status;
            int32_t err = GetCollabStatus(collabId, status);
            reply.WriteInt32(err);
            if (err == SHUYUAN_OK) {
                reply.WriteString(status);
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
