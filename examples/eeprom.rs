//! A persistent number counter.
//!
//! Chose random numbers in a loop until we have chosen 1000 odd numbers.
//! If the device is reset it will continue, keeping track of the previous number
//! of odd numbers.

#![no_std]
#![no_main]

#![feature(lang_items, unwind_attributes)]

extern crate avr_libc;

use avr_libc::{eeprom_read_dword, eeprom_write_dword, random};

#[no_mangle]
pub extern fn main() {
    let mut failed_attempts = load_failed_attempts();

    while failed_attempts < 1000 {
        // odd numbers are bad
        if unsafe { random() } & 0b1 == 0b1 {
            failed_attempts += 1;
        }

        save_failed_attempts(failed_attempts);
    }
}

fn load_failed_attempts() -> u32 {
    unsafe {
        let addr = 12 as *mut u32; // chosen arbitrarily
        eeprom_read_dword(addr)
    }
}

fn save_failed_attempts(attempts: u32) {
    unsafe {
        let addr = 12 as *mut u32; // chosen arbitrarily
        eeprom_write_dword(addr, attempts);
    }
}

// These do not need to be in a module, but we group them here for clarity.
pub mod std {
    #[lang = "eh_personality"]
    #[no_mangle]
    pub unsafe extern "C" fn rust_eh_personality(_state: (), _exception_object: *mut (), _context: *mut ()) -> () {
    }

    #[lang = "panic_fmt"]
    #[unwind]
    pub extern fn rust_begin_panic(_msg: (), _file: &'static str, _line: u32) -> ! {
        loop { }
    }
}

