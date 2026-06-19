#include <fstream>
#include <iostream>
#include <iomanip>
#include <ctime>
#include "SaleManager.h"
#include <fstream>  // Dùng để tạo luồng Đọc/Ghi file
#include <sstream>  // Dùng để chặt chuỗi văn bản theo dấu '|'

using namespace std;

// Hàm khởi tạo
SaleManager::SaleManager(){
    invoiceHead = NULL;
    detailHead  = NULL;
}

// Thêm chi tiết sản phẩm vào hóa đơn (private)
void SaleManager::addInvoiceDetails(const std::string& maHD, const ProductManager& pm) {
    int tiepTuc = 1;
    cout << "Bat dau \n";

    while (tiepTuc == 1) {
        InvoiceDetail detail;
        detail.maHD = maHD;
        detail.chietKhau = 0;

        cout << "Nhap ma san pham (hoac nhap '?' de tim kiem theo ten): ";
        cin >> detail.maSP;

        // Bổ sung luồng tìm kiếm nếu người dùng nhập '?'
        if (detail.maSP == "?") {
            string tuKhoa;
            cout << "=> Nhap ten san pham hoac tu khoa can tim: ";
            cin.ignore();
            getline(cin, tuKhoa);

            // Tìm kiếm - nếu không có kết quả thì quay lại đầu vòng lặp
            bool coKetQua = pm.searchProduct(tuKhoa);
            if (!coKetQua) {
                cout << "=> Khong co san pham nao phu hop. Vui long thu lai!\n";
                continue; // Quay lại đầu while, không hỏi thêm gì
            }

            cout << "\n=> Vui long nhap ma san pham ban muon chon tu danh sach tren: ";
            cin >> detail.maSP;
        }

        // Sau đó tiếp tục lấy dữ liệu như cũ
        const Product* spData = pm.getProduct(detail.maSP);

        if (spData == NULL) {
            cout << "=> Loi: San pham khong ton tai trong kho. Vui long thu lai!\n";
            continue; 
        } else {
            cout << "Nhap So luong (" << spData->tenSP << "): ";
            cin >> detail.soLuong;

            detail.donGia   = spData->donGia;
            //vì nó còn được sử dụng nên tạo 1 biến 
            double tongTruocCK = detail.soLuong * detail.donGia;
            double phanTramCK;
            cout << "Nhap chiet khau (%, nhap 0 neu khong co): ";
            cin >> phanTramCK;
            if (phanTramCK < 0) phanTramCK = 0;
            if (phanTramCK > 100) {
                cout << "=> Loi: Chiet khau vuot qua 100%, tu dong dat ve 0.\n";
                phanTramCK = 0;
            }
            detail.chietKhau = tongTruocCK * phanTramCK / 100.0;
            detail.thanhTien = tongTruocCK - detail.chietKhau;

            if (detail.chietKhau > 0)
            cout << "=> Chiet khau " << phanTramCK << "%: -"
                     << detail.chietKhau << " VND\n";
    
            NodeInvoiceDetail* newNode = new NodeInvoiceDetail;
            newNode->data = detail;
            newNode->next = detailHead;
            detailHead    = newNode;

            cout << " Da them: " << detail.soLuong << " x " << spData->tenSP
                 << " = " << detail.thanhTien << " VND\n";
        }

        cout << "Tiep tuc them san pham? (1: Co / 0: Khong): ";
        cin >> tiepTuc;
    }
}

// Tính tổng tiền hàng của 1 hóa đơn (private)
double SaleManager::calculateTotal(const std::string& maHD){
    double tongTienHang = 0.0;
    NodeInvoiceDetail* tmp = detailHead;
    while (tmp != NULL){
        if (tmp->data.maHD == maHD)
            tongTienHang += tmp->data.thanhTien;
        tmp = tmp->next;
    }
    return tongTienHang;
}

