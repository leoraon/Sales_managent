#pragma once
#include <string>
#include <iomanip>
struct Product{
    std::string maSP;
    std::string tenSP;
    std::string donVi;
    double donGia;
    // Thêm hàm này vào struct
    // Dùng 'const' vì hàm này chỉ in ra, không làm thay đổi dữ liệu sản phẩm
    //tạm thời chưa học hàm trình bày
    void displayRow() const {
        std::cout << "| " << std::left << std::setw(8)  << maSP
                  << "| " << std::left << std::setw(22) << tenSP
                  << "| " << std::left << std::setw(8)  << donVi
                  << "| " << std::right << std::setw(10) << std::fixed << std::setprecision(3) << donGia 
                  << " |\n";
};
};
struct NodeProduct{
    Product data;
    NodeProduct* next;
};
