#!/usr/bin/env bash
# 阶段零 · 同步龙芯 LoongArch 版 OpenHarmony 源码
# 用法：./01-sync-source.sh [源码目录]
# 说明：manifest 与产品名来自公开移植组织 openharmony-loongarch（Gitee，ohos-main 分支）。
set -e

WORKDIR="${1:-openharmony_loongarch}"
mkdir -p "$WORKDIR"
cd "$WORKDIR"

# repo 工具优先使用系统安装版；若无则从 Gitee 取。
if ! command -v repo >/dev/null 2>&1; then
    mkdir -p "$HOME/bin"
    curl -s https://gitee.com/oschina/repo/raw/main/repo -o "$HOME/bin/repo"
    chmod +x "$HOME/bin/repo"
    export PATH="$HOME/bin:$PATH"
fi

repo init -u https://gitee.com/openharmony-loongarch/manifest.git \
    -b ohos-main -m loongarch.xml --no-repo-verify -v

repo sync -c
repo forall -c 'git lfs pull'

# 预编译二进制（SDK / 工具链）下载。
if [ -f "./build/prebuilts_download.sh" ]; then
    ./build/prebuilts_download.sh
else
    echo "[warn] 未找到 build/prebuilts_download.sh，请在源码树内确认预编译下载方式。"
fi

echo "[done] 源码同步完成，目录：$WORKDIR"
