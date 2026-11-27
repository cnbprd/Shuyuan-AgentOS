#include "heming_service_proxy.h"
#include "message_parcel.h"
#include "message_option.h"

namespace OHOS {
namespace Shuyuan {

HemingServiceProxy::HemingServiceProxy(const sptr<IRemoteObject>& impl)
    : IRemoteProxy<IHemingService>(impl)
{
}

int32_t HemingServiceProxy::DispatchPlan(const std::string& planId, const std::string& steps,
    std::string& collabId)
{
    MessageParcel data;
    MessageParcel reply;
    MessageOption option;
    if (!data.WriteInterfaceToken(GetDescriptor())) {
        return SHUYUAN_ERR_IPC;
    }
    data.WriteString(planId);
    data.WriteString(steps);

    int32_t error = Remote()->SendRequest(DISPATCH_PLAN, data, reply, option);
    if (error != ERR_NONE) {
        return SHUYUAN_ERR_IPC;
    }
    int32_t err = reply.ReadInt32();
    if (err == SHUYUAN_OK) {
        collabId = reply.ReadString();
    }
    return err;
}

int32_t HemingServiceProxy::GetCollabStatus(const std::string& collabId, std::string& status)
{
    MessageParcel data;
    MessageParcel reply;
    MessageOption option;
    if (!data.WriteInterfaceToken(GetDescriptor())) {
        return SHUYUAN_ERR_IPC;
    }
    data.WriteString(collabId);

    int32_t error = Remote()->SendRequest(GET_COLLAB_STATUS, data, reply, option);
    if (error != ERR_NONE) {
        return SHUYUAN_ERR_IPC;
    }
    int32_t err = reply.ReadInt32();
    if (err == SHUYUAN_OK) {
        status = reply.ReadString();
    }
    return err;
}

int32_t HemingServiceProxy::IsReady(bool& ready)
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
