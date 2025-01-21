run: grpc
	cd src && go run main.go

build: grpc
	cd src && go build main.go

grpc:
	cd src && cp ../../proto/secret_management.proto . && protoc --go_out=. --go-grpc_out=. --plugin=protoc-gen-grpc=/home/merlinst/go/bin/protoc-gen-go-grpc secret_management.proto
