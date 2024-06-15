#!/bin/bash
CURRDIR=${PWD}
echo "*** Running start script to run configurations ***"
echo "*** Current Directory : $CURRDIR ***"

echo "*** Make for jsoncpp ***"
cd $CURRDIR/vendor/jsoncpp
rm -rf ./build
cmake . -B build
cd build
make

echo "*** Make for spdlog ***"
cd $CURRDIR/vendor/spdlog
rm -rf ./build
cmake . -B build
cd build
make

echo "*** Make for protobuf ****"
cd $CURRDIR/vendor/protobuf
make clean
rm -rf ./.build
mkdir .build
./autogen.sh
./configure --with-protoc=$CURRDIR/vendor/protobuf/.build/bin/protoc --prefix=${PWD}/.build/
make install
cd $CURRDIR

rm ./src/proto/models/*.pb.*
echo "*** Compiling protobuff files using the protoc compiler from vendor ***"
$CURRDIR/vendor/protobuf/.build/bin/protoc --proto_path=$CURRDIR/src/proto $CURRDIR/src/proto/*.proto --cpp_out=$CURRDIR/src/proto/models/

echo "*** Removing any existing build folder ***"
rm -rf ./build/
cmake . -B build
cd build
echo "*** Running Make ***"
make