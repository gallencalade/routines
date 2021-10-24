target = jprobe_exp
obj-m := $(target).o

KERNELDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

install:
	insmod $(target).ko

uninstall:
	rmmod $(target).ko

clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
