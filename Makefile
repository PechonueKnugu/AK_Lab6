ifneq ($(KERNELRELEASE),)
obj-m += hello1.o
obj-m += hello2.o
ccflags-y += -g
else
KDIR ?= /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

default:
	$(MAKE) -C $(KDIR) M=$(PWD) modules
	cp hello1.ko hello1.ko.unstripped
	cp hello2.ko hello2.ko.unstripped
	$(CROSS_COMPILE)strip -g hello1.ko
	$(CROSS_COMPILE)strip -g hello2.ko

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean

%.s %.i: %.c
	$(MAKE) -C $(KDIR) M=$(PWD) $@
endif
