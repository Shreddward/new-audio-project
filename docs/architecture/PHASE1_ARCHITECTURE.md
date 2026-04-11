# Phase 1 Architecture

## Layers
- Core: domain models
- Engine: runtime-safe playback structures
- Export: format adapters
- Validation: schema/content checks
- UI: editor and interaction

## Safety
- No file IO/alloc/locks on audio thread
- Message-thread handoff for editor actions
