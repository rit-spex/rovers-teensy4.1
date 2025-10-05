#!/usr/bin/env bash
echo "Initializing submodules..."
git submodule update --init --recursive

echo "Installing GLFW 3"
sudo apt install libglfw3-dev

echo "Installing clang-tidy and clang-format"
bash -c "$(wget -O - https://apt.llvm.org/llvm.sh)"

USER_HOME=$(getent passwd $SUDO_USER | cut -d: -f6)

sudo add-apt-repository 'deb http://apt.llvm.org/bionic/ llvm-toolchain-bionic main'
wget -O - https://apt.llvm.org/llvm-snapshot.gpg.key|sudo apt-key add -
sudo apt update

echo "Installing clang-format using apt"
sudo apt install clang-format-20
echo "alias clang-format='clang-format-20'" >> ${USER_HOME}/.bashrc

echo "Installing clang-tidy using apt"
sudo apt install clang-tidy-20
echo "alias clang-tidy='clang-tidy-20'" >> ${USER_HOME}/.bashrc

echo "Installing platformio core"
sudo apt install platformio

echo "Installing dos2unix"
sudo apt install dos2unix
