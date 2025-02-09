package rest

import (
	"api/internal/models"
	"api/internal/transport/grpc"
	"context"
	"net/http"
	"time"

	pb "api/internal/transport/grpc/proto"

	"github.com/gin-contrib/cors"
	"github.com/gin-gonic/gin"
)

func MappingRoutes(engine *gin.Engine) {
	engine.Use(cors.New(cors.Config{
		AllowOrigins:     []string{"*"}, // fix in prod
		AllowMethods:     []string{"GET", "POST", "OPTIONS"},
		AllowHeaders:     []string{"Origin", "Content-Type"},
		AllowCredentials: true,
	}))

	engine.POST("/api/v1/secret/write", func(ginCtx *gin.Context) {
		var requestBody models.SecretWriteRequest
		if err := ginCtx.ShouldBindJSON(&requestBody); err != nil {
			ginCtx.JSON(http.StatusBadRequest, gin.H{"error": "You must send the json with the 'secret' and 'password' fields!"})
			return
		}

		if len(requestBody.Secret) == 0 || len(requestBody.Password) == 0 {
			ginCtx.JSON(http.StatusBadRequest, gin.H{"error": "The field values must be filled in!"})
			return
		}

		client := grpc.GetGRPCClient()
		ctx, cancel := context.WithTimeout(context.Background(), 2*time.Second)
		defer cancel()

		requestBodyRpc := &pb.WriteSecretRequest{
			Secret:   requestBody.Secret,
			Password: requestBody.Password,
		}

		responseRpc, err := client.Client.WriteSecret(ctx, requestBodyRpc)

		if err != nil {
			ginCtx.JSON(http.StatusBadRequest, gin.H{"error": err.Error()})
			return
		}

		response := models.SecretWriteResponse{
			FirstToken:  responseRpc.FirstToken,
			SecondToken: responseRpc.SecondToken,
		}

		ginCtx.JSON(http.StatusOK, response)
	})

	engine.GET("/api/v1/secret/read", func(ginCtx *gin.Context) {
		token1 := ginCtx.DefaultQuery("token1", "")
		token2 := ginCtx.DefaultQuery("token2", "")

		if len(token1) == 0 || len(token2) == 0 {
			ginCtx.JSON(http.StatusBadRequest, gin.H{"error": "The values of token1 and token2 must be filled in via query parameters!"})
			return
		}

		client := grpc.GetGRPCClient()
		ctx, cancel := context.WithTimeout(context.Background(), 2*time.Second)
		defer cancel()

		requestBodyRpc := &pb.ReadSecretRequest{
			FirstToken:  token1,
			SecondToken: token2,
		}

		responseRpc, err := client.Client.ReadSecret(ctx, requestBodyRpc)

		if err != nil {
			ginCtx.JSON(http.StatusBadRequest, gin.H{"error": err.Error()})
			return
		}

		response := models.SecretReadResponse{
			Secret: responseRpc.Secret,
		}

		ginCtx.JSON(http.StatusOK, response)
	})
}
