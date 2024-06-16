#include "loadbalancer.h"
#include <iostream>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "Usage: \"./loadbalancer [num of servers]\"" << std::endl;
        return -1;
    }

    int numServers = std::stoi(argv[1]);

    LoadBalancer lb(numServers);
    for (int i = 0; i < numServers*100; i++) {
        lb.createRequest();
    }

    int gen_req_counter = std::rand() % 200 + 50;
    while (1) {
        if (gen_req_counter == 0) {
            lb.createRequest();
            gen_req_counter = std::rand() % 200 + 50;
        }
        lb.assignRequest();
        gen_req_counter--;

        if (lb.incrementCycles() == 10000) { break; }
    }


    return 0;
}