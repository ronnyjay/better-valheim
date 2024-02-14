default: better-valheim

better-valheim: build
	cd build && cmake -DCMAKE_BUILD_TYPE=Debug .. && make

build:
	mkdir -p build

format:
	clang-format -i src/**/*.cpp

run: better-valheim
	build/better-valheim 

.PHONY: clean
clean:
	rm -rf build .cache

