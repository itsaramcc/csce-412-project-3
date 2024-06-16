/**
 * @file main.cpp
 * @brief Main program file for the Load Balancer application.
 */

#include "loadbalancer.h"
#include <iostream>

/**
 * @brief Main function to demonstrate the Load Balancer functionality.
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line arguments (including program name as argv[0]).
 * @return 0 on success, -1 on incorrect usage or other errors.
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "Usage: \"./loadbalancer [num of servers]\"" << std::endl;
        return -1;
    }

    int numServers = std::stoi(argv[1]);

    LoadBalancer lb(numServers);

    // Generate requests for each server, simulating initial workload
    for (int i = 0; i < numServers*100; i++) {
        lb.createRequest();
    }

    int gen_req_counter = std::rand() % 200 + 50;
    while (1) {
        // Create a new request after a certain number of iterations
        if (gen_req_counter == 0) {
            lb.createRequest();
            gen_req_counter = std::rand() % 200 + 50;
        }
        gen_req_counter--;

        // Assign requests to available servers and decrement the counter
        lb.assignRequest();

        // Check if the maximum number of cycles (10000) is reached
        if (lb.incrementCycles() == 10000) { break; }
    }


    return 0;
}