#include "ReportManager.h"
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>  // min(), swap()
#include <iomanip>    // setw(), left
using namespace std;


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
    // map: maHD → có thuộc tháng/năm cần không
    map<string, bool> hdHopLe;

    NodeInvoice* curInv = sm.getInvoiceHead();
    while (curInv != NULL) {
        Invoice& inv = curInv->data;
        if (inv.namLap == nam && inv.thangLap == thang){
            hdHopLe[inv.maHD] = true;
        }
        curInv = curInv->next;
}
    map<string, double> doanhThuSP;  // maSP → tổng thanhTien
    map<string, int>    soLuongSP;   // maSP → tổng soLuong

    NodeInvoiceDetail* curDet = sm.getDetailHead();
    while (curDet != NULL) {
        InvoiceDetail& det = curDet->data;
    // Chỉ tính nếu HD thuộc tháng đã chọn
        if (hdHopLe.count(det.maHD)) {
            doanhThuSP[det.maSP] += det.thanhTien;
            soLuongSP[det.maSP]  += det.soLuong;
    }
    curDet = curDet->next;
}
// Struct tạm để sort
    struct SPStat {
        string maSP;
        int    soLuong;
        double doanhThu;
};
// Đổ map vào vector
    vector<SPStat> dsStat;
    for (auto& kv : doanhThuSP) {
        SPStat s;
        s.maSP     = kv.first;
        s.soLuong  = soLuongSP[kv.first];
        s.doanhThu = kv.second;
        dsStat.push_back(s);
}
    int n = dsStat.size();
    for (int i = 0; i < n - 1; i++) {
        int maxIdx = i;
        for (int j = i + 1; j < n; j++){
        if (dsStat[j].doanhThu > dsStat[maxIdx].doanhThu)
            maxIdx = j;
        }

    // Đưa phần tử lớn nhất về đúng vị trí i
        if (maxIdx != i)
        swap(dsStat[i], dsStat[maxIdx]);
}
    int top = min((int)dsStat.size(), 10);

    cout << "\n=== TOP " << top << " SP BAN CHAY THANG "
         << thang << "/" << nam << " ===\n";
    cout << left << setw(4)  << "STT"
                 << setw(10) << "Ma SP"
                 << setw(50) << "Ten SP"
                 << setw(10) << "So luong"
                 << setw(18) << "Doanh thu" << "\n";
    cout << string(92, '-') << "\n";

    cout << fixed << setprecision(0);
    for (int i = 0; i < top; i++) {
        const Product* sp = pm.getProduct(dsStat[i].maSP);
        string tenSP = (sp != NULL) ? sp->tenSP : "(khong ro)";
        cout << left  << setw(4)  << (i + 1)
                      << setw(10) << dsStat[i].maSP
                      << setw(50) << tenSP
                      << setw(10) << dsStat[i].soLuong
                      << right << setw(15) << dsStat[i].doanhThu << " VND\n";
    }
    cout << defaultfloat;
}
