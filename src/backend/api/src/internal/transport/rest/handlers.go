package rest

import (
	"api/internal/models"
	"api/internal/transport/grpc"
	"context"
	"fmt"
	"net/http"
	"time"

	pb "api/internal/transport/grpc/proto"

	"github.com/gin-gonic/gin"
)

func MappingRoutes(engine *gin.Engine) {
	engine.POST("/api/v1/secret/write", func(c *gin.Context) {
		var reqBody models.SecretWriteRequest
		if err := c.ShouldBindJSON(&reqBody); err != nil {
			c.JSON(http.StatusBadRequest, gin.H{"error": err.Error()})
			return
		}

		client := grpc.GetGRPCClient()
		ctx, cancel := context.WithTimeout(context.Background(), 2*time.Second)
		defer cancel()

		requestBodyRpc := &pb.WriteSecretRequest{
			Secret:   reqBody.Secret,
			Password: reqBody.Password,
		}

		responseRpc, _ := client.Client.WriteSecret(ctx, requestBodyRpc)

		response := models.SecretWriteResponse{
			FirstToken:  responseRpc.FirstToken,
			SecondToken: responseRpc.SecondToken,
		}

		c.JSON(http.StatusOK, response)
	})

	engine.GET("/api/v1/secret/read", func(c *gin.Context) {
		token1 := c.DefaultQuery("token1", "")
		token2 := c.DefaultQuery("token2", "")

		fmt.Println(token1 + ", " + token2)
		// TODO Отправить по rpc на C++ сервер

		response := models.SecretReadResponse{
			Secret: "test secret",
		}

		c.JSON(http.StatusOK, response)
	})
}
