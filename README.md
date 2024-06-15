# BitFab (Bit Fabric)

BitFab is a P2P decentralized blockchain.

Under Development...
Please go to [Notion Plan Page](https://simple-lettuce-0e3.notion.site/9153326b1c794e15b1051562fcd4ee93?v=284d2c9a725642ff8cdf314f54310cb0) for project status.

# Installation

Make sure you have the following tools installed on your system:
  * cmake (https://cmake.org/install/)
  * protobuf
  * autoconf
  * automake
  * libtool
  * make
  * g++
  * unzip


On Ubuntu/Debian, you can install them with:
sudo apt-get install autoconf automake libtool curl make g++ unzip
sudo apt install protobuf-compiler

On mac, you can install them with:
brew install autoconf automake libtool protobuf

To build initially run:
    ./configureBuild.sh

To run executable:
    cd ./build/bin
    ./bitfab
