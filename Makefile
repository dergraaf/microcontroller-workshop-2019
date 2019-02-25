
bootloader:
	tools/stm32flash/stm32flash -w tools/generic_boot20_pb12.bin -v -g 0x0 /dev/ttyUSB0

.PHONY : bootloader
