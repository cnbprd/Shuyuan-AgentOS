#!/usr/bin/env bash
# Copyright (c) 2026 枢元智能体操作系统 (Shuyuan Agent OS)
# SPDX-License-Identifier: Apache-2.0
#
# 仓库合规检查：必需文件、SPDX 头、JSON、bundle 许可证、冲突标记。
set -euo pipefail

cd "$(dirname "$0")/.."

fail=0
required=(LICENSE NOTICE THIRD_PARTY_NOTICES.md README.md CONTRIBUTING.md CODE_OF_CONDUCT.md SECURITY.md DCO)
for f in "${required[@]}"; do
    if [ ! -f "$f" ]; then
        echo "MISSING: $f"
        fail=1
    fi
done

mapfile -t files < <(find src scripts -type f \( -name '*.h' -o -name '*.cpp' -o -name '*.gn' -o -name '*.sh' -o -name '*.te' -o -name '*.rc' -o -name '*.ps1' \) | sort)
count=${#files[@]}
missing=0
for f in "${files[@]}"; do
    if ! grep -q 'SPDX-License-Identifier: Apache-2.0' "$f"; then
        echo "MISSING SPDX: $f"
        missing=$((missing + 1))
        fail=1
    fi
done
echo "SPDX: $((count - missing))/$count"

json_bad=0
while IFS= read -r -d '' f; do
    if ! python3 -c 'import json,sys; json.load(open(sys.argv[1], encoding="utf-8"))' "$f" 2>/dev/null; then
        echo "BAD JSON: $f"
        json_bad=$((json_bad + 1))
        fail=1
    fi
done < <(find src -type f -name '*.json' -print0)
echo "JSON: $json_bad bad"

while IFS= read -r -d '' f; do
    if ! python3 - "$f" <<'PY'
import json
import sys

with open(sys.argv[1], encoding="utf-8") as fp:
    data = json.load(fp)
assert data.get("license") == "Apache-2.0", data.get("license")
PY
    then
        echo "BAD BUNDLE LICENSE: $f"
        fail=1
    fi
done < <(find src -type f -name 'bundle.json' -print0)

if grep -RInE '^(<<<<<<<|>>>>>>>)' src scripts .github README.md CONTRIBUTING.md CODE_OF_CONDUCT.md SECURITY.md 2>/dev/null; then
    echo "CONFLICT MARKERS FOUND"
    fail=1
fi

if [ "$fail" -ne 0 ]; then
    echo "COMPLIANCE FAILED"
    exit 1
fi
echo "COMPLIANCE OK"
