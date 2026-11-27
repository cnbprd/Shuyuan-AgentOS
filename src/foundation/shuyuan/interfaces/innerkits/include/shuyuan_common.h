/*
 * Copyright (c) 2026 枢元智能体操作系统 (Shuyuan Agent OS)
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef SHUYUAN_COMMON_H
#define SHUYUAN_COMMON_H

#include <cstdint>

namespace OHOS {
namespace Shuyuan {

// 枢元统一错误码（公共）。各层接口、服务与测试客户端共用同一份定义，
// 避免在多个头文件中重复定义导致聚合 include 时重定义冲突。
// inline constexpr（C++17）保证多编译单元内同一定义，不产生链接重复符号。
inline constexpr int32_t SHUYUAN_OK = 0;
inline constexpr int32_t SHUYUAN_ERR_IPC = -1;
inline constexpr int32_t SHUYUAN_ERR_NOT_FOUND = -2;
inline constexpr int32_t SHUYUAN_ERR_INVALID_PARAM = -3;

// 就绪里程碑参数名（与 04-启动时序-载阳.md 第 3 节对齐）。
// 参数前缀规范（sys./persist.）与写入 API（SetParameter 等）以真实源码树为准，待核实。
inline constexpr const char* PARAM_JINGZHI_READY = "sys.shuyuan.jingzhi.ready";
inline constexpr const char* PARAM_LINGTAI_READY = "sys.shuyuan.lingtai.ready";
inline constexpr const char* PARAM_JIANGUAN_READY = "sys.shuyuan.jianguan.ready";
inline constexpr const char* PARAM_HEMING_READY = "sys.shuyuan.heming.ready";
inline constexpr const char* PARAM_LINGZHONG_READY = "sys.shuyuan.lingzhong.ready";
inline constexpr const char* PARAM_BOOT_COMPLETE = "sys.shuyuan.boot.complete";

} // namespace Shuyuan
} // namespace OHOS

#endif // SHUYUAN_COMMON_H
