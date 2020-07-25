#! /bin/sh -ea

# This script can be used to export the API documentation to HTML format and push the
# artifacts to the GitHub 'gh-pages' branch.

BOOK_DIR=$(dirname $0)
TARGET_BRANCH=gh-pages

function note() {
  echo "[note]: $@"
}

cd "${BOOK_DIR}"

repository_url=$(git remote get-url origin)
staging_dir=$(mktemp -qd)
staging_dir2=$(mktemp -qd)

note "created staging directories at '$staging_dir' and '$staging_dir2'"

note "generating docs"
cargo doc --target-dir "${staging_dir2}" --target avr-atmega328p.json -Z build-std=core
cp -r ${staging_dir2}/avr-atmega328p/doc/* "${staging_dir}"
rm -rf "${staging_dir2}"

cd "${staging_dir}"
git init

git add .
git commit -m "Generate the HTML version of the book"
git branch -m $TARGET_BRANCH

git remote add origin "${repository_url}"

note "pushing the '$TARGET_BRANCH' branch to '${repository_url}'"
note "reminder: the primary staging directory is '${staging_dir}'"

git push origin $TARGET_BRANCH --force

note "staging directory left at '${staging_dir}'"
