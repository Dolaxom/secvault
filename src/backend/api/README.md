# SecVault Proxy API

## Overview

SecVault Proxy API acts as an HTTP(S) gateway, forwarding client requests to the core business logic server via gRPC.

## Stack

- **Go 1.23.1** + **Gin 1.10.0** – API web server  
- **gRPC client** – for communication with the C++ business logic server  

## Architecture

1. Receives and validates **HTTP(S) requests** via the Gin framework.  
2. Forwards requests to the **C++ business logic server** using **gRPC**.  
3. Returns responses from the business logic server to the client.  

## API Specification

The OpenAPI specification is available at:  
[docs/api/swagger.yaml](../../../docs/api/swagger.yaml)
