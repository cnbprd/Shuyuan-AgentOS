#include "jingzhi_service.h"
#include "hilog/log.h"

namespace OHOS {
namespace Shuyuan {

namespace {
constexpr OHOS::HiviewDFX::HiLogLabel LABEL = {LOG_CORE, 0xD001801, "ShuyuanJingzhi"};
}

REGISTER_SYSTEM_ABILITY_BY_ID(JingzhiService, JINGZHI_SA_ID, true);

JingzhiService::JingzhiService(int32_t saId, bool runOnCreate)
    : SystemAbility(saId, runOnCreate)
{
}

void JingzhiService::OnStart()
{
    HiLog::Info(LABEL, "JingzhiService::OnStart enter.");
    bool ret = Publish(this);
    if (!ret) {
        HiLog::Error(LABEL, "JingzhiService Publish to samgr failed.");
        return;
    }
    {
        std::lock_guard<std::mutex> lock(mutex_);
        ready_ = true;
    }
    HiLog::Info(LABEL, "JingzhiService published as SA %{public}d.", JINGZHI_SA_ID);
}

void JingzhiService::OnStop()
{
    HiLog::Info(LABEL, "JingzhiService::OnStop enter.");
    std::lock_guard<std::mutex> lock(mutex_);
    auditQueue_.clear();
}

int32_t JingzhiService::PreAuthorize(const std::string& subject, const std::string& action,
    int32_t& verdict, std::string& reason)
{
    if (action.empty()) {
        return SHUYUAN_ERR_INVALID_PARAM;
    }

    // 第一版占位静态策略：前缀匹配。策略配置化与审批流在后续版本接入。
    if (action.rfind("deny:", 0) == 0) {
        verdict = VERDICT_DENY;
        reason = "blocked by static deny rule";
    } else if (action.rfind("pending:", 0) == 0) {
        verdict = VERDICT_PENDING;
        reason = "requires approval";
    } else {
        verdict = VERDICT_ALLOW;
        reason = "static allow";
    }

    HiLog::Info(LABEL, "PreAuthorize subject=%{public}s verdict=%{public}d.",
        subject.c_str(), verdict);
    return SHUYUAN_OK;
}

int32_t JingzhiService::Audit(const std::string& record)
{
    if (record.empty()) {
        return SHUYUAN_ERR_INVALID_PARAM;
    }
    std::lock_guard<std::mutex> lock(mutex_);
    auditQueue_.push_back(record);
    auditCount_++;
    return SHUYUAN_OK;
}

int32_t JingzhiService::IsReady(bool& ready)
{
    std::lock_guard<std::mutex> lock(mutex_);
    ready = ready_;
    return SHUYUAN_OK;
}

} // namespace Shuyuan
} // namespace OHOS
