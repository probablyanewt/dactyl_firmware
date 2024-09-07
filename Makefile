all: clean build

build:
	pio -f -c vim run

init:
	pio -f -c vim run --target compiledb

upload:
	pio -f -c vim run --target upload

clean:
	pio -f -c vim run --target clean

program:
	pio -f -c vim run --target program

uploadfs:
	pio -f -c vim run --target uploadfs

update:
	pio -f -c vim pkg update

debug:
	sudo minicom -D /dev/ttyACM0
