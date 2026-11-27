#include "lingtai_service_stub.h"
#include "message_parcel.h"
#include "message_option.h"

namespace OHOS {
namespace Shuyuan {

int32_t LingtaiServiceStub::OnRemoteRequest(uint32_t code, MessageParcel& data,
    MessageParcel& reply, MessageOption& option)
{
    // 接口描述符校验，避免中继攻击；不一致直接拒绝。
    if (data.ReadInterfaceToken() != GetDescriptor()) {
        return SHUYUAN_ERR_IPC;
    }

    switch (code) {
        case REGISTER_AGENT: {
            std::string name = data.ReadString();
            std::string capabilities = data.ReadString();
            std::string agentId;
            int32_t err = RegisterAgent(name, capabilities, agentId);
            reply.WriteInt32(err);
            if (err == SHUYUAN_OK) {
                reply.WriteString(agentId);
            }
            return SHUYUAN_OK;
        }
        case UNREGISTER_AGENT: {
            std::string agentId = data.ReadString();
            int32_t err = UnregisterAgent(agentId);
            reply.WriteInt32(err);
            return SHUYUAN_OK;
        }
        case SUBMIT_INTENT: {
            std::string intent = data.ReadString();
            std::string contextRef = data.ReadString();
            std::string taskId;
            int32_t err = SubmitIntent(intent, contextRef, taskId);
            reply.WriteInt32(err);
            if (err == SHUYUAN_OK) {
                reply.WriteString(taskId);
            }
            return SHUYUAN_OK;
        }
        case GET_TASK_STATUS: {
            std::string taskId = data.ReadString();
            std::string status;
            int32_t err = GetTaskStatus(taskId, status);
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
        case GET_BOOT_STATUS: {
            std::string status;
            int32_t err = GetBootStatus(status);
            reply.WriteInt32(err);
            if (err == SHUYUAN_OK) {
                reply.WriteString(status);
            }
            return SHUYUAN_OK;
        }
        default:
            return IPCObjectStub::OnRemoteRequest(code, data, reply, option);
    }
}

} // namespace Shuyuan
} // namespace OHOS
