#ifndef SHUYUAN_LINGTAI_SERVICE_STUB_H
#define SHUYUAN_LINGTAI_SERVICE_STUB_H

#include "i_lingtai_service.h"
#include "iremote_stub.h"

namespace OHOS {
namespace Shuyuan {

/**
 * Stub：IPC 请求接收端。校验接口描述符后，按消息码分发到业务虚函数，
 * 具体业务由服务实现类 LingtaiService 完成。
 */
class LingtaiServiceStub : public IRemoteStub<ILingtaiService> {
public:
    int32_t OnRemoteRequest(uint32_t code, MessageParcel& data, MessageParcel& reply,
        MessageOption& option) override;
};

} // namespace Shuyuan
} // namespace OHOS

#endif // SHUYUAN_LINGTAI_SERVICE_STUB_H
