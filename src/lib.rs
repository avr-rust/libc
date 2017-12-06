#![no_std]

#![allow(non_camel_case_types, non_upper_case_globals)]

// bindgen uses 'int' for preprocessor defines which causes
// overflowing literal warnings.
// avr-rust/libc#1
#![allow(overflowing_literals)]

pub use self::bindings::*;

mod bindings;
mod rust_ctypes;

