#ifndef SHUYUAN_HEMING_SERVICE_STUB_H
#define SHUYUAN_HEMING_SERVICE_STUB_H

#include "i_heming_service.h"
#include "iremote_stub.h"

namespace OHOS {
namespace Shuyuan {

class HemingServiceStub : public IRemoteStub<IHemingService> {
public:
    int32_t OnRemoteRequest(uint32_t code, MessageParcel& data, MessageParcel& reply,
        MessageOption& option) override;
};

} // namespace Shuyuan
} // namespace OHOS

#endif // SHUYUAN_HEMING_SERVICE_STUB_H
