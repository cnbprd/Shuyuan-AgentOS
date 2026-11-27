/*
 * Copyright (c) 2026 枢元智能体操作系统 (Shuyuan Agent OS)
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef SHUYUAN_JINGZHI_SERVICE_STUB_H
#define SHUYUAN_JINGZHI_SERVICE_STUB_H

#include "i_jingzhi_service.h"
#include "iremote_stub.h"

namespace OHOS {
namespace Shuyuan {

class JingzhiServiceStub : public IRemoteStub<IJingzhiService> {
public:
    int32_t OnRemoteRequest(uint32_t code, MessageParcel& data, MessageParcel& reply,
        MessageOption& option) override;
};

} // namespace Shuyuan
} // namespace OHOS

#endif // SHUYUAN_JINGZHI_SERVICE_STUB_H
