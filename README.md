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

## Install

Clone the repository and go into the folder:
```
git clone https://mygit.th-deg.de/bubungus/Filey.git

cd Filey
```

Create a directory where you want to save the executable:
```
mkdir build

cd build
```

To install the integrity checker, you have to build the Cmake:
```
cmake ..
```

And then build it
```
make
```

## Usage

Now you can use the integrity checker:
```
./Filey -p path -o output_path [options...]
```

Attention if you want to use it outside the folder, please change the path for the logs.
You can do this by changing the path in Filey/src/main.cpp and build it again.
