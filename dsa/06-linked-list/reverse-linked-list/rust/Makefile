.PHONY: test clean
# rustc --test, not cargo: one file, no Cargo.toml, no target/ directory in the
# repo. Debug build on purpose -- overflow checks are on, which is the point.
test: ; @rustc --test --edition 2021 -o /tmp/rl_rust solution.rs && /tmp/rl_rust
release: ; @rustc --test --edition 2021 -O -o /tmp/rl_rust_rel solution.rs && /tmp/rl_rust_rel
clean: ; @rm -f /tmp/rl_rust /tmp/rl_rust_rel
