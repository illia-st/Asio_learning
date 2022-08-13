#pragma once
#include <string>
#include <iostream>
#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>

namespace client {
    enum class Result{
        Connection_failed,
        Connection_succeeded
    };
    struct ConnectionInfo {
        std::string ip;
        uint16_t port;
    };

    class Client {
    public:
        Client() = delete;
        Client(ConnectionInfo info);
        void ChangeConnectionInfo(ConnectionInfo ci_);
        Result SendMessage(const std::string &msg);
        ~Client();
    private:
        ConnectionInfo ci;
        std::vector<char> buffer;
        asio::io_context context;
        std::thread thr;
        asio::ip::tcp::endpoint endpoint;
        void GrabSomeData(asio::ip::tcp::socket& socket);
        //asio::ip::tcp::socket socket;
        //socket will be defined each time in the SendMessage method
    };
}