#pragma once
#include <string>

struct Invoice{
    std::string maHD;
    std::string maKH;
    int ngayLap;
    int thangLap;
    int namLap;
    double tongTienHang;
    double thueVAT;
    double tongThanhToan;
    double tienKhachTra;
    double tienTraLai;    // = tienKhachTra - tongThanhToan
};

struct NodeInvoice {
    Invoice data;
    NodeInvoice* next;
};

struct InvoiceDetail {
    std::string maHD;
    std::string maSP;
    int    soLuong;
    double donGia;      // giá tại thời điểm bán
    double chietKhau;
    double thanhTien;
};

struct NodeInvoiceDetail {
    InvoiceDetail data;
    NodeInvoiceDetail* next;
};