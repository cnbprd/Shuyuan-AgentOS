#ifndef SHUYUAN_LINGZHONG_SERVICE_STUB_H
#define SHUYUAN_LINGZHONG_SERVICE_STUB_H

#include "i_lingzhong_service.h"
#include "iremote_stub.h"

namespace OHOS {
namespace Shuyuan {

class LingzhongServiceStub : public IRemoteStub<ILingzhongService> {
public:
    int32_t OnRemoteRequest(uint32_t code, MessageParcel& data, MessageParcel& reply,
        MessageOption& option) override;
};

} // namespace Shuyuan
} // namespace OHOS

#endif // SHUYUAN_LINGZHONG_SERVICE_STUB_H
