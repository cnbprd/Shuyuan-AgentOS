#ifndef SHUYUAN_LINGTAI_SERVICE_H
#define SHUYUAN_LINGTAI_SERVICE_H

#include "lingtai_service_stub.h"
#include "system_ability.h"
#include <map>
#include <mutex>
#include <string>

namespace OHOS {
namespace Shuyuan {

/**
 * 灵台服务实现类：继承 SystemAbility 与 Stub。
 * 第一版为内存态注册表与任务表，不做持久化、不做推理循环；
 * 推理由外部 Agent 运行时进程承载，灵台只负责路由、登记与状态收口。
 */
class LingtaiService : public SystemAbility, public LingtaiServiceStub {
    DECLARE_SYSTEM_ABILITY(LingtaiService);

public:
    explicit LingtaiService(int32_t saId, bool runOnCreate);
    ~LingtaiService() override = default;

    void OnStart() override;
    void OnStop() override;

    int32_t RegisterAgent(const std::string& name, const std::string& capabilities,
        std::string& agentId) override;
    int32_t UnregisterAgent(const std::string& agentId) override;
    int32_t SubmitIntent(const std::string& intent, const std::string& contextRef,
        std::string& taskId) override;
    int32_t GetTaskStatus(const std::string& taskId, std::string& status) override;
    int32_t IsReady(bool& ready) override;
    int32_t GetBootStatus(std::string& status) override;

private:
    std::mutex mutex_;
    std::map<std::string, std::string> agentRegistry_; // agentId -> 能力描述
    std::map<std::string, std::string> taskStatus_;    // taskId -> 状态
    int32_t agentSeq_ = 0;
    int32_t taskSeq_ = 0;
    bool ready_ = false;
};

} // namespace Shuyuan
} // namespace OHOS

#endif // SHUYUAN_LINGTAI_SERVICE_H
