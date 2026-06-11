#pragma once
#include "Customer.h"
class CustomerManager{
private:
    NodeCustomer* head; //con trỏ quản lý toàn bộ danh sách khách hàng
public:
    //khai báo các hàm liên quan 
    //Nếu bạn chỉ khai báo head mà không làm gì thêm, C++ sẽ gán cho cái head này một địa chỉ bộ nhớ chứa toàn "rác" (một chuỗi số ngẫu nhiên nào đó do chương trình trước để lại).
    CustomerManager(); // Hàm khởi tạo
    void addCustomer(const Customer& kh);
    bool deleteCustomer(const std::string& maKH);
    void searchCustomer(const std::string& maKH);
    bool updateCustomer(const std::string& maKh,const Customer& newData);
    void displayAll();
};
//class này như là kiểu tự xây dựng danh sách liên kết rồi
