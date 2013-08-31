skp2tri
=======

Parse Sketchup skp files into a homemade format

Description :
----------

This project aims at converting Sketchup skp files into a homemade format that can be use with Linux.
As the Sktechup SDK is only for Windows and MacOS, the project supports cross-compilation.

I compile from Ubuntu 13.04 with mingw32, and then call the program with Wine.

Compilation :
----------
From the project-root run:

	mkdir build; cd build
	cmake -DCMAKE_TOOLCHAIN_FILE=/home/julien/skp2tri/Toolchain-windows-mingw32.cmake ..
	make

The binaries will be set in <project-root>/bin with all the required dll.