// Tạo hóa đơn mới
void SaleManager::createInvoice(CustomerManager& cm, const ProductManager& pm) {
    Invoice newInvoice;

    // BƯỚC 1: Tự sinh mã và lấy thời gian
    int cnt = 1;
    NodeInvoice* tmp = invoiceHead;
    while (tmp != NULL){ cnt++; tmp = tmp->next; }
    newInvoice.maHD = "HD" + std::to_string(cnt);

    time_t now = time(0);
    tm* ltm = localtime(&now);
    newInvoice.ngayLap  = ltm->tm_mday;
    newInvoice.thangLap = 1 + ltm->tm_mon;
    newInvoice.namLap   = 1900 + ltm->tm_year;

    // BƯỚC 2: Nhập và xác thực mã khách hàng
    cout << "\n================= QUAY THANH TOAN =================\n";
    cout << "=> Dang tao moi Hoa Don: " << newInvoice.maHD << "\n";
    cin.ignore(); // Xoa bo dem sau lan cin >> cuoi cung
    
    while (true) {
        cout << "Nhap ma khach hang (Enter de bo qua): ";
        std::getline(cin, newInvoice.maKH);
        
        if (newInvoice.maKH.empty()) {
            cout << "=> Khach hang: (Khach le - khong luu ma KH)\n";
            newInvoice.maKH = "KH00"; // <--- THÊM DÒNG NÀY ĐỂ CHỐT MÃ
            break;
        }
        
        Customer* khData = cm.getCustomer(newInvoice.maKH);
        
        if (khData != NULL) {
            cout << "=> Khach hang: " << khData->tenKH
                 << " | SDT: " << khData->SDT << "\n";
            break;
        } else {
            cout << "=> Loi: Khong tim thay ma KH \"" << newInvoice.maKH
                 << "\". Vui long nhap lai.\n";
        }
    }

    // BƯỚC 3: Quét sản phẩm
    cout << "\n================= QUAY THANH TOAN =================\n";
    cout << "=> Dang tao moi Hoa Don: " << newInvoice.maHD << "\n";
    addInvoiceDetails(newInvoice.maHD, pm);

    // BƯỚC 4:tính tiền
    newInvoice.tongTienHang = calculateTotal(newInvoice.maHD);
    newInvoice.thueVAT      = newInvoice.tongTienHang * 0.1;
    newInvoice.tongThanhToan  = newInvoice.tongTienHang + newInvoice.thueVAT;
    // BƯỚC 5: Hiển thị tổng kết
    cout << "\n---------------- TONG KET ----------------\n";
    cout << "Tong tien hang: " << newInvoice.tongTienHang  << " VND\n";
    cout << "Thue VAT (10%): " << newInvoice.thueVAT       << " VND\n";
    cout << "=> KHACH CAN TRA: " << newInvoice.tongThanhToan << " VND\n";
    cout << "------------------------------------------\n";

    // BƯỚC 6: Thu tiền mặt
    do {
        cout << "Tien khach dua: ";
        cin >> newInvoice.tienKhachTra;
        if (newInvoice.tienKhachTra < newInvoice.tongThanhToan)
            cout << "=> Loi: Tien khach dua khong du! Vui long nhap lai.\n";
    } while (newInvoice.tienKhachTra < newInvoice.tongThanhToan);

    newInvoice.tienTraLai = newInvoice.tienKhachTra - newInvoice.tongThanhToan;
    cout << "Tien thoi lai:  " << newInvoice.tienTraLai << " VND\n";

    // BƯỚC 6: Lưu vào linked list
    NodeInvoice* newNode = new NodeInvoice;
    newNode->data = newInvoice;
    newNode->next = invoiceHead;
    invoiceHead   = newNode;

    cout << "\n=> GIAO DICH THANH CONG. DA LUU VAO HE THONG!\n";

    char inHD;
    cout << "Ban co muon in hoa don khong? (y/n): ";
    cin >> inHD;
    if (inHD == 'y' || inHD == 'Y') {
        printInvoice(newInvoice.maHD);
    }
}

