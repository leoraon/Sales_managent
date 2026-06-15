#pragma once
#include "Invoice.h"
#include "CustomerManager.h"
#include "ProductManager.h"
#include <string>
class SaleManager{
private:
   NodeInvoice* invoiceHead;
   NodeInvoiceDetail* detailHead;
   // Hàm hỗ trợ: thêm chi tiết đơn hàng và tính tổng tiền
   void addInvoiceDetails(const std::string& maHD, const ProductManager& pm);
   double caculateTotal(const std::string& maHD);
   bool isInvoiceExist(const std::string& maHD); // Kiểm tra trùng mã hóa đơn
public:
   SaleManager();
   void createInvoice(CustomerManager& cm, const ProductManager& pm); // cm không const vì cần cộng điểm tích lũy
   void displayInvoice(const std::string& maHD);
};


















