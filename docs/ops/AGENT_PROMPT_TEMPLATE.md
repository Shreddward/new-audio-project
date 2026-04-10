# Agent Prompt Templates

Use at task start and agent handoff.

## Codex
Repo: /Users/edwardbraillif/developer/audio/new-audio-project
Branch: codex/<task-name>
Build dir: build_codex

## Claude
Repo: /Users/edwardbraillif/developer/audio/new-audio-project
Branch: claude/<task-name>
Build dir: build_claude

## Gemini
Repo: /Users/edwardbraillif/developer/audio/new-audio-project
Branch: gemini/<task-name>
Build dir: build_gemini

Shared rules:
- Never commit directly to main.
- No destructive commands without explicit approval.
- Stop if unexpected file changes appear.
- Commit small and push often.
- Run ./scripts/snapshot_repo.sh before major refactors.
