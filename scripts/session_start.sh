#!/usr/bin/env bash
set -euo pipefail

expected_repo="/Users/edwardbraillif/developer/audio/new-audio-project"
prefix_regex='^(main|codex/.+|claude/.+)$'

cwd="$(pwd)"
branch="$(git rev-parse --abbrev-ref HEAD)"
remote="$(git remote get-url origin 2>/dev/null || echo 'no-origin')"

echo "cwd: $cwd"
echo "branch: $branch"
echo "origin: $remote"

[[ "$cwd" == "$expected_repo" ]] || { echo "ERROR: wrong repo path"; exit 1; }
[[ "$branch" =~ $prefix_regex ]] || { echo "ERROR: wrong branch prefix for audio"; exit 1; }

echo "OK: audio session context is valid."
