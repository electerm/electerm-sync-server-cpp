# cpp Electerm sync server

[![Build Status](https://github.com/electerm/electerm-sync-server-cpp/actions/workflows/linux.yml/badge.svg)](https://github.com/electerm/electerm-sync-server-cpp/actions)

A simple electerm data sync server.

## deps

Install Boost and [Crow](https://github.com/CrowCpp/Crow)

## Use

```bash
git clone git@github.com:electerm/electerm-sync-server-cpp.git
cd electerm-sync-server-cpp

# create env file, then edit .env
cp sample.env .env

## install proper deps

## init deps
./scripts/init

## build
./scripts/build

## run
./scripts/run

# would show something like
# server running at http://127.0.0.1:7837
# Then you can use http://127.0.0.1:7837/api/sync as API Url in electerm custom sync

# in electerm sync settings, set custom sync server with:
# server url: http://127.0.0.1:7837
# JWT_SECRET: your JWT_SECRET in .env
# JWT_USER_NAME: one JWT_USER in .env
```

## Test

```bash
./scripts/test
```

## Write your own data store

Just take [src/file_store.hpp](src/file_store.hpp) as an example, write your own read/write method

## Sync server in other languages

[https://github.com/electerm/electerm/wiki/Custom-sync-server](https://github.com/electerm/electerm/wiki/Custom-sync-server)

## License

MIT