// Hiển thị chi tiết 1 hóa đơn theo mã
void SaleManager::printInvoice(const std::string& maHD) {
    NodeInvoice* tmpInvoice = invoiceHead;
    while (tmpInvoice != NULL && tmpInvoice->data.maHD != maHD)
        tmpInvoice = tmpInvoice->next;

    if (tmpInvoice == NULL) {
        cout << "\n=> Loi: Khong tim thay hoa don mang ma " << maHD << "!\n";
        return;
    }
    Invoice inv = tmpInvoice->data;

    cout << "\n==========================================================\n";
    cout << "                   BIEN LAI THANH TOAN\n";
    cout << "==========================================================\n";
    cout << "So HD:      " << inv.maHD << "\n";
    cout << "Ngay lap:   " << inv.ngayLap << "/" << inv.thangLap << "/" << inv.namLap << "\n";
    cout << "Ma Khach:   " << inv.maKH << "\n";
    cout << "----------------------------------------------------------\n";
    cout << left << setw(10) << "Ma SP"
         << setw(15) << "So luong"
         << setw(15) << "Don gia"
         << setw(15) << "Thanh tien" << "\n";
    cout << "----------------------------------------------------------\n";

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
    if (!hasDetails) cout << "  (Khong co chi tiet san pham nao)\n";

    cout << "----------------------------------------------------------\n";
    cout << "Tong tien hang:   " << inv.tongTienHang  << " VND\n";
    cout << "Thue VAT (10%):   " << inv.thueVAT       << " VND\n";
    cout << "=> CAN THANH TOAN:" << inv.tongThanhToan  << " VND\n";
    cout << "----------------------------------------------------------\n";
    cout << "Tien khach dua:   " << inv.tienKhachTra  << " VND\n";
    cout << "Tien thoi lai:    " << inv.tienTraLai    << " VND\n";
    cout << "==========================================================\n";
}

// Hiển thị danh sách tóm tắt tất cả hóa đơn
void SaleManager::displayAllInvoices() const {
    if (invoiceHead == NULL) {
        cout << "=> Chua co hoa don nao trong he thong.\n";
        return;
    }
    cout << "\n====================================================================\n";
    cout << "                    DANH SACH TAT CA HOA DON\n";
    cout << "====================================================================\n";
    cout << left  << setw(8)  << "Ma HD"
         << setw(14) << "Ngay lap"
         << setw(10) << "Ma KH"
         << right << setw(14) << "Thanh toan" << "\n";
    cout << "--------------------------------------------------------------------\n";
    NodeInvoice* cur = invoiceHead;
    while (cur != NULL) {
        Invoice& inv = cur->data;
        string ngay = to_string(inv.ngayLap) + "/" + to_string(inv.thangLap) + "/" + to_string(inv.namLap);
        cout << left  << setw(8)  << inv.maHD
             << setw(14) << ngay
             << setw(10) << inv.maKH
             << right << setw(14) << fixed << setprecision(0)
             << inv.tongThanhToan << " VND\n";
        cur = cur->next;
    }
    cout << "====================================================================\n";
}

// Getters để ReportManager có thể truy xuất
NodeInvoice*       SaleManager::getInvoiceHead() const { return invoiceHead; }
NodeInvoiceDetail* SaleManager::getDetailHead()  const { return detailHead;  }

// Hiện lịch sử giao dịch của một khách hàng theo mã KH
void SaleManager::hienThiLichSuKH(const std::string& maKH) const {
    cout << "\n====== LICH SU GIAO DICH KH: " << maKH << " ======\n";
    cout << left  << setw(12) << "Ma HD"
                  << setw(15) << "Ngay lap"
         << right << setw(20) << "Tong thanh toan" << "\n";
    cout << string(47, '-') << "\n";

    bool coHD = false;
    NodeInvoice* cur = invoiceHead;

    while (cur != nullptr) {
        if (cur->data.maKH == maKH) {
            // Định dạng ngày: DD/MM/YYYY
            string ngay = to_string(cur->data.ngayLap)  + "/" +
                          to_string(cur->data.thangLap) + "/" +
                          to_string(cur->data.namLap);

            cout << fixed << setprecision(0);
            cout << left  << setw(12) << cur->data.maHD
                          << setw(15) << ngay
                 << right << setw(20) << cur->data.tongThanhToan << " VND\n";
            coHD = true;
        }
        cur = cur->next;
    }

    if (!coHD)
        cout << "=> Khach hang nay chua co giao dich nao.\n";

    cout << defaultfloat;
}


