.PHONY: build clean

# Release / Debug
BUILD_TYPE = Debug

build:
	conan install . --output-folder=build --build=missing 
	mkdir -p build && cd build && cmake .. -DCMAKE_BUILD_TYPE=$(BUILD_TYPE) && make

clean:
	rm -rf build

