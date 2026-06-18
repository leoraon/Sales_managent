#pragma once
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>

struct Customer{
    std::string maKH;
    std::string tenKH;
    std::string SDT;

    // Bộ đếm tự sinh mã KH
    static int demKH;
    static std::string sinhMaKH() {
        demKH++;
        std::ostringstream oss;
        oss << "KH" << std::setfill('0') << std::setw(4) << demKH;
        return oss.str();
    }

    void displayRow() const {
        std::cout << "| " << std::left << std::setw(8)  << maKH
                  << "| " << std::left << std::setw(22) << tenKH
                  << "| " << std::left << std::setw(13) << SDT
                  << " |\n";
    }
};

// Bắt buộc phải có dòng này (khởi tạo biến static bên ngoài struct)
inline int Customer::demKH = 0;

struct NodeCustomer{
    Customer data;
    NodeCustomer* next;
};
