package app

import (
	"api/internal/transport/rest"

	"github.com/gin-gonic/gin"
)

func RunServer() {
	// gin.SetMode(gin.ReleaseMode) // TODO сделать через command line

	engine := gin.Default()
	engine.SetTrustedProxies([]string{"127.0.0.1"})

	rest.MappingRoutes(engine)

	engine.Run(":8090")
}
