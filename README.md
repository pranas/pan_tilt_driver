Pan & Tilt Driver
================================

This code is part of my internet controlled pan and tilt system project.

It is a simple program for [LeafLabs Maple](http://leaflabs.com/devices/maple/) microcontroller board. It reads commands sent over serial port and translates them to PWM output on board pins.

Maple is Arduino-like board. You should be able to easily port this code for Arduino board if you want to.

## Protocol

This program uses human readable protocol. Two commands are supported:

* ``PAN X;`` changes PWM output on PIN 5 to X (0-65535)
* ``TILT Y;`` changes PWM output on PIN 6 to Y (0-65535)

For example:

    PAN 65535;TILT 65535;PAN 32767;TILT 32767;PAN 0;TILT 32767;

## Installation

Easiest way to install this on your Maple board is to use [Maple IDE](http://leaflabs.com/docs/maple-ide-install.html).

You can also set up [Unix toolchain](http://leaflabs.com/docs/unix-toolchain.html) on your own and compile it on command line.