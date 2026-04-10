# Multi-Agent Workflow

- Default branch protection: no direct force-push to `main`.
- Each agent works on its own branch namespace.
- Each agent builds only in its own build directory.
- Merge only after local build and smoke test pass.
- If unexpected file changes appear, stop and review before continuing.
