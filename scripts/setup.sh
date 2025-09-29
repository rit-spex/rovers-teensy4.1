#!/usr/bin/env bash
echo "Initializing submodules..."
git submodule update --init --recursive

echo "Installing clang-tidy and clang-format"
bash -c "$(wget -O - https://apt.llvm.org/llvm.sh)"

echo "Installing clang-format using apt"
sudo apt install clang-format-19
echo "alias clang-format='clang-format-19'" >> ~/.bashrc

echo "Installing clang-tidy using apt"
sudo apt install clang-tidy-19
echo "alias clang-tidy='clang-tidy-19'" >> ~/.bashrc

echo "Installing platformio core"
curl -fsSL -o get-platformio.py https://raw.githubusercontent.com/platformio/platformio-core-installer/master/get-platformio.py
python3 get-platformio.py
