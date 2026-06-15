#include <iostream>
#include <iomanip>
#include <ctime>
#include "SaleManager.h"

using namespace std;
//hàm khởi tạo
SaleManager::SaleManager(){
    invoiceHead=NULL;
    detailHead=NULL;
}
void SaleManager::addInvoiceDetails(const std::string& maHD, const ProductManager& pm) {
    int tiepTuc = 1;
    cout << "Bat dau \n";
    
    while (tiepTuc == 1) {
        InvoiceDetail detail;
        detail.maHD = maHD;
        detail.chietKhau = 0; // Đặt mặc định ban đầu là 0
        
        cout << "Nhap ma san pham: ";
        cin >> detail.maSP;
        
        const Product* spData = pm.getProduct(detail.maSP);
        
        if (spData == NULL) {
            cout << "Loi: San pham khong ton tai trong kho\n";
        } else {
            cout << "Nhap So luong(" << spData->tenSP << "): ";
            cin >> detail.soLuong;
            
            detail.donGia = spData->donGia;
            double tiLeGiam = spData->tiLeKhuyenMai; 
            detail.chietKhau = (detail.soLuong * detail.donGia) * tiLeGiam;

            if (detail.chietKhau > 0) {
                cout << "=> [He thong] San pham dang Sale, giam: -" << detail.chietKhau << " VND\n";
            }
            detail.thanhTien = (detail.soLuong * detail.donGia) - detail.chietKhau;
            NodeInvoiceDetail* newNode = new NodeInvoiceDetail;
            newNode->data = detail;
            newNode->next = detailHead;
            detailHead = newNode;      
            cout << " Da them: " << detail.soLuong << " x " << spData->tenSP 
                 << " = " << detail.thanhTien << " VND\n";
        } 
        
        cout << "Tiep tuc them san pham? (1: Co / 0: Khong): ";
        cin >> tiepTuc;
    }
}
double SaleManager::caculateTotal(const std::string& maHD){
    double tongTienHang=0.0;
    NodeInvoiceDetail*tmp=detailHead;
    while(tmp!=NULL){
        if (tmp->data.maHD==maHD){
            tongTienHang+=tmp->data.thanhTien;
        }
        tmp=tmp->next;
    }
    return tongTienHang;
}
//sp thì ko thay đổi còn khách hàng thì tích thêm điểm tích luỹ nên ko có const
void SaleManager::createInvoice(CustomerManager& cm, const ProductManager& pm) {
    Invoice newInvoice;
    
    // --- BƯỚC 1: HỆ THỐNG TỰ SINH MÃ VÀ THỜI GIAN ---
    int cnt = 1; 
    NodeInvoice* tmp = invoiceHead;
    while (tmp != NULL) {
        cnt++;
        tmp = tmp->next;
    }
    newInvoice.maHD = "HD" + std::to_string(cnt);
    
    time_t now = time(0);
    tm *ltm = localtime(&now);
    newInvoice.ngayLap = ltm->tm_mday;
    newInvoice.thangLap = 1 + ltm->tm_mon;
    newInvoice.namLap = 1900 + ltm->tm_year;

    // --- BƯỚC 2: QUÉT MÃ VẠCH SẢN PHẨM ---
    cout << "\n================= QUAY THANH TOAN =================\n";
    cout << "=> Dang tao moi Hoa Don: " << newInvoice.maHD << "\n";
    addInvoiceDetails(newInvoice.maHD, pm);

    // --- BƯỚC 3: TÍNH TOÁN TIỀN TẠM TÍNH ---
    newInvoice.tongTienHang = caculateTotal(newInvoice.maHD);
    newInvoice.thueVAT = newInvoice.tongTienHang * 0.1; 
    
    double tongTienTamTinh = newInvoice.tongTienHang + newInvoice.thueVAT; 
    double tienGiamGia = 0; 

    // --- BƯỚC 4: XỬ LÝ KHÁCH HÀNG & ĐIỂM TÍCH LŨY ---
    cout << "\nNhap Ma Khach Hang (Nhap KH00 neu la khach vang lai): ";
    cin >> newInvoice.maKH;

    if (newInvoice.maKH != "KH00") {
        Customer* kh = cm.getCustomer(newInvoice.maKH); 
        if (kh != NULL) {
            cout << "=> Tai khoan: " << kh->tenKH << " | Diem hien co: " << kh->diemTichLuy << " diem\n";
            
            if (kh->diemTichLuy > 0) {
                int luaChon;
                cout << "Khach co muon dung diem de tru tien khong? (1: Co, 0: Khong): ";
                cin >> luaChon;
                
                if (luaChon == 1) {
                    int diemMuonDung;
                    cout << "Nhap so diem muon dung (Toi da " << kh->diemTichLuy << "): ";
                    cin >> diemMuonDung;
                    
                    if (diemMuonDung > kh->diemTichLuy) diemMuonDung = kh->diemTichLuy;
                    if (diemMuonDung > tongTienTamTinh) diemMuonDung = tongTienTamTinh;
                    
                    tienGiamGia = diemMuonDung; 
                    kh->diemTichLuy -= diemMuonDung; 
                    cout << "=> Da tru " << diemMuonDung << " diem vao hoa don.\n";
                }
            }

            newInvoice.tongThanhToan = tongTienTamTinh - tienGiamGia;

            // Tích lũy 2% trên số tiền thực trả
            int diemCongThem = newInvoice.tongThanhToan * 0.02; 
            kh->diemTichLuy += diemCongThem; 
            
            cout << "=> Diem tich them: +" << diemCongThem << " diem. Tong diem: " << kh->diemTichLuy << " diem\n";
        } else {
            cout << "=> Loi: Khong tim thay tai khoan! Chuyen ve KH00.\n";
            newInvoice.maKH = "KH00"; 
            newInvoice.tongThanhToan = tongTienTamTinh; 
        }
    } else {
        newInvoice.tongThanhToan = tongTienTamTinh; 
    }

    // Đổ dữ liệu giảm giá vào hóa đơn để lưu trữ
    newInvoice.tienGiamGia = tienGiamGia;

    // --- BƯỚC 5: MÀN HÌNH CHỐT SỐ LIỆU ĐỂ THU TIỀN ---
    cout << "\n---------------- TONG KET ----------------\n";
    cout << "Tong tien hang: " << newInvoice.tongTienHang << " VND\n";
    cout << "Thue VAT (10%): " << newInvoice.thueVAT << " VND\n";
    if (newInvoice.tienGiamGia > 0) cout << "Tru diem:      -" << newInvoice.tienGiamGia << " VND\n"; 
    cout << "=> KHACH CAN TRA: " << newInvoice.tongThanhToan << " VND\n";
    cout << "------------------------------------------\n";

    // --- BƯỚC 6: GIAO DỊCH TIỀN MẶT ---
    do {
        cout << "Tien khach dua: ";
        cin >> newInvoice.tienKhachTra;
        if (newInvoice.tienKhachTra < newInvoice.tongThanhToan) {
            cout << "=> Loi: Tien khach dua khong du! Vui long nhap lai.\n";
        }
    } while (newInvoice.tienKhachTra < newInvoice.tongThanhToan);

    newInvoice.tienTraLai = newInvoice.tienKhachTra - newInvoice.tongThanhToan;
    cout << "Tien thoi lai:  " << newInvoice.tienTraLai << " VND\n";

    // --- BƯỚC 7: LƯU VÀO DANH SÁCH LIÊN KẾT ---
    NodeInvoice* newNode = new NodeInvoice;
    newNode->data = newInvoice;
    newNode->next = invoiceHead;
    invoiceHead = newNode;

    cout << "\n=> GIAO DICH THANH CONG. DA LUU VAO HE THONG!\n";
}

