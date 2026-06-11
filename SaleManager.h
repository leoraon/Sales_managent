#pragma once
#include "Invoice.h"
#include "CustomerManager.h"
#include "ProductManager.h"
#include <string>
class SaleManager{
private:
   NodeInvoice* invoiceHead;
   NodeInvoiceDetail* detailHead;
   //bổ sung hai hàm :thêm chi tiết đơn hàng và tính tổng tiền để hỗ trợ hàm tạo hoá đơn mới
   void addInvoiceDetails(const std::string& maHD,const ProductManager& pm);
   double caculateTotal(const std::string& maHD);
public:
   SaleManager();
   void createInvoice(const CustomerManager& cm,const ProductManager& pm);//mình đang truyền dữ liệu như một danh bạ chứ không phải đơn lẻ
   void displayInovoice(const std::string& maHD);
};


















