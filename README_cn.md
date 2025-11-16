# cpp Electerm 同步服务器

[![Build Status](https://github.com/electerm/electerm-sync-server-cpp/actions/workflows/linux.yml/badge.svg)](https://github.com/electerm/electerm-sync-server-cpp/actions)

**语言:** [English](README.md) | [中文](README_cn.md)

一个简单的 electerm 数据同步服务器。

## 依赖项

### 系统依赖

**macOS (使用 Homebrew):**

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
# 或
sudo dnf install cmake boost-devel asio-devel openssl-devel sqlite-devel  # Fedora
```

### 项目依赖

项目使用 Crow (web 框架) 和 jwt-cpp 头文件，这些会自动下载。

## 设置

```bash
git clone git@github.com:electerm/electerm-sync-server-cpp.git
cd electerm-sync-server-cpp

# 创建环境文件，然后编辑 .env
cp sample.env .env
# 编辑 .env 设置您的 JWT_SECRET 和 JWT_USERS

# 下载项目依赖 (Crow 和 jwt-cpp 头文件)
./scripts/init

# 构建项目
./scripts/build

# 运行服务器
./scripts/run
```

服务器将启动并显示类似信息：

```text
server running at http://127.0.0.1:7837
```

## 配置

编辑 `.env` 文件进行配置：

- `PORT`: 服务器端口 (默认: 7837)
- `HOST`: 服务器主机 (默认: 127.0.0.1)
- `JWT_SECRET`: JWT 令牌的密钥 (生产环境请更改!)
- `JWT_USERS`: 允许的用户名列表，用逗号分隔
- `FILE_STORE_PATH`: 可选的数据存储路径 (默认为当前目录)

## 在 Electerm 中使用

在 electerm 同步设置中，设置自定义同步服务器：

- **服务器 URL**: `http://127.0.0.1:7837`
- **JWT_SECRET**: 您的 `.env` 中的 JWT_SECRET
- **JWT_USER_NAME**: 您的 `.env` 中的某个 JWT_USERS

## API 端点

- `GET /api/sync` - 检索用户数据 (需要 JWT 认证)
- `POST /api/sync` - 测试端点 (需要 JWT 认证)
- `PUT /api/sync` - 存储用户数据 (需要 JWT 认证)
- `GET /test` - 健康检查端点

## 测试

```bash
./scripts/test
```

## 编写自己的数据存储

以 [src/data_store.hpp](src/data_store.hpp) 为例实现您自己的读写方法。

## 其他语言的同步服务器

[https://github.com/electerm/electerm/wiki/Custom-sync-server](https://github.com/electerm/electerm/wiki/Custom-sync-server)

## 许可证

MIT
