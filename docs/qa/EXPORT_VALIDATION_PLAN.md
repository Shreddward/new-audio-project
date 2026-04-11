# Export Validation Plan

1. Validate required fields before serialization.
2. Deterministic output check (same input -> same bytes/text).
3. Re-parse exported file and assert structural validity.
4. Fixture tests for SFZ and ADV baseline outputs.
