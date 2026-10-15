.PHONY: test clean
# rustc --test, not cargo: one file, no Cargo.toml, no target/ directory in the
# repo. Debug build on purpose -- overflow checks are on, which is the point.
test: ; @rustc --test --edition 2021 -o /tmp/llc_rust solution.rs && /tmp/llc_rust
release: ; @rustc --test --edition 2021 -O -o /tmp/llc_rust_rel solution.rs && /tmp/llc_rust_rel
clean: ; @rm -f /tmp/llc_rust /tmp/llc_rust_rel
