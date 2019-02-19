# CSCI 3753 Programming Assignment 2
## Author: Owen Shepherd
## Date: February 18th, 2018

## Instructions
The device file should be created with the command "sudo mknod -m 777 /dev/simple_char_device c 240 0"  
Then, the driver module should be loaded with "make -C /lib/modules/$(uname -r)/build M=$PWD
modules"  
Finally, the driver can be controlled with the pa2 executable, whose source code is listed in pa2.c.
