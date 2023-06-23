obj-m += sev_sysfs_driver.o

all: module dt
	echo "Build driver and device tree overlay"
module:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
dt: anoverlay.dts
	dtc -@ -I dts -O dtb -o anoverlay.dtbo anoverlay.dts
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean