# cpp Electerm sync server

[![Build Status](https://github.com/electerm/electerm-sync-server-cpp/actions/workflows/linux.yml/badge.svg)](https://github.com/electerm/electerm-sync-server-cpp/actions)

**Languages:** [English](README.md) | [中文](README_cn.md)

A simple electerm data sync server.

## Dependencies

### System Dependencies

**macOS (with Homebrew):**

```bash
brew install cmake boost asio
```

**Ubuntu/Debian:**

```bash
sudo apt update
sudo apt install cmake libboost-all-dev libasio-dev libssl-dev
```

**CentOS/RHEL/Fedora:**

```bash
sudo yum install cmake boost-devel asio-devel openssl-devel  # CentOS/RHEL
# or
sudo dnf install cmake boost-devel asio-devel openssl-devel  # Fedora
```

### Project Dependencies

The project uses Crow (web framework) and jwt-cpp headers, which are downloaded automatically.

## Setup

```bash
git clone git@github.com:electerm/electerm-sync-server-cpp.git
cd electerm-sync-server-cpp

# create env file, then edit .env
cp sample.env .env
# Edit .env to set your JWT_SECRET and JWT_USERS

# download project dependencies (Crow and jwt-cpp headers)
./scripts/init

# build the project
./scripts/build

# run the server
./scripts/run
```

The server will start and show something like:

```text
server running at http://127.0.0.1:7837
```

## Configuration

Edit the `.env` file to configure:

- `PORT`: Server port (default: 7837)
- `HOST`: Server host (default: 127.0.0.1)
- `JWT_SECRET`: Secret key for JWT tokens (change in production!)
- `JWT_USERS`: Comma-separated list of allowed usernames
- `FILE_STORE_PATH`: Optional path for data storage (defaults to current directory)

## Usage in Electerm

In electerm sync settings, set custom sync server with:

- **Server URL**: `http://127.0.0.1:7837`
- **JWT_SECRET**: Your JWT_SECRET from `.env`
- **JWT_USER_NAME**: One of the JWT_USERS from `.env`

## API Endpoints

- `GET /api/sync` - Retrieve user data (requires JWT auth)
- `POST /api/sync` - Test endpoint (requires JWT auth)
- `PUT /api/sync` - Store user data (requires JWT auth)
- `GET /test` - Health check endpoint

## Testing

```bash
./scripts/test
```

## Write your own data store

Take [src/file_store.hpp](src/file_store.hpp) as an example to implement your own read/write methods.

## Sync server in other languages

[https://github.com/electerm/electerm/wiki/Custom-sync-server](https://github.com/electerm/electerm/wiki/Custom-sync-server)

## License

MIT
