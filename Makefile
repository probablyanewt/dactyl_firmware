all: clean build

build:
	pio -f -c vim run	

init:
	PLATFORMIO_BUILD_FLAGS=-DPACTF_ENABLE pio -f -c vim run --target compiledb 

upload:
	pio -f -c vim run --target upload

clean:
	pio -f -c vim run --target clean

update:
	pio -f -c vim pkg update

debug:
	minicom -D /dev/ttyACM0

test: 
	@mkdir -p .tests
	@gcc -DPACTF_ENABLE -o .tests/$(file) src/$(file).c
	@./.tests/$(file)

test-all:
	$(MAKE) test --no-print-directory file=layout
	$(MAKE) test --no-print-directory file=keystate

