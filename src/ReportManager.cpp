#include "ReportManager.h"
#include <iostream>
#include <algorithm>  // swap()
#include <iomanip>    // setw(), left
using namespace std;

// Thêm hàm trim ở đầu file ReportManager.cpp
static std::string trim(const std::string& s) {
    int start = s.find_first_not_of(" \t\r\n");
    int end   = s.find_last_not_of(" \t\r\n");
    return (start == std::string::npos) ? "" : s.substr(start, end - start + 1);
}


void ReportManager::reportRevenue(const SaleManager& sm) {
    int nam, thang;
    cout << "Nhap nam: ";
    cin  >> nam;
    cout << "Nhap thang (nhap 0 de xem ca nam): ";
    cin  >> thang;
    //bao cao nhung thong so don gian
    // Biến tích lũy
    int    soHD          = 0;
    double tongTienHang  = 0;
    double tongVAT       = 0;
    double tongThanhToan = 0;

    // Duyệt linked list hóa đơn
    NodeInvoice* cur = sm.getInvoiceHead();
    while (cur != NULL) {
        Invoice& inv = cur->data;

        bool dung_nam   = (inv.namLap == nam);
        bool dung_thang = (thang == 0) || (inv.thangLap == thang);

        if (dung_nam && dung_thang) {
            soHD++;
            tongTienHang  += inv.tongTienHang;
            tongVAT       += inv.thueVAT;
            tongThanhToan += inv.tongThanhToan;
        }

        cur = cur->next;
    }

    // Hiển thị
    if (thang == 0)
        cout << "\n=== DOANH THU NAM " << nam << " ===\n";
    else
        cout << "\n=== DOANH THU THANG " << thang << "/" << nam << " ===\n";

    if (soHD == 0) {
        cout << "=> Khong co hoa don nao trong ky nay.\n";
        return;
    }

    cout << "So hoa don     : " << soHD << "\n";
    cout << fixed << setprecision(0);
    cout << "Tong tien hang : " << tongTienHang  << " VND\n";
    cout << "Thue VAT       : " << tongVAT       << " VND\n";
    cout << "Tong thanh toan: " << tongThanhToan << " VND\n";
    cout << defaultfloat; // Reset lai dinh dang sau khi in xong
}
void ReportManager::getTop10BestSellers(const SaleManager& sm, const ProductManager& pm) {
    int nam, thang;
    cout << "Nhap nam  (vd: 2026): "; cin >> nam;
    cout << "Nhap thang (1-12)   : "; cin >> thang;

    // ── Bước 1: Tổng hợp doanh thu theo sản phẩm ──
    // Không dùng mảng maHD trung gian (tránh overflow khi có hàng nghìn HD).
    // Thay vào đó: với mỗi chi tiết, duyệt thẳng qua linked list hóa đơn
    // để kiểm tra tháng/năm hợp lệ.
    const int MAX_SP = 1000;   // đủ chứa số loại SP khác nhau
    string dsMaSP[MAX_SP];
    int    dsSoLuong[MAX_SP]  = {};
    double dsDoanhThu[MAX_SP] = {};
    int    n = 0;

    NodeInvoiceDetail* curDet = sm.getDetailHead();
    while (curDet != nullptr) {
        InvoiceDetail& det = curDet->data;

        // Tìm hóa đơn tương ứng trong linked list để lấy thang/nam
        bool hopLe = false;
        NodeInvoice* curInv = sm.getInvoiceHead();
        while (curInv != nullptr) {
            if (trim(curInv->data.maHD) == trim(det.maHD)) {
                if (curInv->data.namLap == nam && curInv->data.thangLap == thang)
                    hopLe = true;
                break;   // đã tìm thấy HD → dừng
            }
            curInv = curInv->next;
        }

        if (hopLe) {
            // Tìm maSP đã tồn tại trong mảng chưa
            int viTri = -1;
            for (int i = 0; i < n; i++) {
                if (trim(dsMaSP[i]) == trim(det.maSP)) { viTri = i; break; }
            }
            if (viTri != -1) {
                dsSoLuong[viTri]  += det.soLuong;
                dsDoanhThu[viTri] += det.thanhTien;
            } else if (n < MAX_SP) {
                dsMaSP[n]      = trim(det.maSP);
                dsSoLuong[n]   = det.soLuong;
                dsDoanhThu[n]  = det.thanhTien;
                n++;
            }
        }
        curDet = curDet->next;
    }

    // ── Bước 2: Kiểm tra kết quả ──
    if (n == 0) {
        cout << "\n=> Khong co du lieu ban hang trong thang "
             << thang << "/" << nam << "!\n";
        return;
    }

    // ── Bước 3: Selection Sort theo doanhThu giảm dần ──
    for (int i = 0; i < n - 1; i++) {
        int maxIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (dsDoanhThu[j] > dsDoanhThu[maxIdx])
                maxIdx = j;
        }
        if (maxIdx != i) {
            swap(dsMaSP[i],     dsMaSP[maxIdx]);
            swap(dsSoLuong[i],  dsSoLuong[maxIdx]);
            swap(dsDoanhThu[i], dsDoanhThu[maxIdx]);
        }
    }

    // ── Bước 4: In kết quả ──
    int top = (n < 10) ? n : 10;
    cout << "\n=== TOP " << top << " SP BAN CHAY THANG "
         << thang << "/" << nam << " ===\n";
    cout << left  << setw(4)  << "STT"
                  << setw(10) << "Ma SP"
                  << setw(30) << "Ten SP"
                  << setw(10) << "So luong"
         << right << setw(18) << "Doanh thu" << "\n";
    cout << string(72, '-') << "\n";

    cout << fixed << setprecision(0);
    for (int i = 0; i < top; i++) {
        const Product* sp = pm.getProduct(dsMaSP[i]);
        string tenSP = (sp != nullptr) ? sp->tenSP : "(khong ro)";
        cout << left  << setw(4)  << (i + 1)
                      << setw(10) << dsMaSP[i]
                      << setw(30) << tenSP
                      << setw(10) << dsSoLuong[i]
             << right << setw(15) << dsDoanhThu[i] << " VND\n";
    }
    cout << defaultfloat;
}