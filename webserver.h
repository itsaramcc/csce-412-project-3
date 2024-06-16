/**
 * @file webserver.h
 * @brief Header file for the WebServer class.
 */


#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <iostream>
#include <string>

/**
 * @brief Structure representing a request with source IP, destination IP, and processing cycles.
 */
typedef struct {
    std::string src; ///< Source IP address
    std::string dest; ///< Destination IP address
    int cycles; ///< Processing cycles required
} request;

/**
 * @brief The WebServer class represents a single web server that can accept and process requests.
 */
class WebServer {
    private:
        int id; ///< Id of the server
        request req; ///< Current request being processed
        bool available; ///< Availability status of the server
        
    public:
        /**
         * @brief Constructor to initialize a WebServer instance.
         */
        WebServer(int _id);

        /**
         * @brief Destructor to clean up resources.
         */
        ~WebServer();

        /**
         * @brief Accepts a request if the server is available.
         * @param req Request to be accepted.
         * @return 0 if request accepted successfully, -1 if server not available.
         */
        int acceptRequest(request newReq, int cycle = -1);

        /**
         * @brief Processes the current request on the server.
         * @return 0 if request processed successfully, -1 if no request to process.
         */
        int processRequest(int cycle = -1);

        /**
         * @brief Checks if the server is available to accept a new request.
         * @return true if available, false otherwise.
         */
        bool isAvailable();
};

#endif // WEBSERVER_H



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