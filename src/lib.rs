//! Rust bindings to [avr-libc](http://www.nongnu.org/avr-libc/).
//!
//! When compiled with the avr-rust compiler, the libc bindings in this crate
//! automatically pick up the right mcu-specific headers depending on what
//! cpu is specified in the target specification file.
//!
//! This means that on different microcontrollers, this crate will have a different
//! public API. In general, most functions are the same across all chips. Many
//! constants however are device-specific.

#![no_std]

#![allow(non_camel_case_types, non_upper_case_globals)]

// bindgen uses 'int' for preprocessor defines which causes
// overflowing literal warnings.
// avr-rust/libc#1
#![allow(overflowing_literals)]

pub use self::bindings::*;

mod bindings;
mod rust_ctypes;

