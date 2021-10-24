obj-m := dev_scull.o

all:
	$(MAKE) -C /lib/modules/4.4.0-38-generic/build M=$(PWD) modules

clean:
	$(MAKE) -C /lib/modules/4.4.0-38-generic/build M=$(PWD) modules
