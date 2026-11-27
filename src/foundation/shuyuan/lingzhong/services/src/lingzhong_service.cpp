/*
 * Copyright (c) 2026 枢元智能体操作系统 (Shuyuan AgentOS)
 * SPDX-License-Identifier: Apache-2.0
 */
#include "lingzhong_service.h"
#include "hilog/log.h"

namespace OHOS {
namespace Shuyuan {

namespace {
constexpr OHOS::HiviewDFX::HiLogLabel LABEL = {LOG_CORE, 0xD001804, "ShuyuanLingzhong"};
}

REGISTER_SYSTEM_ABILITY_BY_ID(LingzhongService, LINGZHONG_SA_ID, true);

LingzhongService::LingzhongService(int32_t saId, bool runOnCreate)
    : SystemAbility(saId, runOnCreate)
{
}

void LingzhongService::OnStart()
{
    HiLog::Info(LABEL, "LingzhongService::OnStart enter.");
    bool ret = Publish(this);
    if (!ret) {
        HiLog::Error(LABEL, "LingzhongService Publish to samgr failed.");
        return;
    }
    {
        std::lock_guard<std::mutex> lock(mutex_);
        ready_ = true;
    }
    HiLog::Info(LABEL, "LingzhongService published as SA %{public}d.", LINGZHONG_SA_ID);
}

void LingzhongService::OnStop()
{
    HiLog::Info(LABEL, "LingzhongService::OnStop enter.");
    std::lock_guard<std::mutex> lock(mutex_);
    taskState_.clear();
}

int32_t LingzhongService::AttachTask(const std::string& taskId)
{
    if (taskId.empty()) {
        return SHUYUAN_ERR_INVALID_PARAM;
    }
    std::lock_guard<std::mutex> lock(mutex_);
    if (taskState_.find(taskId) == taskState_.end()) {
        taskState_[taskId] = "attached";
    }
    return SHUYUAN_OK;
}

int32_t LingzhongService::FinishTask(const std::string& taskId, const std::string& result,
    std::string& finalState)
{
    std::lock_guard<std::mutex> lock(mutex_);
    auto it = taskState_.find(taskId);
    if (it == taskState_.end()) {
        return SHUYUAN_ERR_NOT_FOUND;
    }
    it->second = "done";
    finalState = "done";
    HiLog::Info(LABEL, "Task %{public}s finished, result length=%{public}zu.",
        taskId.c_str(), result.size());
    return SHUYUAN_OK;
}

int32_t LingzhongService::GetTaskFinalState(const std::string& taskId, std::string& state)
{
    std::lock_guard<std::mutex> lock(mutex_);
    auto it = taskState_.find(taskId);
    if (it == taskState_.end()) {
        return SHUYUAN_ERR_NOT_FOUND;
    }
    state = it->second;
    return SHUYUAN_OK;
}

int32_t LingzhongService::IsReady(bool& ready)
{
    std::lock_guard<std::mutex> lock(mutex_);
    ready = ready_;
    return SHUYUAN_OK;
}

} // namespace Shuyuan
} // namespace OHOS
