#pragma once
#include "Customer.h"
class CustomerManager{
private:
    NodeCustomer* head; //con trỏ quản lý toàn bộ danh sách khách hàng
    //thêm hàm tìm node để hỗ trợ các phương thức
    NodeCustomer* findNode(const std::string& maSP);
public:
    //khai báo các hàm liên quan 
    //Nếu bạn chỉ khai báo head mà không làm gì thêm, C++ sẽ gán cho cái head này một địa chỉ bộ nhớ chứa toàn "rác" (một chuỗi số ngẫu nhiên nào đó do chương trình trước để lại).
    CustomerManager(); // Hàm khởi tạo
    void addCustomer(const Customer& kh);
    bool deleteCustomer(const std::string& maKH);
    void searchCustomer(const std::string& maKH);
    bool updateCustomer(const std::string& maKH,const Customer& newData);
    void displayAll();
    // Tra cứu khách hàng (const) - dùng bởi SaleManager
    Customer* getCustomer(const std::string& maKH) const;
};
//class này như là kiểu tự xây dựng danh sách liên kết rồi
