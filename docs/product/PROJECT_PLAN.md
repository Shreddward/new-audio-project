# New Audio Project - Project Plan

## Mission

Rebuild a Liaison-style professional multisample editor/sampler from first principles in JUCE with first-class support for:

- Plugin formats: VST3, AU, AAX, Standalone
- Library conversion and interchange: ConvertWithMoss, `.adv`, `.exs`, `.sfz`
- Core workflows: autosampling, mapping, playback, loop editing, export

Constraints:

- Branches only: `codex/*`, `claude/*`
- PR-only workflow
- No Gemini agent in this project

## Product Pillars

1. Fast, deterministic sampling workflows
2. Accurate mapping and playback behavior
3. Reliable import/export and round-trip conversion validation
4. Professional editing UX for loop and waveform operations
5. Production-safe plugin build and packaging path, including AAX

## Phase Plan

## P0: Foundation and Build Reliability

Objectives:

- Stabilize JUCE project architecture and module boundaries
- Establish build matrix and CI/local build conventions
- Land first playable sampler path with deterministic state model

Deliverables:

- Core domain model for project/session, multisample regions, velocity layers, round robin
- Engine skeleton for sample playback and voice allocation
- Deterministic serialization baseline for project data
- Build targets compiling for Standalone/VST3/AU, and AAX path scaffolded

Exit Criteria:

- Clean compile in primary local environments
- Smoke playback works from minimal mapped sample set
- Baseline tests for state serialization and engine invariants

## P1: Import/Export and Conversion Integrity

Objectives:

- Integrate ConvertWithMoss as controlled converter pipeline
- Implement import/export validation harness for `.adv`, `.exs`, `.sfz`
- Define fidelity scoring and known-loss reporting

Deliverables:

- Conversion adapter layer and normalized internal mapping schema
- Golden fixture library for each format
- Validation reports: mapping, root key, key range, velocity splits, loop metadata
- SFZ export coverage matrix for target opcode subset

Exit Criteria:

- Repeatable conversions with deterministic output
- Fixture-based pass/fail reports stored per commit/PR run
- Documented known gaps per format

## P2: Autosampling and Loop Editor MVP

Objectives:

- Deliver guided autosampling flows (plugin + external hardware path)
- Implement loop discovery, candidate ranking, and destructive loop crossfade print
- Ship editor interactions needed for production sampling sessions

Deliverables:

- Autosampling session controller (MIDI note stepping, capture rules, naming)
- Round-robin and velocity capture templates
- Loop candidate engine + audition controls + commit-to-file operations
- Waveform editor with zoom/pan and sample/time domain controls

Exit Criteria:

- End-to-end autosample session produces usable mapped instrument
- Loop editing path supports candidate stepping, preview, and commit
- Resulting assets export correctly through supported interchange paths

## Phase 1 (Immediate Execution Slice)

Phase 1 combines P0 + P1 baseline slices needed to de-risk architecture and format interoperability early.

In Scope:

1. JUCE core architecture baseline
2. ConvertWithMoss integration strategy + adapter skeleton
3. Import/export validation harness for `.adv`, `.exs`, `.sfz`
4. AAX path definition and practical build matrix

Out of Scope for this slice:

- Full autosampling UX
- Full loop editor UX
- Deep DSP enhancement beyond playback/mapping correctness

## Risks and Controls

1. AAX toolchain complexity and signing constraints
   - Control: treat AAX as tracked build lane with explicit prerequisites and non-blocking fallback when unavailable
2. Format conversion ambiguities across `.adv`/`.exs`/`.sfz`
   - Control: normalized schema + fixture-driven diff reports
3. Hidden drift between import/output contracts and engine behavior
   - Control: contract tests at adapter boundary and playback verification tests
4. Parallel agent collisions
   - Control: strict file ownership and handoff protocol

## Definition of Done for Phase 1

- Core architecture docs and module boundaries are implemented in repo structure
- Conversion adapter skeleton in place with initial fixtures and validation scripts
- `.adv`/`.exs`/`.sfz` validation plan codified and test harness runnable
- Build matrix documented with explicit AAX lane status and prerequisites
- Branches merged by PR only with passing local validation gates
