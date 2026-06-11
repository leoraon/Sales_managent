#pragma once
#include <string>
struct Invoice{
    std::string maHD;
    std::string maKH;
    std::string thoiGianLap; // Ví dụ: "15/04/2026 14:30:00"
    double tongTienHang; 
    double thueVAT;
    double tongThanhToan;  
     // Bổ sung thực tế của bạn
    double tienKhachTra;
    double tienTraLai;   // = tienKhachTra - tongThanhToan
};
struct NodeInvoice {
    Invoice data;
    NodeInvoice* next;
};

struct InvoiceDetail {
    std::string maHD;     
    std::string maSP;     
    int soLuong;
    double donGia;   // Giá tại thời điểm bán
    double chietKhau; 
    double thanhTien; 
   
};

struct NodeInvoiceDetail {
    InvoiceDetail data;
    NodeInvoiceDetail* next;
};