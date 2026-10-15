.PHONY: test clean
# rustc --test, not cargo: one file, no Cargo.toml, no target/ directory in the
# repo. Debug build on purpose -- overflow checks are on, which is the point.
test: ; @rustc --test --edition 2021 -o /tmp/vpar_rust solution.rs && /tmp/vpar_rust
release: ; @rustc --test --edition 2021 -O -o /tmp/vpar_rust_rel solution.rs && /tmp/vpar_rust_rel
clean: ; @rm -f /tmp/vpar_rust /tmp/vpar_rust_rel
