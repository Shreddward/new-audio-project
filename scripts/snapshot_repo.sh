#!/usr/bin/env bash
set -euo pipefail

if ! git rev-parse --is-inside-work-tree >/dev/null 2>&1; then
  echo "Run inside a git repo"
  exit 1
fi

BACKUP_ROOT="/Users/edwardbraillif/developer/_backups"
REPO_NAME="$(basename "$(git rev-parse --show-toplevel)")"
STAMP="$(date +%Y%m%d-%H%M%S)"

mkdir -p "$BACKUP_ROOT/$REPO_NAME"

git add -A
git commit -m "snapshot: $STAMP" --allow-empty >/dev/null 2>&1 || true
git tag -f "snapshot-$STAMP" >/dev/null 2>&1 || true
git bundle create "$BACKUP_ROOT/$REPO_NAME/$REPO_NAME-$STAMP.bundle" --all

echo "Created: $BACKUP_ROOT/$REPO_NAME/$REPO_NAME-$STAMP.bundle"
