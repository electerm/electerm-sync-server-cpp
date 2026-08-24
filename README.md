# cpp Electerm sync server

[![Build Status](https://github.com/electerm/electerm-sync-server-cpp/actions/workflows/linux.yml/badge.svg)](https://github.com/electerm/electerm-sync-server-cpp/actions)

**Languages:** [English](README.md) | [中文](README_cn.md)

Open-sourced terminal/ssh/sftp/telnet/serialport/RDP/VNC/Spice/ftp client(Linux, Mac, Windows, Android, HarmonyOS).

Besides mainstream Windows/macOS/Linux/Android, electerm also supports HarmonyOS, and older systems — Ubuntu 18, Windows 7, macOS 10+, and special Chinese Linux distributions such as UOS, Kylin, and LoongArch (both old-world and new-world).

<p>
  <a href="https://electerm.org">Homepage / Downloads</a> ·
  <a href="https://theme.electerm.org">Theme</a> ·
  <a href="https://github.com/electerm/electerm-web-docker">Docker</a> ·
  <a href="https://demo.electerm.org">Online demo</a> ·
  <a href="https://github.com/electerm/electerm-android">Android</a> ·
  <a href="https://github.com/electerm/electerm-harmony">HarmonyOS</a> ·
  <a href="https://appgallery.huawei.com/app/detail?id=org.electerm.electerm">Huawei AppGallery</a> ·
  <a href="https://www.microsoft.com/store/apps/9NCN7272GTFF">Microsoft Store</a> ·
  <a href="https://snapcraft.io/electerm">Snap Store</a> ·
  <a href="https://repos.electerm.org/deb">deb repo</a> ·
  <a href="https://repos.electerm.org/rpm">rpm repo</a>
</p>

<div>🌐 <strong><a href="https://cloud.electerm.org">electerm online</a></strong> — Public free online electerm app</div>
<div>🤖 <strong><a href="https://ai.electerm.org">electerm AI</a></strong> — Free AI for electerm users</div>
<div>💻 <strong><a href="https://github.com/electerm/electerm-web">electerm-web</a></strong> — Web app version running in browser (including mobile device)</div>

A simple electerm data sync server.

## Dependencies

### System Dependencies

**macOS (with Homebrew):**

```bash
brew install cmake boost asio sqlite3
```

**Ubuntu/Debian:**

```bash
sudo apt update
sudo apt install cmake libboost-all-dev libasio-dev libssl-dev libsqlite3-dev
```

**CentOS/RHEL/Fedora:**

```bash
sudo yum install cmake boost-devel asio-devel openssl-devel sqlite-devel  # CentOS/RHEL
# or
sudo dnf install cmake boost-devel asio-devel openssl-devel sqlite-devel  # Fedora
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

Take [src/data_store.hpp](src/data_store.hpp) as an example to implement your own read/write methods.

## Sync server in other languages

[https://github.com/electerm/electerm/wiki/Custom-sync-server](https://github.com/electerm/electerm/wiki/Custom-sync-server)

## License

MIT
