<<<<<<< HEAD
obj-m += tasks.o
=======
obj-m += task.o
>>>>>>> 2dfec6abe36dbb2644a24a6f3ff1cf32d304caa7

KERNELDIR ?= /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

all:
	$(MAKE) -C $(KERNELDIR) M=$(PWD)
clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
