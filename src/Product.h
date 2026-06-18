#pragma once
#include <string>
#include <iomanip>
#include <iostream>
#include <sstream>  


struct Product{
    std::string maSP;
    std::string tenSP;
    std::string donVi;
    double donGia;
    //bổ sung biến đếm để tự sinh mã sp
    static int demSP;
    static std::string sinhMaSP() {
        demSP++;
        std::ostringstream oss;
        oss << "SP" << std::setfill('0') << std::setw(4) << demSP;
    return oss.str();
}

    void displayRow() const {
        std::cout << "| " << std::left  << std::setw(8)  << maSP
                  << "| " << std::left  << std::setw(22) << tenSP
                  << "| " << std::left  << std::setw(8)  << donVi
                  << "| " << std::right << std::setw(10) << std::fixed
                          << std::setprecision(0) << donGia
                  << " |\n";
    }
};
// bắt buộc với static
inline int Product::demSP = 0;

struct NodeProduct{
    Product data;
    NodeProduct* next;
};