// ====================================================================
// ── GHI FILE ──
// ====================================================================
void SaleManager::saveToFile(const std::string& invFile, const std::string& detFile) const {
    // 1. Ghi hoa don tong (Master)
    std::ofstream fInv(invFile);
    if (!fInv.is_open()) {
        std::cout << "=> Loi: Khong mo duoc file " << invFile << " de ghi!\n";
        return;
    }
    NodeInvoice* cur = invoiceHead;
    while (cur != NULL) {
        Invoice& inv = cur->data;
        fInv << inv.maHD          << "|"
             << inv.maKH          << "|"
             << inv.ngayLap       << "|"
             << inv.thangLap      << "|"
             << inv.namLap        << "|"
             << inv.tongTienHang  << "|"
             << inv.thueVAT       << "|"
             << inv.tongThanhToan << "|"
             << inv.tienKhachTra  << "|"
             << inv.tienTraLai    << "\n";
        cur = cur->next;
    }
    fInv.close();

    // 2. Ghi chi tiet hoa don (Detail)
    std::ofstream fDet(detFile);
    if (!fDet.is_open()) {
        std::cout << "=> Loi: Khong mo duoc file " << detFile << " de ghi!\n";
        return;
    }
    NodeInvoiceDetail* curD = detailHead;
    while (curD != NULL) {
        InvoiceDetail& det = curD->data;
        fDet << det.maHD      << "|"
             << det.maSP      << "|"
             << det.soLuong   << "|"
             << det.donGia    << "|"
             << det.chietKhau << "|"
             << det.thanhTien << "\n";
        curD = curD->next;
    }
    fDet.close();
    
    std::cout << "=> Da luu toan bo du lieu ban hang thanh cong!\n";
}

// ====================================================================
// ── DOC FILE ──
// ====================================================================
void SaleManager::loadFromFile(const std::string& invFile, const std::string& detFile) {
    // 1. Doc hoa don tong (Master)
    std::ifstream fInv(invFile);
    if (fInv.is_open()) {
        std::string line;
        NodeInvoice* invoiceTail = nullptr;

        while (std::getline(fInv, line)) {
            if (line.empty()) continue;

            std::stringstream ss(line);
            Invoice inv;
            std::string tempStr;

            std::getline(ss, inv.maHD, '|');
            std::getline(ss, inv.maKH, '|');

            std::getline(ss, tempStr, '|'); inv.ngayLap = std::stoi(tempStr);
            std::getline(ss, tempStr, '|'); inv.thangLap = std::stoi(tempStr);
            std::getline(ss, tempStr, '|'); inv.namLap = std::stoi(tempStr);

            std::getline(ss, tempStr, '|'); inv.tongTienHang = std::stod(tempStr);
            std::getline(ss, tempStr, '|'); inv.thueVAT = std::stod(tempStr);
            std::getline(ss, tempStr, '|'); inv.tongThanhToan = std::stod(tempStr);
            std::getline(ss, tempStr, '|'); inv.tienKhachTra = std::stod(tempStr);
            
            std::getline(ss, tempStr);      inv.tienTraLai = std::stod(tempStr);

            NodeInvoice* newNode = new NodeInvoice;
            newNode->data = inv;
            newNode->next = nullptr;

            if (invoiceHead == nullptr) {
                invoiceHead = newNode;
                invoiceTail = newNode;
            } else {
                invoiceTail->next = newNode;
                invoiceTail = newNode;
            }
        }
        fInv.close();
        std::cout << "=> Da doc du lieu tu " << invFile << " len he thong.\n"; 
    } else {
        std::cout << "=> File " << invFile << " chua ton tai. He thong se tao moi khi luu.\n";
    }

    // 2. Doc chi tiet hoa don (Detail)
    std::ifstream fDet(detFile);
    if (fDet.is_open()) {
        std::string line;
        NodeInvoiceDetail* detailTail = nullptr;

        while (std::getline(fDet, line)) {
            if (line.empty()) continue;

            std::stringstream ss(line);
            InvoiceDetail det;
            std::string tempStr;

            std::getline(ss, det.maHD, '|');
            std::getline(ss, det.maSP, '|');

            std::getline(ss, tempStr, '|'); det.soLuong = std::stoi(tempStr);
            std::getline(ss, tempStr, '|'); det.donGia = std::stod(tempStr);
            std::getline(ss, tempStr, '|'); det.chietKhau = std::stod(tempStr);
            
            std::getline(ss, tempStr);      det.thanhTien = std::stod(tempStr);

            NodeInvoiceDetail* newNode = new NodeInvoiceDetail;
            newNode->data = det;
            newNode->next = nullptr;

            if (detailHead == nullptr) {
                detailHead = newNode;
                detailTail = newNode;
            } else {
                detailTail->next = newNode;
                detailTail = newNode;
            }
        }
        fDet.close();
        std::cout << "=> Da doc du lieu tu " << detFile << " len he thong.\n";
    } else {
        std::cout << "=> File " << detFile << " chua ton tai. He thong se tao moi khi luu.\n";
    }
}