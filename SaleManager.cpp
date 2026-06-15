#include <iostream>
#include <iomanip>
#include "SaleManager.h"

using namespace std;

// ================================================================
// KHỞI TẠO
// ================================================================
SaleManager::SaleManager() {
    invoiceHead = nullptr;
    detailHead  = nullptr;
}

// ================================================================
// HÀM PRIVATE 1: isInvoiceExist
//   Mục đích: duyệt invoiceHead, kiểm tra maHD đã tồn tại chưa
//   Trả về : true nếu trùng, false nếu chưa có
// ================================================================
bool SaleManager::isInvoiceExist(const string& maHD) {
    NodeInvoice* cur = invoiceHead;
    while (cur != nullptr) {
        if (cur->data.maHD == maHD)
            return true;
        cur = cur->next;
    }
    return false;
}

// ================================================================
// HÀM PRIVATE 2: addInvoiceDetails
//   Mục đích: vòng lặp nhập từng sản phẩm khách mua
//   Input   : maHD (để gắn vào chi tiết), pm (tra cứu giá)
//   Output  : các node InvoiceDetail được thêm vào detailHead
// ================================================================
void SaleManager::addInvoiceDetails(const string& maHD, const ProductManager& pm) {
    char tiepTuc;
    do {
        InvoiceDetail ct;
        ct.maHD = maHD; // Gắn mã hóa đơn cha vào từng dòng chi tiết

        // Bước 1: Nhập mã sản phẩm
        cout << "  Nhap ma san pham: ";
        cin >> ct.maSP;

        // Bước 2: Kiểm tra sản phẩm có tồn tại không
        const Product* sp = pm.getProduct(ct.maSP);
        if (sp == nullptr) {
            cout << "  [!] Ma san pham khong ton tai. Bo qua dong nay.\n";
            cout << "  Tiep tuc them san pham? (y/n): ";
            cin >> tiepTuc;
            continue; // Quay lại đầu vòng lặp, bỏ qua dòng này
        }

        // Bước 3: Lấy giá từ danh mục, hiển thị cho thu ngân xác nhận
        ct.donGia = sp->donGia;
        cout << "  [" << sp->tenSP << "] - Don gia: "
             << fixed << setprecision(0) << ct.donGia << " VND\n";

        // Bước 4: Nhập số lượng
        cout << "  So luong: ";
        cin >> ct.soLuong;

        // Bước 5: Nhập chiết khấu
        cout << "  Chiet khau (%): ";
        cin >> ct.chietKhau;

        // Bước 6: Tính thành tiền
        // Công thức: thanhTien = donGia * soLuong * (1 - chietKhau/100)
        ct.thanhTien = ct.donGia * ct.soLuong * (1.0 - ct.chietKhau / 100.0);
        cout << "  => Thanh tien: " << ct.thanhTien << " VND\n";

        // Bước 7: Tạo node mới, thêm vào đầu detailHead
        NodeInvoiceDetail* newNode = new NodeInvoiceDetail;
        newNode->data = ct;
        newNode->next = detailHead;
        detailHead    = newNode;

        cout << "  Tiep tuc them san pham? (y/n): ";
        cin >> tiepTuc;

    } while (tiepTuc == 'y' || tiepTuc == 'Y');
}

// ================================================================
// HÀM PRIVATE 3: caculateTotal
//   Mục đích: duyệt detailHead, cộng thanhTien của đúng hóa đơn
//   Lý do cần lọc theo maHD: vì detailHead chứa chi tiết của
//   TẤT CẢ hóa đơn, không riêng hóa đơn hiện tại
// ================================================================
double SaleManager::caculateTotal(const string& maHD) {
    double tong = 0.0;
    NodeInvoiceDetail* cur = detailHead;
    while (cur != nullptr) {
        if (cur->data.maHD == maHD)      // Chỉ cộng đúng hóa đơn này
            tong += cur->data.thanhTien;
        cur = cur->next;
    }
    return tong;
}

