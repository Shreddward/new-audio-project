# CONTEXT_HANDOFF

## Goal
Rebuild Liaison from scratch as a professional multisample editor/sampler in:
`/Users/edwardbraillif/developer/audio/new-audio-project`

## Current Status
- New safe workspace established under `/Users/edwardbraillif/developer`
- Fresh repo created and pushed: `https://github.com/Shreddward/new-audio-project`
- Session safety docs added (`AGENT_RUNTIME_RULES.md`, `AGENT_PROMPT_TEMPLATE.md`, `SESSION_START.md`)
- JUCE/CMake scaffold and first performance scaffold implemented successfully
- Working branch started: `codex/feature-performance-scaffold`

## Hard Constraints
- Never commit directly to `main`
- Branch namespaces: `codex/*`, `claude/*` only
- Build dirs: `build_codex`, `build_claude` only
- No destructive commands without explicit approval
- Stop on unexpected file changes
- Commit small and push frequently

## Product Requirements (High-Level)
- AAX support ASAP + VST3/AU/Standalone
- Multisample editor + mapping engine
- Internal third-party plugin autosampling + external hardware autosampling (MIDI/audio) + CV protocol roadmap
- Record directly into assigned key/note regions
- Built-in tuner + auto pitch detect + auto note assignment option
- Waveform editor with Samples/Time/Bars + conventional zoom/pan
- Computer keyboard MIDI (A-L notes, Z/X octave, C/V velocity)
- Round robin + velocity layer capture (independent or simultaneous)
- Recording templates (drums/plucked/sustained)
- Batch processing/export with master channel strip + automation lanes
- ConvertWithMoss integration + converter fixture tests
- SFZ export compatibility for Serum 2.0.16 opcode coverage
- Sample-accurate loop finder algorithm with ranked candidates and `<` `>` stepping
- Destructive loop crossfade print and WAV/FLAC loop metadata writing
- GoldWave-style editing parity
- Avoid stock/vibecode UI feel

## External References
- ConvertWithMoss: https://github.com/git-moss/ConvertWithMoss
- GM Percussion map reference:
  https://musescore.org/sites/musescore.org/files/General%20MIDI%20Standard%20Percussion%20Set%20Key%20Map.pdf

## Immediate Next Task
Produce P0/P1/P2 implementation plan with codex/claude ownership and first PR slice:
AAX build + core state model + mapping playback + record-to-key + tuner/pitch-detect skeleton.

## Open Decisions
- Final product name TBD (keep internal ID stable, display name can change later)
- Exact plugin/codesigning release policy to finalize after core rebuild stabilizes
