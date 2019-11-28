#!/bin/bash

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
