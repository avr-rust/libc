#! /bin/sh -ea

TEMP_CHECKOUT_NAME=avr-libc.new.in-progress

SCRIPT_DIR=$(dirname $0)
cd "${SCRIPT_DIR}"

echo "Checking out the most recent avr-libc"
svn co svn://svn.savannah.nongnu.org/avr-libc/trunk "${TEMP_CHECKOUT_NAME}"

echo "Moving the old libc to a temporary directory"
mv avr-libc avr-libc.old

echo "Moving the new libc to the avr-libc directory"
mv "${TEMP_CHECKOUT_NAME}/avr-libc" "avr-libc"
rm -rf "${TEMP_CHECKOUT_NAME}"

echo "Cleaning up the old avr-libc sources"
rm -rf avr-libc.old
