# Filey the File Integrity Checker

## Introduction

Filey is a file and directory tool that checks the integrity of the given file or directory.

## Features

```
Usage: ./filey -p path -o path [options]...
Filey file integrity checker
-p path
Path to file or directory to check integrity
-o path
Path to output
-r
Set if the file structure is to be traversed recursively
-f
Force overwriting of the old saved hashes
-h
Display this page
```
## Prerequisites

Install CMake (3.26 or higher):
```bash
sudo apt install cmake
```

Install OpenSSL (3 or higher):
```bash
sudo apt install openssl
```

## Install

Clone the repository and go into the folder:
```bash
git clone https://mygit.th-deg.de/bubungus/Filey.git

cd Filey
```

You might need to link your OpenSSL installation in the CMake file


Create a directory where you want to save the executable:
```bash
mkdir build

cd build
```

To install the integrity checker, you have to build the Cmake:
```bash
cmake ..
```

And then build it
```bash
make
```

## Usage

Now you can use the integrity checker:
```bash
./Filey -p path -o output_path [options...]
```

Attention if you want to use it outside the folder, please change the path for the logs.
You can do this by changing the path in Filey/src/main.cpp and build it again.

Example usage:
```bash
./Filey -p ../files/ -o ../hashes/
```

This will hash the two text files in the folder. If you change the content, an alert will be sent.
