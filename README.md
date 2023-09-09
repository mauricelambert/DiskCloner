# DiskCloner

## Description

This repository implements a cross-platform disk cloner written in C and an optional python CLI.

## Requirements

There is no requirements.

Optional:
 - Python3
 - Python3 Standard Library

## Installation

### Compilation

```bash
git clone "https://github.com/mauricelambert/DiskCloner.git"
cd "DiskCloner"
gcc -O5 FileCloner.c -o FileCloner.exe
./FileCloner.exe sdb sdDisk.bin
```

### Download

#### Windows

```bash
git clone "https://github.com/mauricelambert/DiskCloner.git"
cd "DiskCloner"
wget https://mauricelambert.github.io/info/python/security/libFileCloner.dll
python WindowsDiskClonerInterface.py "SD Card" sdDisk.bin
```

```bash
wget https://mauricelambert.github.io/info/python/security/WindowsFileCloner.exe
WindowsFileCloner.exe "\\.\PHYSICALDRIVE1" sdDisk.bin
```

#### Linux

```bash
git clone "https://github.com/mauricelambert/DiskCloner.git"
cd "DiskCloner"
wget https://mauricelambert.github.io/info/python/security/libFileCloner.so
python3 LinuxDiskClonerInterface.py sdb sdDisk.bin
```

```bash
wget https://mauricelambert.github.io/info/python/security/LinuxFileCloner
./LinuxFileCloner sdb sdDisk.bin
```

## Usages

### Command line

```bash
./FileCloner.exe sdb sdDisk.bin
python3 LinuxDiskClonerInterface.py sdb sdDisk.bin         # Linux
python WindowsDiskClonerInterface.py "SD Card" sdDisk.bin  # Windows
```

## Links

 - [Github](https://github.com/mauricelambert/DiskCloner)
 - [Linux executable](https://mauricelambert.github.io/info/python/security/WindowsFileCloner.exe)
 - [Linux Shared Object](https://mauricelambert.github.io/info/python/security/libFileCloner.so)
 - [Windows executable](https://mauricelambert.github.io/info/python/security/WindowsFileCloner.exe)
 - [Windows DLL](https://mauricelambert.github.io/info/python/security/libFileCloner.dll)

## License

Licensed under the [GPL, version 3](https://www.gnu.org/licenses/).
