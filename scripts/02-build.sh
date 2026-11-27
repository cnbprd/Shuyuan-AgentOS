#!/usr/bin/env bash
# 阶段零/一 · 编译入口
# 用法：
#   ./02-build.sh [产品名] [build-target]
# 产品名（2026-11-27 依 manifest 与 vendor 仓实证）：
#   qemu-loongarch64-linux-min  最小虚拟机镜像（vendor/ohemu，board=device/qemu/loongarch64_virt/linux）
#   ls3a5000@loongson           3A5000/3A6000 7A 系列主板 PC 镜像（vendor/loongson，product_name=ls3a5000）
# 注意：公开仓内不存在 loongpc 这个产品名，也没有 3A6000 独立板级目录。
# 未传 build-target 时编译整包；传入部件名时只编对应目标（目标名以源码树为准）。
set -e

PRODUCT="${1:-qemu-loongarch64-linux-min}"
TARGET="${2:-}"

if [ -n "$TARGET" ]; then
    ./build.sh --product-name "$PRODUCT" --ccache \
        --build-target "$TARGET" \
        --gn-args ohos_extra_cppflags="-Wno-format"
else
    ./build.sh --product-name "$PRODUCT" --ccache \
        --gn-args ohos_extra_cppflags="-Wno-format"
fi

echo "[done] 编译结束，产品：$PRODUCT"