void SaleManager::displayInvoice(const std::string& maHD) {
    // 1. Tìm thông tin Master (Hóa đơn tổng)
    NodeInvoice* tmpInvoice = invoiceHead;
    while (tmpInvoice != NULL && tmpInvoice->data.maHD != maHD) {
        tmpInvoice = tmpInvoice->next;
    }

    if (tmpInvoice == NULL) {
        cout << "\n=> Loi: Khong tim thay hoa don mang ma " << maHD << "!\n";
        return; 
    }

    Invoice inv = tmpInvoice->data;

    // 2. In Header
    cout << "\n==========================================================\n";
    cout << "                   BIEN LAI THANH TOAN                    \n";
    cout << "==========================================================\n";
    cout << "So HD:      " << inv.maHD << "\n";
    cout << "Ngay lap:   " << inv.ngayLap << "/" << inv.thangLap << "/" << inv.namLap << "\n";
    cout << "Ma Khach:   " << inv.maKH << "\n";
    cout << "----------------------------------------------------------\n";
    
    // Tạo tiêu đề cột sản phẩm
    cout << left << setw(10) << "Ma SP" 
         << setw(15) << "So luong" 
         << setw(15) << "Don gia" 
         << setw(15) << "Thanh tien" << "\n";
    cout << "----------------------------------------------------------\n";

    // 3. Quét danh sách Detail để in các món hàng thuộc hóa đơn này
    NodeInvoiceDetail* tmpDetail = detailHead;
    bool hasDetails = false;
    
    while (tmpDetail != NULL) {
        if (tmpDetail->data.maHD == maHD) {
            cout << left << setw(10) << tmpDetail->data.maSP
                 << setw(15) << tmpDetail->data.soLuong
                 << setw(15) << tmpDetail->data.donGia
                 << setw(15) << tmpDetail->data.thanhTien << "\n";
            hasDetails = true;
        }
        tmpDetail = tmpDetail->next;
    }

    if (!hasDetails) {
        cout << "  (Khong co chi tiet san pham nao)\n";
    }

    // 4. In Footer (Tổng tiền bạc)
    cout << "----------------------------------------------------------\n";
    cout << "Tong tien hang:   " << inv.tongTienHang << " VND\n";
    cout << "Thue VAT (10%):   " << inv.thueVAT << " VND\n";
    
    if (inv.tienGiamGia > 0) {
        cout << "Giam gia (Diem): -" << inv.tienGiamGia << " VND\n";
    }
    
    cout << "=> CAN THANH TOAN:" << inv.tongThanhToan << " VND\n";
    cout << "----------------------------------------------------------\n";
    cout << "Tien khach dua:   " << inv.tienKhachTra << " VND\n";
    cout << "Tien thoi lai:    " << inv.tienTraLai << " VND\n";
    cout << "==========================================================\n";
}