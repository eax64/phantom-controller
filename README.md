phantom-controller
==================

Userland linux joystick driver for DJI phantom 2 controller. The aim of this tool is to be able to use a DJI phantom 2 controller as a joystick on a computer. The communication protocol between the DJI RC software and the controller is not public and it wasn't easily possible to use the controller with an other software. With this little hack (still in early pre-alpha!) it should be possible. :)

## How to

### Compile and launch the program
```
make
sudo ./phantom-contoller
```

### Start a joystick reader
```
jstest /dev/input/jsX
```
or
```
jstest-gtk
```
