#pragma once
#include <string>
#include <iostream>
#include <iomanip>

struct Customer{
    std::string maKH;
    std::string tenKH;
    std::string SDT;

    void displayRow() const {
        std::cout << "| " << std::left << std::setw(8)  << maKH
                  << "| " << std::left << std::setw(22) << tenKH
                  << "| " << std::left << std::setw(13) << SDT
                  << " |\n";
    }
};
struct NodeCustomer{
    Customer data;
    NodeCustomer* next;
};
