#include <iostream>
#include <chrono>
#include <vector>

#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>


std::vector<char> vBuffer(20 * 1024);
void GrabSomeData(asio::ip::tcp::socket& socket){
    socket.async_read_some(asio::buffer(vBuffer.data(), vBuffer.size()),
                           [&](std::error_code ec, std::size_t length){
       if(!ec)
       {
           std::cout << "\n\nRead " << length << " bytes\n";
           for(size_t i {}; i < length; ++i){
               std::cout << vBuffer[i];
           }
           GrabSomeData(socket);
       }
    });
}

int main(){
    asio::error_code ec;

    asio::io_context context;
    asio::io_context::work idleWork(context);

    std::thread thr {[&context](){context.run();}};

    asio::ip::tcp::endpoint endpoint(asio::ip::make_address("51.38.81.49",
                                                            ec), 80);
    asio::ip::tcp::socket socket (context);
    socket.connect(endpoint);

    if(!ec){
        std::cout << "it is connected" << std::endl;
    }
    else{
        std::cout << "Here are some troubles with the connection to address "
        << ec.message() <<  std::endl;
    }


    if(socket.is_open()){
        std::string sRequest {"GET /index.html HTTP/1.1\r\nHost: example.com\r\nConnection: close\r\n\r\n"};
        socket.write_some(asio::buffer(sRequest.data(), sRequest.size()), ec);
//        we have to wait a little to give the network enough time to get us
//        the information
//        using namespace std::chrono_literals;
//        std::this_thread::sleep_for(200ms);
        // this is a better way how to wait
        GrabSomeData(socket);

    }
    thr.join();
    return 0;
}