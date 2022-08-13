#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <asio.hpp>
#include <asio/ts/internet.hpp>
#include <asio/ts/buffer.hpp>

namespace server {
    struct ConnectionInfo {
        std::string ip;
        uint16_t port;
    };
    class Server {
    public:
        Server() = delete;
        Server(ConnectionInfo ci);
        ~Server();
        void HandleConnection();


    private:
        ConnectionInfo ci;
        std::vector<char> buffer;
        asio::ip::tcp::endpoint endpoint;
        std::thread thr;
        asio::io_context context;
        void GrabSomeData(asio::ip::tcp::socket& socket);
        void SendSomeData(asio::ip::tcp::socket& socket);
    };
}