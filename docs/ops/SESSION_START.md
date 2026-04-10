# Global Session Start

## Existing local repo
cd /Users/edwardbraillif/developer/audio/new-audio-project
git status
git branch --show-current
git fetch --all --prune
git pull --ff-only
./scripts/snapshot_repo.sh

## Start a new feature branch
git checkout -b codex/<task-name>
# or claude/<task-name>
# or gemini/<task-name>

## First-time clone
git clone --recurse-submodules https://github.com/Shreddward/new-audio-project.git /Users/edwardbraillif/developer/audio/new-audio-project
cd /Users/edwardbraillif/developer/audio/new-audio-project
