package rest

import (
	"api/internal/models"
	"fmt"
	"net/http"

	"github.com/gin-gonic/gin"
)

func MappingRoutes(engine *gin.Engine) {
	engine.POST("/api/v1/secret/write", func(c *gin.Context) {
		var json models.SecretWriteRequest
		if err := c.ShouldBindJSON(&json); err != nil {
			c.JSON(http.StatusBadRequest, gin.H{"error": err.Error()})
			return
		}

		// TODO Отправить по rpc на C++ сервер

		response := models.SecretWriteResponse{
			FirstToken:  "first test token",
			SecondToken: "second test token",
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
