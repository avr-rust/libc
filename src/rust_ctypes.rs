pub type c_char = i8;
pub type c_schar = i8;
#[allow(dead_code)] pub type c_short = i16;
pub type c_int = i16;
pub type c_long = i32;
pub type c_longlong = i64;


pub type c_uchar = u8;
#[allow(dead_code)] pub type c_ushort = u16;
pub type c_uint = u16;
pub type c_ulong = u32;
pub type c_ulonglong = u64;

// Not C compliant.
#[allow(dead_code)]
pub type c_float = f32;
#[allow(dead_code)]
pub type c_double = f32;

#[repr(u8)]
pub enum c_void {
    // Two dummy variants so the #[repr] attribute can be used.
    #[doc(hidden)]
    __variant1,
    #[doc(hidden)]
    __variant2,
}