// ================================================================
// HÀM PUBLIC: createInvoice
//
//   PHASE 1 - Thiết lập thông tin chung:
//             Nhập maHD (kiểm tra trùng), ngày lập, maKH (kiểm tra tồn tại)
//
//   PHASE 2 - Gọi trợ thủ xử lý mua hàng:
//             addInvoiceDetails → caculateTotal
//
//   PHASE 3 - Tính thuế & thanh toán:
//             VAT 10%, nhập tiền khách, tính tiền thối
//
//   PHASE 4 - Cộng điểm & lưu hóa đơn:
//             Cộng điểm tích lũy, thêm node vào invoiceHead
// ================================================================
void SaleManager::createInvoice(CustomerManager& cm, const ProductManager& pm) {
    Invoice newInvoice;
    cout << "\n================= LAP HOA DON MOI =================\n";

    // ─────────────────────────────────────────────────────────
    // PHASE 1: THIẾT LẬP THÔNG TIN CHUNG (MASTER INFO)
    // ─────────────────────────────────────────────────────────

    // Nhập mã hóa đơn và kiểm tra trùng
    do {
        cout << "Nhap Ma Hoa Don: ";
        cin >> newInvoice.maHD;
        if (isInvoiceExist(newInvoice.maHD))
            cout << "[!] Ma hoa don da ton tai! Vui long nhap ma khac.\n";
    } while (isInvoiceExist(newInvoice.maHD));

    // Nhập ngày lập (thủ công để tiện kiểm thử nhiều ngày khác nhau)
    // cin.ignore() xóa ký tự '\n' còn trong buffer sau cin >>
    cout << "Nhap ngay lap (VD: 14/06/2026): ";
    cin.ignore();
    getline(cin, newInvoice.thoiGianLap);

    // Nhập mã khách hàng và kiểm tra tồn tại
    // KH00 = khách vãng lai (không cần có trong hệ thống)
    cout << "Nhap Ma Khach Hang (KH00 = khach vang lai): ";
    cin >> newInvoice.maKH;

    if (newInvoice.maKH != "KH00") {
        const Customer* kh = cm.getCustomer(newInvoice.maKH);
        if (kh == nullptr) {
            cout << "[!] Khach hang khong ton tai! Huy tao hoa don.\n";
            return; // Dừng hàm, không tạo hóa đơn
        }
        // Hiển thị tên khách để thu ngân xác nhận đúng người
        cout << "Khach hang: " << kh->tenKH
             << " | Diem hien tai: " << kh->diemTichluy << "\n";
    }

    // ─────────────────────────────────────────────────────────
    // PHASE 2: GỌI TRỢ THỦ ĐỂ MUA HÀNG & TÍNH TIỀN HÀNG
    // ─────────────────────────────────────────────────────────

    cout << "\n--- NHAP SAN PHAM ---\n";
    // 1. Thu ngân quét mã vạch từng sản phẩm
    addInvoiceDetails(newInvoice.maHD, pm);

    // 2. Kế toán chốt tổng tiền hàng từ chi tiết vừa nhập
    newInvoice.tongTienHang = caculateTotal(newInvoice.maHD);

    // ─────────────────────────────────────────────────────────
    // PHASE 3: TÍNH THUẾ & THANH TOÁN
    // ─────────────────────────────────────────────────────────

    newInvoice.thueVAT       = newInvoice.tongTienHang * 0.1;  // VAT 10%
    newInvoice.tongThanhToan = newInvoice.tongTienHang + newInvoice.thueVAT;

    cout << "\n---------------- TONG KET HOA DON ----------------\n";
    cout << "Tong tien hang : " << newInvoice.tongTienHang << " VND\n";
    cout << "Thue VAT (10%) : " << newInvoice.thueVAT      << " VND\n";
    cout << "KHACH CAN TRA  : " << newInvoice.tongThanhToan << " VND\n";
    cout << "---------------------------------------------------\n";

    // Vòng lặp nhận tiền - chống lỗi nhập thiếu tiền
    do {
        cout << "Nhap so tien khach dua: ";
        cin >> newInvoice.tienKhachTra;
        if (newInvoice.tienKhachTra < newInvoice.tongThanhToan)
            cout << "[!] So tien khach dua khong du! Vui long nhap lai.\n";
    } while (newInvoice.tienKhachTra < newInvoice.tongThanhToan);

    newInvoice.tienTraLai = newInvoice.tienKhachTra - newInvoice.tongThanhToan;
    cout << "Tien tra lai   : " << newInvoice.tienTraLai << " VND\n";

    // ─────────────────────────────────────────────────────────
    // PHASE 4: CỘNG ĐIỂM TÍCH LŨY & LƯU HÓA ĐƠN
    // ─────────────────────────────────────────────────────────

    // Cộng điểm cho khách thành viên (không cộng cho KH00)
    // Quy tắc: cứ 10,000 VND thanh toán = 1 điểm
    if (newInvoice.maKH != "KH00") {
        int diemCong = (int)(newInvoice.tongThanhToan / 10000);
        if (diemCong > 0) {
            // Lấy bản sao thông tin khách, cộng điểm, rồi cập nhật lại
            Customer kh = *cm.getCustomer(newInvoice.maKH);
            kh.diemTichluy += diemCong;
            cm.updateCustomer(kh.maKH, kh);
            cout << "[+] Cong " << diemCong << " diem tich luy. Tong diem: "
                 << kh.diemTichluy << "\n";
        }
    }

    // Tạo node mới và thêm vào đầu danh sách hóa đơn (O(1))
    NodeInvoice* newNode = new NodeInvoice;
    newNode->data = newInvoice;
    newNode->next = invoiceHead;
    invoiceHead   = newNode;

    cout << "======== HOA DON " << newInvoice.maHD << " DA LUU THANH CONG ========\n";
}

