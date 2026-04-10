# Agent Assignments (Codex + Claude)

## Team and Rules

Active agents:

- Codex
- Claude

Not used in this project:

- Gemini

Workflow rules:

1. Branches only `codex/*` or `claude/*`
2. PR-only merges into `main`
3. No direct commits to `main`
4. Build in isolated directories only:
   - `build_codex`
   - `build_claude`
5. Stop immediately on unexpected file changes

## Ownership Model for Phase 1

## Stream A: JUCE Core Architecture

Primary owner: Codex

Scope:

- `Source/PluginProcessor.*`
- Core engine/state modules under `Source/` as introduced
- `CMakeLists.txt` updates tied to architecture and target config
- Serialization/state schema contracts

Deliverables:

- Engine/module boundaries and state graph
- Playback/mapping core skeleton
- Build target wiring for core plugin formats

## Stream B: ConvertWithMoss Adapter + Validation Harness

Primary owner: Codex

Scope:

- Import/export adapter modules
- Fixture definitions and validation scripts
- Format contract docs

Deliverables:

- Normalized mapping schema
- Adapter interfaces for `.adv`/`.exs`/`.sfz`
- Fixture-based validation outputs and pass/fail criteria

## Stream C: Editor UX and Interaction Layer

Primary owner: Claude

Scope:

- `Source/PluginEditor.*`
- UI components for mapping view, waveform view, loop candidate controls
- Interaction flows for autosampling and loop editor milestones

Deliverables:

- UI shell aligned to engine contracts
- Editing workflows for Phase 2 milestones without backend contract drift

## Shared/Coordination Files

Require explicit handoff before editing:

- `CMakeLists.txt`
- `Source/PluginProcessor.*`
- `Source/PluginEditor.*`
- Any shared model header used by both DSP and UI layers

## Merge Order for Phase 1

1. `codex/phase1-juce-core-architecture`
2. `codex/phase1-conversion-validation`
3. `claude/phase1-editor-shell`

If Claude starts early, Claude should build against stable mock interfaces and avoid changing core engine contracts.

## Handoff Contract

Every handoff must include:

1. Branch name
2. Files changed
3. Public interfaces changed
4. Build/test commands run and result
5. Remaining gaps and blockers
