# How to use seven segment display driver
Two folders **seven_seg_dev_driver** and **seven_seg_sysfs_driver** contains driver to control seven segment display for raspberry pi 4. They contain a Make file, a device tree overlay file, a driver file, and a test file.  
To use those driver, user just need to run the command   
```bash
make all
```
to compile Linux driver and device tree overlay. After that, user must load the device tree overlay first, before loading the driver.
For device driver in **seven_seg_dev_driver**:
```bash
sudo dtoverlay newoverlay.dbto
sudo insmod sev_dev_driver.ko
```
For sysfs driver in **seven_seg_sysfs_driver**:
```bash
sudo dtoverlay newoverlay.dbto
sudo insmod sev_sysfs_driver.ko
```
## Device driver
After loading both overlay and driver, a file name 'seven_seg_disp' will appear under the folder /dev/, user can use command like 
```bash
sudo echo 1 > /dev/seven_seg_disp
```
to set the seven segment to display 1, for the counting from 0 to 9, user can compile the test file 'test_pro_dev.c' to do it:
```bash
gcc test_pro_dev.c -o test
sudo ./test
```
For removingthe driver, user must unload driver first then remove the overlay:
``` bash
sudo rmmod sev_dev_driver.ko
sudo dtoverlay -r newoverlay.dbto
```
## Sysfs driver
After loading both driver and overlay file, a file name 'myleds' will appear under the folder /sys/class/sev_leds/.   
To set the display, it simply writes to the file:
```bash
sudo echo 1 > /sys/class/sev_leds/myleds
```
To get the current value displaying on seven segment display, it simply reads the file:
```bash
sudo cat /sys/class/sev_leds/myleds
```
To run the test program, compiles and run the file 'test_pro_sysfs.c':
```bash
gcc test_pro_sysfs.c -o test
sudo ./test 
```
To remove the driver, unload the module driver first and unload the device tree overlay:
```bash
sudo rmmod sev_sysfs_driver
sudo dtoverlay -r anoverlay
```