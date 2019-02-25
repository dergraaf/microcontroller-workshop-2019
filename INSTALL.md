
Installation
------------

Install cross-compiler for ARM:
```
wget https://developer.arm.com/-/media/Files/downloads/gnu-rm/8-2018q4/gcc-arm-none-eabi-8-2018-q4-major-linux.tar.bz2
tar xjf gcc-arm-none-eabi-8-2018-q4-major-linux.tar.bz2
sudo mv gcc-arm-none-eabi-8-2018-q4-major/ /opt/
echo "export PATH=\$PATH:/opt/gcc-arm-none-eabi-8-2018-q4-major/bin/" >> ~/.bashrc
source ~/.bashrc
```

Install the build system:
```
sudo apt install python3-pip git dfu-util scons
sudo -H pip3 install lbuild pyelftools
```

Use the Python3 version of SCons
```
sudo nano `which scons`
```
And change `python` to `python3` in the first line.

Get the source code
```
git clone https://github.com/dergraaf/microcontroller-workshop-2019.git
cd microcontroller-workshop-2019
git submodule update --init --recursive
```

Install udev rules for programming via USB:
```
sudo cp -v tools/45-maple.rules /etc/udev/rules.d/45-maple.rules
sudo chown root:root /etc/udev/rules.d/45-maple.rules
sudo chmod 644 /etc/udev/rules.d/45-maple.rules
sudo udevadm trigger
```

Check the example can be built:
```
cd examples/blink
make prepare
make build

# Requires the connected STM32F103 board
make program
```
