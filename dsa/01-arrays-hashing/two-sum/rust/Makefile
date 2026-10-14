.PHONY: test clean
# rustc --test, not cargo: one file, no Cargo.toml, no target/ directory in the
# repo. Debug build on purpose -- overflow checks are on, which is the point.
test: ; @rustc --test --edition 2021 -o /tmp/ts_rust solution.rs && /tmp/ts_rust
release: ; @rustc --test --edition 2021 -O -o /tmp/ts_rust_rel solution.rs && /tmp/ts_rust_rel
clean: ; @rm -f /tmp/ts_rust /tmp/ts_rust_rel
