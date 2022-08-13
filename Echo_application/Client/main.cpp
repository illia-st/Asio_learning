#include "Client.h"
using namespace client;

int main(){
    ConnectionInfo ci{"127.0.0.1", 2228};

    Client cl {ci};
    std::string msg;
    while(std::getline(std::cin, msg)){
        cl.SendMessage(msg);
        msg.clear();
    }
    return 0;
}