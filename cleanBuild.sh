#!/bin/bash
CURRDIR=${PWD}
echo "*** Running clean build script ***"
echo "*** Current Directory : $CURRDIR ***"
echo "*** Compiling protobuff files using the protoc compiler from vendor ***"

rm ./src/proto/models/*.pb.*

$CURRDIR/vendor/protobuf/.build/bin/protoc --proto_path=$CURRDIR/src/proto $CURRDIR/src/proto/*.proto --cpp_out=$CURRDIR/src/proto/models/

echo "*** Running Make clean ***"
rm -rf ./build/
cmake . -B build
cd build

echo "*** Running Make ***"
make