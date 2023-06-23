obj-m += gpio_driver.o

all: module dt
	echo "Build driver and device tree overlay"
module:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
dt: myoverlay.dts
	dtc -@ -I dts -O dtb -o myoverlay.dtbo myoverlay.dts
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean