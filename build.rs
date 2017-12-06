use std::path::Path;
use std::process::Command;
use std::env;

const AVR_ARCH: &'static str = "avr6";

fn main() {
    let manifest_dir = Path::new(env!("CARGO_MANIFEST_DIR"));
    let libc_dir = manifest_dir.join("avr-libc");

    bootstrap(&libc_dir);
    configure(&libc_dir);
    make(&libc_dir, AVR_ARCH);
}

fn bootstrap(libc_dir: &Path) {
    println!("Bootstrapping avr-libc");

    let mut cmd = Command::new("sh");
    cmd.arg("bootstrap");

    cmd.current_dir(libc_dir);
    println!("{:?}", cmd);

    if !cmd.status().expect("failed to bootstrap avr-libc").success() {
        panic!("failed to bootstrap");
    }
}

fn configure(libc_dir: &Path) {
    println!("Configuring avr-libc");

    let target = env::var("TARGET").unwrap();;

    let mut cmd = Command::new("sh");
    cmd.arg("configure");
    cmd.arg(&format!("--build={}", target));
    cmd.arg("--host=avr");

    cmd.env("CC", "avr-gcc");

    cmd.current_dir(libc_dir);
    println!("{:?}", cmd);

    if !cmd.status().expect("failed to configure avr-libc").success() {
        panic!("failed to configure");
    }
}

fn make(libc_dir: &Path, avr_arch: &str) {
    println!("Making avr-libc");

    let arch_dir = libc_dir.join("avr").join("lib").join(avr_arch);

    let mut cmd = Command::new("make");
    cmd.current_dir(&arch_dir);
    println!("{:?}", cmd);

    if !cmd.status().expect("failed to compile avr-libc").success() {
        panic!("failed to make");
    }
}

