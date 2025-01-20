.PHONY: build clean

# Release / Debug
BUILD_TYPE = Debug

build:
	cp -R ../proto .
	protoc --cpp_out=. --grpc_out=. --plugin=protoc-gen-grpc=/usr/bin/grpc_cpp_plugin proto/secret_management.proto
	conan install . --output-folder=build --build=missing 
	mkdir -p build && cd build && cmake .. -DCMAKE_BUILD_TYPE=$(BUILD_TYPE) && make

clean:
	rm -rf build
	rm -rf proto

