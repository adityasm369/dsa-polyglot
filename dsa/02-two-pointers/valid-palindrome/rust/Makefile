.PHONY: test clean
# rustc --test, not cargo: one file, no Cargo.toml, no target/ directory in the
# repo. Debug build on purpose -- overflow checks are on, which is the point.
test: ; @rustc --test --edition 2021 -o /tmp/vp_rust solution.rs && /tmp/vp_rust
release: ; @rustc --test --edition 2021 -O -o /tmp/vp_rust_rel solution.rs && /tmp/vp_rust_rel
clean: ; @rm -f /tmp/vp_rust /tmp/vp_rust_rel
