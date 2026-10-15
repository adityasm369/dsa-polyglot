.PHONY: test clean
# rustc --test, not cargo: one file, no Cargo.toml, no target/ directory in the
# repo. Debug build on purpose -- overflow checks are on, which is the point.
test: ; @rustc --test --edition 2021 -o /tmp/cs_rust solution.rs && /tmp/cs_rust
release: ; @rustc --test --edition 2021 -O -o /tmp/cs_rust_rel solution.rs && /tmp/cs_rust_rel
clean: ; @rm -f /tmp/cs_rust /tmp/cs_rust_rel
