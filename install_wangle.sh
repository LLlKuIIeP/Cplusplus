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
  

#!fmt
cd ~/
git clone --recursive https://github.com/fmtlib/fmt.git
cd fmt/makmake install
cmake .
make -j8
sudo make install

#!folly
cd ~/
git clone --recursive https://github.com/facebook/folly.git
cd fmt/
cmake .
make -j8
sudo make install

#!fizz
cd ~/
git clone --recursive https://github.com/facebookincubator/fizz.git
cd fizz/fizz/
cmake .
make -j8
sudo make install

#!wangle
cd ~/
git clone --recursive https://github.com/facebook/wangle.git
cd wangle/wangle
cmake .
make -j8
ctest
sudo make install
