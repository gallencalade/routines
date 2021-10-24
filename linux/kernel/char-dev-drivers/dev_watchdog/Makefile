obj-m := watchdog.o

all:
	$(MAKE) -C /lib/modules/4.4.0-36-generic/build M=$(PWD) modules

clean:
	$(MAKE) -C /lib/modules/4.4.0-36-generic/build M=$(PWD) modules
