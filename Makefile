PRESET ?= x86_64-linux-clang-debug

.PHONY: all config build clean rebuild sandbox ln

all: build

config:
	cmake --preset=$(PRESET)

build:
	cmake --build --preset=$(PRESET)

clean:
	rm -rf out/build/$(PRESET)

rebuild: clean config build

sandbox:
	./out/build/$(PRESET)/sandbox/sequel-sandbox

ln:
	ln -s ./out/build/$(PRESET)/compile_commands.json .
