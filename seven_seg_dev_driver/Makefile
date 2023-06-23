obj-m += sev_dev_driver.o

all: module dt
	echo "Build driver and device tree overlay"
module:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
dt: newoverlay.dts
	dtc -@ -I dts -O dtb -o newoverlay.dtbo newoverlay.dts
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean