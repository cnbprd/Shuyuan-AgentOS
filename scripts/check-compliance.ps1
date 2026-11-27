# Copyright (c) 2026 枢元智能体操作系统 (Shuyuan AgentOS)
# SPDX-License-Identifier: Apache-2.0
#
# 仓库合规检查（Windows）：必需文件、SPDX 头、JSON、bundle 许可证、冲突标记。
$ErrorActionPreference = 'Stop'
Set-Location (Resolve-Path (Join-Path $PSScriptRoot '..'))

$fail = $false
function Fail([string]$Message) {
    Write-Host "FAIL: $Message"
    $script:fail = $true
}

$required = @(
    'LICENSE', 'NOTICE', 'THIRD_PARTY_NOTICES.md', 'README.md',
    'CONTRIBUTING.md', 'CODE_OF_CONDUCT.md', 'SECURITY.md', 'DCO'
)
foreach ($f in $required) {
    if (-not (Test-Path -LiteralPath $f)) { Fail "MISSING: $f" }
}

$exts = @('.h', '.cpp', '.gn', '.sh', '.te', '.rc', '.ps1')
$files = Get-ChildItem -LiteralPath 'src', 'scripts' -Recurse -File |
    Where-Object { $exts -contains $_.Extension.ToLower() }
$missing = 0
foreach ($f in $files) {
    if (-not (Select-String -LiteralPath $f.FullName -Pattern 'SPDX-License-Identifier: Apache-2.0' -SimpleMatch -Quiet)) {
        Fail "MISSING SPDX: $($f.FullName)"
        $missing++
    }
}
Write-Host "SPDX: $($files.Count - $missing)/$($files.Count)"

$jsonBad = 0
$jsonFiles = Get-ChildItem -LiteralPath 'src' -Recurse -File -Filter '*.json'
foreach ($f in $jsonFiles) {
    try {
        Get-Content -LiteralPath $f.FullName -Raw -Encoding UTF8 | ConvertFrom-Json | Out-Null
    } catch {
        Fail "BAD JSON: $($f.FullName)"
        $jsonBad++
    }
}
Write-Host "JSON: $jsonBad bad"

$bundles = Get-ChildItem -LiteralPath 'src' -Recurse -File -Filter 'bundle.json'
foreach ($f in $bundles) {
    try {
        $obj = Get-Content -LiteralPath $f.FullName -Raw -Encoding UTF8 | ConvertFrom-Json
        if ($obj.license -ne 'Apache-2.0') { Fail "BAD BUNDLE LICENSE: $($f.FullName)" }
    } catch {
        Fail "BAD BUNDLE JSON: $($f.FullName)"
    }
}

$conflictFiles = @(
    Get-ChildItem -LiteralPath 'src', 'scripts', '.github' -Recurse -File -ErrorAction SilentlyContinue
    Get-Item -LiteralPath 'README.md', 'CONTRIBUTING.md', 'CODE_OF_CONDUCT.md', 'SECURITY.md' -ErrorAction SilentlyContinue
)
foreach ($f in $conflictFiles) {
    $m = Select-String -LiteralPath $f.FullName -Pattern '^(<<<<<<<|>>>>>>>)' -ErrorAction SilentlyContinue
    if ($m) { Fail "CONFLICT MARKERS: $($f.FullName)" }
}

if ($fail) {
    Write-Host 'COMPLIANCE FAILED'
    exit 1
}
Write-Host 'COMPLIANCE OK'
