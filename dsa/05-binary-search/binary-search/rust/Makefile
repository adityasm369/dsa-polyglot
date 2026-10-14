.PHONY: test clean
# rustc --test, not cargo: one file, no Cargo.toml, no target/ directory in the
# repo. Debug build on purpose -- overflow checks are on, which is the point.
test: ; @rustc --test --edition 2021 -o /tmp/bs_rust solution.rs && /tmp/bs_rust
release: ; @rustc --test --edition 2021 -O -o /tmp/bs_rust_rel solution.rs && /tmp/bs_rust_rel
clean: ; @rm -f /tmp/bs_rust /tmp/bs_rust_rel
