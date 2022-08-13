#include "Server.h"

int main(){
    using namespace server;
    ConnectionInfo info{"127.0.0.1", 2228};
    Server sr(info);
    sr.HandleConnection();
    return 0;
}