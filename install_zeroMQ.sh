#!/bin/bash
sudo apt-get install \
    g++ \
    cmake \
    libboost-all-dev \
    libevent-dev \
    libdouble-conversion-dev \
    libgoogle-glog-dev \
    libgflags-dev \
    libiberty-dev \
    liblz4-dev \
    liblzma-dev \
    libsnappy-dev \
    make \
    zlib1g-dev \
    binutils-dev \
    libjemalloc-dev \
    libssl-dev \
    pkg-config \
    libsodium-dev -y

sudo apt-get install \
    libunwind8-dev \
    libelf-dev \
    libdwarf-dev -y
  

#!libzmq
# or sudo apt-get install libczmq-dev -y
cd ~/
git clone --recurse-submodules https://github.com/zeromq/libzmq.git
cd libzmq/
mkdir cmake-make && cd cmake-make && cmake ..
make -j8
sudo make install

#!cppzmq
cd ~/
git clone --recurse-submodules https://github.com/zeromq/cppzmq.git
cd cppzmq/
cmake .
make -j8
sudo make install
