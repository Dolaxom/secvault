FROM swaggerapi/swagger-ui

LABEL maintainer="Nikolai Ryzhov <dolaxom4@gmail.com>"

ENV SWAGGER_JSON=/usr/share/swagger.yaml
EXPOSE 8080
