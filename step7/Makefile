obj-m += pseudo7.o

KSRC= /home/ltts/ebuildws/kernel_ws/linux-4.14.224/


all:
	make -C ${KSRC} M=${PWD} modules ARCH=arm CROSS_COMPILE=arm-linux-gnueabi-
clean:
	make -C ${KSRC} M=${PWD} clean ARCH=arm CROSS_COMPILE=arm-linux-gnueabi-
