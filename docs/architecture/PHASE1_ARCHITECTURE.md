# Phase 1 Architecture

## Scope

Phase 1 architecture focuses on four tracks:

1. JUCE core architecture
2. ConvertWithMoss integration strategy
3. Import/export validation for `.adv`, `.exs`, `.sfz`
4. AAX build path and cross-format build matrix

## Core Architecture (JUCE)

## Layered Model

1. Domain Layer
   - Project/session graph
   - Multisample program model
   - Region, key range, velocity layer, round-robin definitions
2. Engine Layer
   - Voice allocation
   - Sample playback and transport-time consistency
   - Mapping resolver (note/velocity/round-robin selection)
3. Adapter Layer
   - Format import/export adapters
   - Conversion normalization against internal schema
4. UI Layer
   - Editor interaction model, waveform/loop/mapping views
   - Strictly consumes domain/engine contracts

## Recommended Module Boundaries

- `Source/core/domain/*`
- `Source/core/engine/*`
- `Source/core/io/*`
- `Source/adapters/convertwithmoss/*`
- `Source/adapters/formats/*`
- `Source/ui/*`

These paths are target architecture and can be staged incrementally.

## Canonical Internal Schema

All imports normalize into one internal schema before playback or re-export:

- Program metadata
- Groups/layers
- Region map:
  - key low/high
  - velocity low/high
  - root key
  - round-robin index/group
  - sample path
  - loop metadata (start/end/crossfade)
- Playback modifiers (gain/pan/tune/envelope refs where available)

This schema is the single source of truth for export back to `.adv`/`.exs`/`.sfz`.

## ConvertWithMoss Integration Strategy

## Integration Style

- Use ConvertWithMoss as an external conversion stage, not as runtime business logic.
- Build an adapter service that:
  1. invokes converter pipeline
  2. parses output into canonical schema
  3. records unsupported fields and conversion warnings

## Adapter Contracts

- Input: source instrument/package path + declared format
- Output:
  - normalized internal schema artifact
  - conversion diagnostics (warnings/errors/known-loss tags)

## Determinism Requirement

Given identical input and converter version, normalized output must be stable byte-for-byte or semantically equivalent under canonical ordering.

## Import/Export Validation Plan (`.adv` / `.exs` / `.sfz`)

## Fixture Strategy

- Maintain golden fixtures per format in a dedicated fixtures directory
- Include simple, medium, and edge-case instruments:
  - overlapping key ranges
  - layered velocities
  - round robin
  - loop metadata present/missing

## Validation Pipeline

1. Import fixture -> normalize schema
2. Export from schema -> target format
3. Re-import exported file
4. Structural compare against expected canonical model

## Validation Metrics

- Mapping fidelity: key/velocity/root correctness
- Region count and layer integrity
- Loop metadata retention
- Round-robin retention
- Unsupported feature reporting completeness

## Pass/Fail Policy

- Hard fail on mapping correctness regressions
- Soft fail with warning on known unsupported opcode/feature gaps
- Report includes machine-readable diff summary per fixture

## AAX Path and Build Matrix

## Build Targets

- Standalone
- VST3
- AU
- AAX

## Matrix Dimensions

- Configuration: Debug, Release
- Platform: macOS (initial), Windows (planned lane)
- Target format: per above

## AAX Lane Requirements

- AAX SDK availability and version pin
- CMake option gating (`ENABLE_AAX`) with explicit error messages
- Separate CI/local lane so missing AAX prerequisites do not block non-AAX development

## Build Policy

- CMake is source of truth
- Agent-specific build dirs only (`build_codex`, `build_claude`)
- Phase 1 gate: at minimum Standalone/VST3/AU green, AAX lane documented and executable where SDK is present

## Autosampling + Loop Editor Milestones (Architecture-Aligned)

## M1: Autosampling Engine Skeleton

- Session planner for note/velocity sweeps
- Capture pipeline interfaces (internal plugin target first)
- File naming and region assignment strategy

## M2: Autosampling Hardware Extension

- External MIDI/audio device route abstraction
- Latency compensation and capture window controls

## M3: Loop Candidate Engine

- Candidate generation and ranking API
- Preview stepping (`<` / `>`) against ranked list

## M4: Loop Commit and Editor Integration

- Destructive loop crossfade print path
- Loop metadata write-back for WAV/FLAC
- UI integration with waveform editor controls

## Phase 1 Acceptance Checklist

1. Canonical schema and module boundaries documented and implemented as stubs/skeletons
2. ConvertWithMoss adapter interface merged with diagnostics contract
3. Validation harness for `.adv`/`.exs`/`.sfz` executes against initial fixture set
4. Build matrix documented; AAX prerequisites and lane behavior codified
5. No Gemini references in workflow or assignments
