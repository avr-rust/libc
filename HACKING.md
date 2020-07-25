# Tips on working with this project

Install nightly Rust

Building directly:

```rust
cargo build --target avr-atmega328p.json -Z build-std=core
```

# Generate documentation

```bash
cargo doc --target avr-atmega328
```
