# SecVault Business Logic Server

## Overview

The SecVault business logic server handles secure data storage and cryptographic operations. It communicates with the proxy API (Go) via **gRPC**.

## Stack

- **C++** – core language  
- **gRPC 1.67.1** – inter-service communication  
- **libpq 15.5** – PostgreSQL client library  
- **Crypto++ 8.9.0, OpenSSL** – cryptographic operations  
- **spdlog 1.15.0, fmt 11.0.2** – logging and string formatting  
- **CMake + Conan** – build system and dependency management  
