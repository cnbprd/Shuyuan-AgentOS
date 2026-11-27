#ifndef SHUYUAN_JIANGUAN_SERVICE_STUB_H
#define SHUYUAN_JIANGUAN_SERVICE_STUB_H

#include "i_jianguan_service.h"
#include "iremote_stub.h"

namespace OHOS {
namespace Shuyuan {

class JianguanServiceStub : public IRemoteStub<IJianguanService> {
public:
    int32_t OnRemoteRequest(uint32_t code, MessageParcel& data, MessageParcel& reply,
        MessageOption& option) override;
};

} // namespace Shuyuan
} // namespace OHOS

#endif // SHUYUAN_JIANGUAN_SERVICE_STUB_H
