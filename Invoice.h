#pragma once
#include <string>
struct Invoice{
    std::string maHD;
    std::string maKH;
    //vì một số yếu tố kk khi làm việc vs thời gian nen de lai bien la ngaylap de dễ thống kê
    int ngayLap;
    int thangLap;
    int namLap;
    double tongTienHang; 
    double thueVAT;
    double tongThanhToan;  
    double tienGiamGia; //bổ sung vì có cơ chế tích luỹ điểm
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