// ================================================================
// HÀM PUBLIC: displayInvoice
//   Tìm hóa đơn theo maHD, in thông tin đầu + bảng chi tiết
// ================================================================
void SaleManager::displayInvoice(const string& maHD) {
    // Tìm hóa đơn trong invoiceHead
    NodeInvoice* curHD = invoiceHead;
    while (curHD != nullptr && curHD->data.maHD != maHD)
        curHD = curHD->next;

    if (curHD == nullptr) {
        cout << "[!] Khong tim thay hoa don co ma: " << maHD << "\n";
        return;
    }

    const Invoice& hd = curHD->data;

    // In header hóa đơn
    cout << "\n====================================================\n";
    cout << "              HOA DON BAN HANG\n";
    cout << "====================================================\n";
    cout << left << setw(18) << "Ma hoa don:"    << hd.maHD        << "\n";
    cout << left << setw(18) << "Ma khach hang:" << hd.maKH        << "\n";
    cout << left << setw(18) << "Ngay lap:"      << hd.thoiGianLap << "\n";
    cout << "----------------------------------------------------\n";

    // In bảng chi tiết sản phẩm
    cout << "| " << left  << setw(8)  << "Ma SP"
         << "| " << right << setw(5)  << "SL"
         << "| " << right << setw(12) << "Don gia"
         << "| " << right << setw(7)  << "CK(%)"
         << "| " << right << setw(13) << "Thanh tien"
         << " |\n";
    cout << "----------------------------------------------------\n";

    NodeInvoiceDetail* curCT = detailHead;
    while (curCT != nullptr) {
        if (curCT->data.maHD == maHD) {
            const InvoiceDetail& ct = curCT->data;
            cout << "| " << left  << setw(8)  << ct.maSP
                 << "| " << right << setw(5)  << ct.soLuong
                 << "| " << right << setw(12) << fixed << setprecision(0) << ct.donGia
                 << "| " << right << setw(7)  << ct.chietKhau
                 << "| " << right << setw(13) << ct.thanhTien
                 << " |\n";
        }
        curCT = curCT->next;
    }

    // In tổng kết
    cout << "====================================================\n";
    cout << right << setw(38) << "Tong tien hang: "
         << setw(12) << hd.tongTienHang  << " VND\n";
    cout << right << setw(38) << "Thue VAT (10%): "
         << setw(12) << hd.thueVAT       << " VND\n";
    cout << right << setw(38) << "Tong thanh toan: "
         << setw(12) << hd.tongThanhToan << " VND\n";
    cout << right << setw(38) << "Tien khach tra: "
         << setw(12) << hd.tienKhachTra  << " VND\n";
    cout << right << setw(38) << "Tien tra lai: "
         << setw(12) << hd.tienTraLai    << " VND\n";
    cout << "====================================================\n";
}
