#include <iostream>
#include <string>

typedef struct {
    std::string src;
    std::string dest;
    int cycles;
} request;

class WebServer {
    private:
        int id;
        request req;
        bool available;
    public:
        WebServer(int _id);
        ~WebServer();
        int acceptRequest(request newReq, int cycle);
        int processRequest(int cycle);
        bool isAvailable();
};

WebServer::WebServer(int _id) : id(_id), available(true) {}

WebServer::~WebServer() {}

int WebServer::acceptRequest(request newReq, int cycle) {
    if (available) {
        req = newReq;
        available = false;
        std::cout << "[" << cycle << "] " << "Server " << id << " assigned request from " << req.src << " to " << req.dest << " for " << req.cycles << " cycles." << std::endl;
        return 0;  // Indicating success
    }

    return -1;
}

int WebServer::processRequest(int cycle) {
    if (!available) {
        if (req.cycles == 0) {
            std::cout << "[" << cycle << "] " << "Server " << id << " completed request from " << req.src << " to " << req.dest << std::endl;
            available = true;
        }
        req.cycles--;

        return 0;
    }
    
    return -1;
}

bool WebServer::isAvailable() {
    return available;
}