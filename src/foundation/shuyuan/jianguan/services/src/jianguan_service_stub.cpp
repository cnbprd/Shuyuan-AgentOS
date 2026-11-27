/*
 * Copyright (c) 2026 枢元智能体操作系统 (Shuyuan AgentOS)
 * SPDX-License-Identifier: Apache-2.0
 */
#include "jianguan_service_stub.h"
#include "message_parcel.h"
#include "message_option.h"

namespace OHOS {
namespace Shuyuan {

int32_t JianguanServiceStub::OnRemoteRequest(uint32_t code, MessageParcel& data,
    MessageParcel& reply, MessageOption& option)
{
    if (data.ReadInterfaceToken() != GetDescriptor()) {
        return SHUYUAN_ERR_IPC;
    }

    switch (code) {
        case GET_SNAPSHOT: {
            std::string snapshot;
            int32_t err = GetSnapshot(snapshot);
            reply.WriteInt32(err);
            if (err == SHUYUAN_OK) {
                reply.WriteString(snapshot);
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
