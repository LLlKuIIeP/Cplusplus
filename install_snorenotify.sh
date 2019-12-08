#!/bin/bash
cd ~/

sudo apt-get install \
  qttools5-dev-tools \
  qttools5-dev \
  qt5-default \
  qttools5-dev \
  qttools5-dev-tools \
  libqt5svg5-dev \
  libqt5texttospeech5-dev \
  qtdeclarative5-dev \
  qtdeclarative5-dev-tools \
  qtquickcontrols2-5-dev \
  qml-module-qtquick-controls \
  qml-module-qtquick-controls2 \
  qml-module-qtquick-dialogs \
  qml-module-qtqml-models2 \
  qml-module-qtquick-templates2 \
  qml-module-qt-labs-folderlistmodel \
  qml-module-qt-labs-settings \
  qml-module-qt-labs-platform -y

# extra-cmake-modules
git clone --recurse-submodules https://github.com/KDE/extra-cmake-modules.git
cd extra-cmake-modules
cmake .
make
sudo make install

# snorenotify
git clone --recurse-submodules https://github.com/KDE/snorenotify.git
cd ../snorenotify/
cmake .
make -j8
sudo make install
