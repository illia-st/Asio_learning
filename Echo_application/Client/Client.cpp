#include "Client.h"

client::Client::Client(client::ConnectionInfo info): ci{std::move(info)}, endpoint{asio::ip::address::from_string(ci.ip)
                                                                                   , ci.port} {
    thr = std::thread([&](){this->context.run();});
}
client::Client::~Client(){ thr.join(); }

void client::Client::ChangeConnectionInfo(client::ConnectionInfo ci_){
    ci = std::move(ci_);
}

client::Result client::Client::SendMessage(const std::string& msg){
    asio::ip::tcp::socket socket(context);
    asio::error_code ec;
    socket.connect(endpoint, ec);
    if(!ec){
        std::cout << "Connected to the server" << std::endl;
    }
    else{
        return client::Result::Connection_failed;
    }
    std::cout << "Sending request ..." << std::endl;
    socket.write_some(asio::buffer(msg.data(), msg.size()), ec);

    std::cout << "Waiting for response ..." << std::endl;
    GrabSomeData(socket);

    return client::Result::Connection_succeeded;
}
void client::Client::GrabSomeData(asio::ip::tcp::socket &socket) {
    socket.async_read_some(asio::buffer(buffer.data(), buffer.size()),
                           [&](std::error_code ec, std::size_t length){
           if(!ec)
           {
               std::cout << "\n\nRead " << length << " bytes\n";
               for(size_t i {}; i < length; ++i){
                   std::cout << buffer[i];
               }
               GrabSomeData(socket);
           }
       });
}