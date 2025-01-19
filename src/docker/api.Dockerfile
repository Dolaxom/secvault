FROM golang:1.23 AS builder
WORKDIR /app

COPY api/src/go.mod api/src/go.sum ./
RUN go mod download

COPY api/src/ .
RUN go build -o main .

FROM gcr.io/distroless/base
COPY --from=builder /app/main /main
EXPOSE 8090

CMD ["/main"]
