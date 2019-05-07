# moxa-gpio-control

`moxa-gpio-control` is a C library for controlling the Linux GPIO
subsystem via sysfs interface.

## Build

This project use autotools as buildsystem. You can build this project by

* If the build target architecture is x86_64

	```
	# ./autogen.sh --host=x86_64-linux-gnu --includedir=/usr/include/moxa --libdir=/usr/lib/x86_64-linux-gnu
	# make
	# make install
	```
* If the build target architecture is armhf

	```
	# ./autogen.sh --host=arm-linux-gnueabihf --includedir=/usr/include/moxa --libdir=/usr/lib/arm-linux-gnueabihf
	# make
	# make install
	```

The autogen script will execute ./configure and pass all the command-line
arguments to it.

## Documentation

[API Reference](/API_References.md)
