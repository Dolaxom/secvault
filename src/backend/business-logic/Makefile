.PHONY: build clean

# Release / Debug
BUILD_TYPE = Debug

build:
	mkdir proto
	cp ../proto/secret_management.proto .
	# protoc -I . --cpp_out=proto --grpc_out=proto --plugin=protoc-gen-grpc=grpc_cpp_plugin secret_management.proto
	/home/merlinst/.conan2/p/b/protof25d9860b8789/p/bin/protoc -I . --cpp_out=proto --grpc_out=proto --plugin=protoc-gen-grpc=/home/merlinst/.conan2/p/b/grpcb413bdac61f49/p/bin/grpc_cpp_plugin secret_management.proto
	conan install . --output-folder=build --build=missing
	mkdir -p build && cd build && cmake .. -DCMAKE_BUILD_TYPE=$(BUILD_TYPE) -DCMAKE_TOOLCHAIN_FILE="build/Release/generators/conan_toolchain.cmake" && make

clean:
	rm -rf build
	rm -rf proto

build_draft:
	/home/merlinst/.local/bin/cmake -DCMAKE_POLICY_DEFAULT_CMP0091=NEW -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=generators/conan_toolchain.cmake -S/home/merlinst/secvault/src/backend/business-logic -B/home/merlinst/secvault/src/backend/business-logic/build/build/Release -G "Unix Makefiles"
	cd build/build/Release && make 

conan_install:
	conan install . --output-folder=build --build=missing
