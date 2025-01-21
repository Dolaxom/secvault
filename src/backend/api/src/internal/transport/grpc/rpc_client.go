package grpc

import (
	"log"
	"sync"

	pb "api/internal/transport/grpc/proto"

	"google.golang.org/grpc"
)

type GRPCClient struct {
	Client pb.SecretServiceClient
}

var (
	instance *GRPCClient
	once     sync.Once
)

func GetGRPCClient() *GRPCClient {
	once.Do(func() {
		conn, err := grpc.Dial("localhost:9005", grpc.WithInsecure())
		if err != nil {
			log.Fatalf("Server fatal error: %v", err)
		}

		instance = &GRPCClient{
			Client: pb.NewSecretServiceClient(conn),
		}
	})
	return instance
}
