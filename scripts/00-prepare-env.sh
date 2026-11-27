#!/usr/bin/env bash
# Copyright (c) 2026 枢元智能体操作系统 (Shuyuan AgentOS)
# SPDX-License-Identifier: Apache-2.0
# 阶段零 · 宿主编译环境准备（Ubuntu 22.04 / WSL2）
# 注意：本脚本在 Linux 宿主或 WSL2 内执行，不要在 Windows PowerShell 直接运行。
# 依赖清单为 OpenHarmony 通用编译基线；具体版本与补充包以官方文档为准（待核实项见 07 手册第 7 节）。
set -e

export DEBIAN_FRONTEND=noninteractive

apt-get update
apt-get install -y \
    binutils \
    git \
    git-lfs \
    flex \
    bison \
    ccache \
    python3-pip \
    python3-venv \
    device-tree-compiler \
    repo \
    build-essential \
    ninja-build \
    wget \
    curl \
    openjdk-17-jdk-headless

git lfs install

# OpenHarmony 构建工具 hb：通常随源码 build 目录提供；
# 若需独立安装，包名与命令以官方文档为准，此处不写死，避免装错。
echo "[info] hb 构建工具请按 OpenHarmony 官方文档方式配置（待核实）。"

echo "[done] 宿主基础依赖安装完成。"
