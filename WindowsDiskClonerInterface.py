#!/usr/bin/env python3
# -*- coding: utf-8 -*-

###################
#    This file implements an interface for Linux FileCloner with Python
#    Copyright (C) 2023  DiskCloner

#    This program is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.

#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.

#    You should have received a copy of the GNU General Public License
#    along with this program.  If not, see <https://www.gnu.org/licenses/>.
###################

"""
This file implements an interface for Linux 
FileCloner with python to clone hard disk.
"""

__version__ = "0.0.2"
__author__ = "Maurice Lambert"
__author_email__ = "mauricelambert434@gmail.com"
__maintainer__ = "Maurice Lambert"
__maintainer_email__ = "mauricelambert434@gmail.com"
__description__ = """
This file implements an interface for Linux 
FileCloner with python to clone hard disk.
"""
__url__ = "https://github.com/mauricelambert/DiskCloner"

__all__ = ["main"]

__license__ = "GPL-3.0 License"
__copyright__ = """
DiskCloner  Copyright (C) 2023  Maurice Lambert
This program comes with ABSOLUTELY NO WARRANTY.
This is free software, and you are welcome to redistribute it
under certain conditions.
"""
copyright = __copyright__
license = __license__

print(copyright)

from sys import stderr, exit, argv, executable
from os.path import join, exists, dirname
from subprocess import check_output
from ctypes import c_char, cdll
from os import getcwd

filename = "libFileCloner.dll"
filenames = (join(dirname(__file__), filename), join(getcwd(), filename))
bufferSize = 131072

for filename in filenames:
    if exists(filename):
        break
else:
    print(f"Library {filename!r} is missing", file=stderr)
    exit(1)

libfilecloner = cdll.LoadLibrary(filename)


def main() -> int:
    """
    This function starts the script from the command line.
    """

    disks = {
        x.split(r"\\.\PHYSICALDRIVE")[0].strip(): r"\\.\PHYSICALDRIVE"
        + x.split(r"\\.\PHYSICALDRIVE")[1].split()[0]
        for x in check_output(
            "wmic DISKDRIVE list brief", encoding="cp437"
        ).splitlines()
        if r"\\.\PHYSICALDRIVE" in x
    }

    if len(argv) != 3:
        print(
            f"USAGES: {executable} {argv[0]} diskName"
            " destinationFilePath\nDisks names:\n -",
            "\n - ".join(disks),
            file=stderr,
        )
        return 2

    _, sourcefilepath, destinationfilepath = argv
    buffer = (c_char * bufferSize)(b"\0")

    if sourcefilepath in disks:
        sourcefilepath = disks[sourcefilepath]

    libfilecloner.clone_from_filename(
        sourcefilepath.encode(),
        destinationfilepath.encode(),
        buffer,
        bufferSize,
    )

    return 0


if __name__ == "__main__":
    exit(main())
