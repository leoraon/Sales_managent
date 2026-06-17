#pragma once
#include "Product.h"
class ProductManager{
private:
    NodeProduct* head;
    //thêm hàm tìm node để hỗ trợ các phương thức
    NodeProduct* findNode(const std::string& maSP) const;
public:
    ProductManager(); // Hàm khởi tạo
    void addProduct(const Product& sp);
    bool deleteProduct(const std::string& maSP);
    void searchProduct(const std::string& tuKhoa);
    bool updateProduct(const std::string& maSP,const Product& newData);
    void displayAll();
    // Tra cứu sản phẩm (const) - dùng bởi SaleManager
    const Product* getProduct(const std::string& maSP) const;
    // ── Bước D: Lưu/đọc file ── (Manager tự quản lý file của chính nó)
    void saveToFile(const std::string& filename) const ;
    void loadFromFile(const std::string& filename);
};
