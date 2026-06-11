#pragma once
#include "Product.h"
class ProductManager{
    NodeProduct* head;
    //thêm hàm tìm node để hỗ trợ các phương thức
    NodeProduct* findNode(const std::string& maSP);
public:
    ProductManager(); // Hàm khởi tạo
    void addProduct(const Product& sp);
    bool deleteProduct(const std::string& maSP);
    void searchProduct(const std::string& maSP);
    bool updateProduct(const std::string& maSP,const Product& newData);
    void displayAll();
};
//thay đổi kiểu trả về với hàm tìm kiếm để hỗ trợ các hàm khác