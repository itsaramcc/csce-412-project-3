#include "webserver.h"
#include <queue>
#include <sstream>

class LoadBalancer {
    private:
        WebServer** webServers;
        std::queue<request> requestQ;
        int cyclesElapsed;
        int numServers;

    public:
        LoadBalancer(int numServers);
        ~LoadBalancer();
        void createRequest();
        int assignRequest();
        int incrementCycles();
};

LoadBalancer::LoadBalancer(int _numServers) {
    numServers = _numServers;
    cyclesElapsed = 0;

    webServers = new WebServer*[numServers];
    for (int i = 0; i < numServers; i++) {
        webServers[i] = new WebServer(i + 1);
    }
}

LoadBalancer::~LoadBalancer() {
    for (int i = 0; i < numServers; i++) {
        delete webServers[i];
    }
    delete[] webServers;
}

std::string generateRandomIP() {
    std::ostringstream ip;
    ip << (std::rand() % 256) << "."
       << (std::rand() % 256) << "."
       << (std::rand() % 256) << "."
       << (std::rand() % 256);
    return ip.str();
}

void LoadBalancer::createRequest() {
    request newReq;
    newReq.src = generateRandomIP();
    newReq.dest = generateRandomIP();
    newReq.cycles = std::rand() % 100 + 1;  // Random cycles between 1 and 100
    requestQ.push(newReq);
    std::cout << "[" << cyclesElapsed << "] " << "Created request from " << newReq.src << " to " << newReq.dest << " for " << newReq.cycles << " cycles." << std::endl;
}

int LoadBalancer::assignRequest() {
    if (requestQ.empty()) {
        return -1;
    }

    for (int i = 0; i < numServers; ++i) {
        if (webServers[i]->isAvailable()) {
            request req = requestQ.front();
            if (webServers[i]->acceptRequest(req, cyclesElapsed) == 0) {
                requestQ.pop();
                return 0;
            }
        }
    }
    return -1;
}

int LoadBalancer::incrementCycles() {
    ++cyclesElapsed;

    for (int i = 0; i < numServers; ++i) {
        if (!webServers[i]->isAvailable()) {
            webServers[i]->processRequest(cyclesElapsed);
        }
    }
    return cyclesElapsed;
}