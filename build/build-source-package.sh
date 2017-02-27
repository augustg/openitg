#!/bin/bash

# exit immediately on nonzero exit code
set -e
set -u

OUTPUT_DIR="$1"

function print_usage
{
	echo "Usage: $0 [output directory]"
	exit 0
}

if ! [ -d "$OUTPUT_DIR" ]; then print_usage; fi

pushd .

OPENITG_VERSION="`git describe --abbrev=0`" # 0.9
# OPENITG_VERSION="`git describe | sed -r 's/-/+/g'`" # 0.9+23+a9f34be

TEMP_WORK_DIR="/tmp/openitg-work-tmp"

if [ -d $TEMP_WORK_DIR ]; then
    rm -rf $TEMP_WORK_DIR
fi

mkdir -p $TEMP_WORK_DIR
cp -r .. $TEMP_WORK_DIR/openitg-$OPENITG_VERSION

# Enter repository
cd $TEMP_WORK_DIR/openitg-$OPENITG_VERSION

# .tarball-version
echo $OPENITG_VERSION > .tarball-version
REPLACEMENT_REGEX='.*AC_INIT(\[OpenITG\].*'
sed "s/$REPLACEMENT_REGEX/AC_INIT([OpenITG], [$OPENITG_VERSION])/" configure.ac > configure2.ac
rm configure.ac
mv configure2.ac configure.ac

# Clean all changes, added files, and files hidden by .gitignore
#git clean -dfx

# Remove git files
rm -rf .git .gitignore

# When a user downloads a source package it should be prepared for running ./configure
./autogen.sh

cd ..

tar -Jcf $TEMP_WORK_DIR/openitg-$OPENITG_VERSION.tar.xz openitg-$OPENITG_VERSION

# Back to build directory
popd

mv $TEMP_WORK_DIR/openitg-$OPENITG_VERSION.tar.xz $OUTPUT_DIR/

rm -rf $TEMP_WORK_DIR