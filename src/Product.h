#pragma once
#include <string>
#include <iomanip>
#include <iostream>

struct Product{
    std::string maSP;
    std::string tenSP;
    std::string donVi;
    double donGia;

    void displayRow() const {
        std::cout << "| " << std::left  << std::setw(8)  << maSP
                  << "| " << std::left  << std::setw(22) << tenSP
                  << "| " << std::left  << std::setw(8)  << donVi
                  << "| " << std::right << std::setw(10) << std::fixed
                          << std::setprecision(0) << donGia
                  << " |\n";
    }
};

struct NodeProduct{
    Product data;
    NodeProduct* next;
};
