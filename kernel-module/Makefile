obj-m += globalvar.o
obj-m += hellomod.o
obj-m += currentptr.o
obj-m += basicmem.o

KERNEL_PATH := /lib/modules/$(shell uname -r)/build/

all:
	make -C $(KERNEL_PATH) M=$(PWD) modules
clean:
	make -C $(KERNEL_PATH) M=$(PWD) clean


