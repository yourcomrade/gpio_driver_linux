obj-m += test.o

all: module
	echo "Build driver and device tree overlay"
module:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean