# Agent Runtime Rules

1. Never commit directly to `main`.
2. Use one branch namespace per agent:
- `codex/*`
- `claude/*`
- `gemini/*`
3. Use isolated build directories only:
- `build_codex`
- `build_claude`
- `build_gemini`
4. Run `./scripts/snapshot_repo.sh` before major refactors.
5. Never run destructive commands (`rm -rf`, `git reset --hard`, `git checkout --`) unless explicitly approved.
6. If unexpected file changes appear, stop and ask before continuing.
7. Commit small, focused changes and push frequently.
8. Open PRs into `main`; require review before merge.
9. Keep dependency versions pinned and documented in `docs/ops/DEPENDENCIES.md`.
10. End each work session with:
- `git status`
- push current branch
- short note in `docs/ops/` if recovery context is needed
