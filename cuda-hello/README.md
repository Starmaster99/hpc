# Hello World on CUDA

A simple project to test the readiness of your environment for CUDA application development.

## Preparation

Please, ensure that you have installed:
* gcc-13
* g++-13
* nvcc

> **NOTICE:** it doesn't really matter which version of CUDA you are running because of the code simplicity, but make sure you use CUDA 12.6 or higher.

## Installation

Please, follow these steps to install the app:

```bash
git clone https://github.com/Starmaster99/hpc.git
cd hpc/cuda-hello
mkdir build/
cd build/
cmake ..
make install
```

## Configuration

The editor of my choice is VSCode. You may leave me now you are planning to use something other.

To continue, please ensure that you have installed these extensions and the recommended ones too:
* C/C++ by Microsoft
* CMake Tools by Microsoft
* Nsight Visual Studio Code Edition by NVIDIA

Everything should be preconfigured, but checking is recommended.

Configure your environment:

Press **F1** key and type `CMake: Configure`. Choose empty.

You are good to go. From now on, press **F1** key and choose `CMake: Debug` option. If you don't see it, please, press the same key and select the `CMake: Select Variant` option. Select the `Debug`.