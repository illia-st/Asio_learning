#include "Server.h"

namespace server{
    Server::Server(server::ConnectionInfo ci) : ci{std::move(ci)},
        buffer(std::vector<char>(1024)),
        endpoint(asio::ip::address::from_string(ci.ip), ci.port){
        asio::io_context::work work(context);
        thr = std::thread([&](){context.run();});
    }

    void Server::HandleConnection() {
        asio::ip::tcp::acceptor acceptor(context, endpoint);
        asio::error_code ec;
        while(true){
            asio::ip::tcp::socket socket(context);
            acceptor.accept(socket);
            GrabSomeData(socket);
            socket.close();
        }
    }

    void Server::GrabSomeData(asio::ip::tcp::socket& socket){
        socket.async_read_some(asio::buffer(buffer.data(),buffer.size()),
                               [&](std::error_code ec, std::size_t length){
                                   if(!ec)
                                   {
                                       std::cout << "\n\nRead " << length << " bytes\n";
                                       for(size_t i {}; i < length; ++i){
                                           std::cout << buffer[i];
                                       }
                                       SendSomeData(socket);
                                       GrabSomeData(socket);
                                   }
                            });
    }
    void Server::SendSomeData(asio::ip::tcp::socket &socket) {
        socket.async_write_some(asio::buffer(buffer.data(), buffer.size()),
                                [&](std::error_code ec, std::size_t length){
           if(!ec){
               SendSomeData(socket);
           }
        });
    }

}