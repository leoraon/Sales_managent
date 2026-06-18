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
   double calculateTotal(const std::string& maHD);
public:
   SaleManager();
   void createInvoice(CustomerManager& cm,const ProductManager& pm);//mình đang truyền dữ liệu như một danh bạ chứ không phải đơn lẻ
   void printInvoice(const std::string& maHD);
   // Hiện danh sách tóm tắt tất cả hóa đơn (dùng bởi menuBanHang case 3)
   void displayAllInvoices() const;
   // Lưu/đọc file
   void saveToFile(const std::string& invoiceFile, const std::string& detailFile) const;
   void loadFromFile(const std::string& invoiceFile, const std::string& detailFile);
   // Getter cho ReportManager truy xuất dữ liệu nội bộ
   NodeInvoice*       getInvoiceHead() const;
   NodeInvoiceDetail* getDetailHead()  const;
   // Hiện lịch sử giao dịch của một khách hàng
   void hienThiLichSuKH(const std::string& maKH) const;
};
