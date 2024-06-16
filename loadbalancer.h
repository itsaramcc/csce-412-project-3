/**
 * @file loadbalancer.h
 * @brief Header file for the LoadBalancer class.
 */

#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include "webserver.h"
#include <queue>
#include <sstream>

/**
 * @brief The LoadBalancer class manages multiple WebServer instances
 *        and handles incoming requests.
 */
class LoadBalancer {
    private:
        WebServer** webServers; ///< Array of pointers to WebServer instances
        std::queue<request> requestQ; ///< Queue to store incoming requests
        int cyclesElapsed; ///< Number of cycles elapsed
        int numServers; ///< Number of WebServer instances

    public:
        /**
         * @brief Constructor to initialize the LoadBalancer with a given number of servers.
         * @param numServers Number of WebServer instances to manage.
         */
        LoadBalancer(int numServers);

        /**
         * @brief Destructor to clean up dynamically allocated resources.
         */
        ~LoadBalancer();

        /**
         * @brief Creates a randomly generated request and adds it to the request queue.
         */
        void createRequest();

        /**
         * @brief Assigns pending requests to available WebServer instances.
         * @return 0 if request assigned successfully, -1 if no servers available.
         */
        int assignRequest();

        /**
         * @brief Increments the cycles elapsed and processes requests on each server.
         * @return The updated number of cycles elapsed.
         */
        int incrementCycles();
};

#endif // LOADBALANCER_H


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

/**
 * @brief Generate a random IP address.
 * @return A randomly generated IP address in the format "x.x.x.x".
 */
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