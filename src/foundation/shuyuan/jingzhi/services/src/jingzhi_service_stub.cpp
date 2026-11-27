#include "jingzhi_service_stub.h"
#include "message_parcel.h"
#include "message_option.h"

namespace OHOS {
namespace Shuyuan {

int32_t JingzhiServiceStub::OnRemoteRequest(uint32_t code, MessageParcel& data,
    MessageParcel& reply, MessageOption& option)
{
    if (data.ReadInterfaceToken() != GetDescriptor()) {
        return SHUYUAN_ERR_IPC;
    }

    switch (code) {
        case PRE_AUTHORIZE: {
            std::string subject = data.ReadString();
            std::string action = data.ReadString();
            int32_t verdict = VERDICT_ALLOW;
            std::string reason;
            int32_t err = PreAuthorize(subject, action, verdict, reason);
            reply.WriteInt32(err);
            if (err == SHUYUAN_OK) {
                reply.WriteInt32(verdict);
                reply.WriteString(reason);
            }
            return SHUYUAN_OK;
        }
        case AUDIT: {
            std::string record = data.ReadString();
            int32_t err = Audit(record);
            reply.WriteInt32(err);
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
