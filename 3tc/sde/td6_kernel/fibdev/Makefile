# If KERNELRELEASE is not defined, we were called directly from the command
# line; invoke the kernel build system
ifeq ($(KERNELRELEASE),)

KERNELDIR ?= /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

clean:
	rm -rf *.o *~ core .depend .*.cmd *.ko *.mod.c *.symvers *.order .tmp*

# Otherwise we've been invoked from the kernel build system and can use its language
	 else

$(info Building with KERNELRELEASE = ${KERNELRELEASE})
obj-m := fibdev.o

 endif

# Disable module signature verification to suppress warnings about tainted kernels
CONFIG_MODULE_SIG=n    
