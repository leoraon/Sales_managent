#include <iostream>
#include <iomanip>
#include <string>
#include <windows.h>
#include "CustomerManager.h"
#include "ProductManager.h"
#include "SaleManager.h"
#include "ReportManager.h"
#include <io.h>      
#include <fcntl.h>   
using namespace std;

// ──  xử lý nhập chữ/ký tự ──
int nhapSoNguyen(const string& thongBao) {
    int ket;
    while (true) {
        cout << thongBao;
        if (cin >> ket) break;          // Nhập đúng số → thoát
        cin.clear();                    // Xóa cờ lỗi
        cin.ignore(1000, '\n');         // Xóa rác trong bộ đệm
        cout << "=> Chi duoc nhap so! Vui long thu lai.\n";
    }
    return ket;
}

// ── Hàm xóa sản phẩm (dùng chung nhiều nơi) ──
void xoaSanPham(ProductManager& pm) {
    string maSP;
    cout << "Nhap ma SP can xoa: "; cin >> maSP;
    if (pm.deleteProduct(maSP))
        cout << "=> Da xoa san pham " << maSP << " thanh cong!\n";
    else
        cout << "=> Loi: Khong tim thay san pham " << maSP << "!\n";
}

// ── Hàm cập nhật sản phẩm (dùng chung nhiều nơi) ──
void capNhatSanPham(ProductManager& pm) {
    string maSP;
    const Product* cu = nullptr;

    // Bước 1: Nhập mã SP, lặp lại nếu sai
    do {
        cout << "Nhap ma SP can cap nhat: "; cin >> maSP;
        cu = pm.getProduct(maSP);
        if (cu == nullptr)
            cout << "=> Khong tim thay SP \"" << maSP << "\". Nhap lai!\n";
    } while (cu == nullptr);

    // Bước 2: Hiện thông tin hiện tại
    cout << "\n--- THONG TIN HIEN TAI ---\n";
    cout << "Ten SP : " << cu->tenSP  << "\n";
    cout << "Don vi : " << cu->donVi  << "\n";
    cout << "Don gia: " << cu->donGia << "\n";
    cout << "(Nhan Enter de giu nguyen, nhap moi de thay doi)\n\n";

    // Bước 3: Nhập thông tin mới - Enter để giữ nguyên
    Product newData;
    newData.maSP = maSP;
    string input;
    cin.ignore();

    cout << "Ten SP moi [" << cu->tenSP << "]: ";
    getline(cin, input);
    newData.tenSP = input.empty() ? cu->tenSP : input;

    cout << "Don vi moi [" << cu->donVi << "]: ";
    getline(cin, input);
    newData.donVi = input.empty() ? cu->donVi : input;

    cout << "Don gia moi [" << cu->donGia << "]: ";
    getline(cin, input);
    newData.donGia = input.empty() ? cu->donGia : stod(input);

    // Bước 4: Cập nhật
    pm.updateProduct(maSP, newData);
    cout << "=> Cap nhat thanh cong!\n";
}

// SUB-MENU: QUẢN LÝ SẢN PHẨM
void menuSanPham(ProductManager& pm) {
    int luaChon;
    do {
        cout << "\n--- QUAN LY SAN PHAM ---\n";
        cout << "1. Them san pham moi\n";
        cout << "2. Xoa san pham\n";
        cout << "3. Tim kiem san pham\n";
        cout << "4. Cap nhat san pham\n";
        cout << "5. Hien thi tat ca san pham\n";
        cout << "0. Quay lai menu chinh\n";
        luaChon = nhapSoNguyen("Lua chon: ");

        if (luaChon == 1) {
            Product sp;
            sp.maSP = Product::sinhMaSP();
            cout << "Ma SP tuong ung: " << sp.maSP << "\n";
            cout << "Ten SP: ";
            cin.ignore();
            getline(cin, sp.tenSP);
            cout << "Don vi tinh: "; getline(cin, sp.donVi);
            cout << "Don gia: "; cin >> sp.donGia;
            pm.addProduct(sp);
            cout << "=> Da them san pham thanh cong!\n";
        }
        else if (luaChon == 2) {
            xoaSanPham(pm);
        }
        else if (luaChon == 3) {
            string tuKhoa;
            cout << "Nhap tu khoa cho san pham can tim: ";
            cin.ignore();
            getline(cin, tuKhoa);
            pm.searchProduct(tuKhoa);

            // Hành động sau tìm kiếm
            int luaChonSau;
            do {
                cout << "\nBan muon lam gi tiep theo?\n";
                cout << "  1. Xoa san pham vua tim\n";
                cout << "  2. Cap nhat san pham vua tim\n";
                cout << "  0. Quay lai\n";
                luaChonSau = nhapSoNguyen("Lua chon: ");

                if      (luaChonSau == 1) xoaSanPham(pm);
                else if (luaChonSau == 2) capNhatSanPham(pm);
                else if (luaChonSau != 0)
                    cout << "=> Lua chon khong hop le! Vui long thu lai.\n";
            } while (luaChonSau != 0 && luaChonSau != 1 && luaChonSau != 2);

        }
        else if (luaChon == 4) {
            capNhatSanPham(pm);
        }
        else if (luaChon == 5) {
            pm.displayAll();
        }
        else if (luaChon != 0) {
            cout << "=> Lua chon khong hop le!\n";
        }
    } while (luaChon != 0);
}

// ── Hàm xóa khách hàng (dùng chung nhiều nơi) ──
void xoaKhachHang(CustomerManager& cm) {
    string maKH;
    cout << "Nhap ma KH can xoa: "; cin >> maKH;
    if (cm.deleteCustomer(maKH))
        cout << "=> Da xoa khach hang " << maKH << " thanh cong!\n";
    else
        cout << "=> Loi: Khong tim thay khach hang " << maKH << "!\n";
}

// ── Hàm cập nhật khách hàng (dùng chung nhiều nơi) ──
void capNhatKhachHang(CustomerManager& cm) {
    string maKH;
    Customer* cu = nullptr;

    // Bước 1: Nhập mã KH, lặp lại nếu sai
    do {
        cout << "Nhap ma KH can cap nhat: "; cin >> maKH;
        cu = cm.getCustomer(maKH);
        if (cu == nullptr)
            cout << "=> Khong tim thay KH \"" << maKH << "\". Nhap lai!\n";
    } while (cu == nullptr);

    // Bước 2: Hiện thông tin hiện tại
    cout << "\n--- THONG TIN HIEN TAI ---\n";
    cout << "Ten KH: " << cu->tenKH << "\n";
    cout << "SDT   : " << cu->SDT   << "\n";
    cout << "(Nhan Enter de giu nguyen, nhap moi de thay doi)\n\n";

    // Bước 3: Nhập thông tin mới - Enter để giữ nguyên
    Customer newData;
    newData.maKH = maKH;
    string input;
    cin.ignore();

    cout << "Ten KH moi [" << cu->tenKH << "]: ";
    getline(cin, input);
    newData.tenKH = input.empty() ? cu->tenKH : input;

    cout << "SDT moi [" << cu->SDT << "]: ";
    getline(cin, input);
    newData.SDT = input.empty() ? cu->SDT : input;

    // Bước 4: Cập nhật
    cm.updateCustomer(maKH, newData);
    cout << "=> Cap nhat thanh cong!\n";
}

// SUB-MENU: QUẢN LÝ KHÁCH HÀNG
void menuKhachHang(CustomerManager& cm, const SaleManager& sm) {
    int luaChon;
    do {
        cout << "\n--- QUAN LY KHACH HANG ---\n";
        cout << "1. Them khach hang moi\n";
        cout << "2. Xoa khach hang\n";
        cout << "3. Tim kiem khach hang\n";
        cout << "4. Cap nhat khach hang\n";
        cout << "5. Hien thi tat ca khach hang\n";
        cout << "0. Quay lai menu chinh\n";
        luaChon = nhapSoNguyen("Lua chon: ");

        if (luaChon == 1) {
            Customer kh;
            kh.maKH = Customer::sinhMaKH();
            cout << "Ma KH tuong ung: " << kh.maKH << "\n";
            cin.ignore();
            cout << "Ten KH: "; getline(cin, kh.tenKH);
            cout << "So dien thoai: "; cin >> kh.SDT;
            cm.addCustomer(kh);
            cout << "=> Da them khach hang thanh cong!\n";
        }
        else if (luaChon == 2) {
            xoaKhachHang(cm);
        }
        else if (luaChon == 3) {
            string tuKhoa;
            cout << "Nhap tu khoa KH can tim: ";
            cin.ignore();
            getline(cin, tuKhoa);
            cm.searchCustomer(tuKhoa);

            // Hành động sau tìm kiếm
            int luaChonSau;
            do {
                cout << "\nBan muon lam gi tiep theo?\n";
                cout << "  1. Xoa khach hang vua tim\n";
                cout << "  2. Cap nhat khach hang vua tim\n";
                cout << "  3. Xem lich su giao dich\n";
                cout << "  0. Quay lai\n";
                luaChonSau = nhapSoNguyen("Lua chon: ");

                if      (luaChonSau == 1) xoaKhachHang(cm);
                else if (luaChonSau == 2) capNhatKhachHang(cm);
                else if (luaChonSau == 3) {
                    string maKH;
                    cout << "Nhap ma KH can xem lich su: "; cin >> maKH;
                    sm.hienThiLichSuKH(maKH);
                }
                else if (luaChonSau != 0)
                    cout << "=> Lua chon khong hop le! Vui long thu lai.\n";
            } while (luaChonSau != 0 && luaChonSau != 1 && luaChonSau != 2 && luaChonSau != 3);
        }
        else if (luaChon == 4) {
            capNhatKhachHang(cm);
        }
        else if (luaChon == 5) {
            cm.displayAll();
        }
        else if (luaChon != 0) {
            cout << "=> Lua chon khong hop le!\n";
        }
    } while (luaChon != 0);
}

// SUB-MENU: QUẢN LÝ BÁN HÀNG & HÓA ĐƠN
void menuBanHang(SaleManager& sm, CustomerManager& cm, const ProductManager& pm) {
    int luaChon;
    do {
        cout << "\n--- QUAN LY BAN HANG & HOA DON ---\n";
        cout << "  1. Tao hoa don moi\n";
        cout << "  2. Tim kiem hoa don theo ngay\n";
        cout << "  3. Xem danh sach tat ca hoa don\n";
        cout << "  0. Quay lai menu chinh\n";
        luaChon = nhapSoNguyen("Lua chon: ");
        if      (luaChon == 1) { sm.createInvoice(cm, pm); }
        else if (luaChon == 2) {
            sm.searchInvoice();
            char inHD;
            cout << "Ban co muon in hoa don khong? (y/n): ";
            cin >> inHD;
            if (inHD == 'y' || inHD == 'Y') {
                cin.ignore();
                cout << "Nhap ma HD muon in: ";
                string maHDIn;
                getline(cin, maHDIn);
                sm.printInvoice(maHDIn, cm, pm);
            } 
        }
        else if (luaChon == 3) { sm.displayAllInvoices(); }
        else if (luaChon != 0) { cout << "=> Lua chon khong hop le!\n"; }
    } while (luaChon != 0);
}

// SUB-MENU: BÁO CÁO & THỐNG KÊ
void menuBaoCao(ReportManager& rm, const SaleManager& sm, const ProductManager& pm) {
    int luaChon;
    do {
        cout << "\n--- BAO CAO & THONG KE ---\n";
        cout << "  1. Doanh thu theo thang\n";
        cout << "  2. Top 10 san pham ban chay nhat\n";
        cout << "  0. Quay lai menu chinh\n";
        luaChon = nhapSoNguyen("Lua chon: ");
        if      (luaChon == 1) { rm.reportRevenue(sm); }
        else if (luaChon == 2) { rm.getTop10BestSellers(sm, pm); }
        else if (luaChon != 0) { cout << "=> Lua chon khong hop le!\n"; }
    } while (luaChon != 0);
}

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    ProductManager pm;
    CustomerManager cm;
    SaleManager sm;
    ReportManager rm;

    // Đọc dữ liệu từ file khi khởi động
    pm.loadFromFile("../data/sanpham.txt");
    cm.loadFromFile("../data/khachhang.txt");
    sm.loadFromFile("../data/hoadon.txt", "../data/chitiet.txt");

    int luaChon;
    do {
        cout << "\n========================================\n";
        cout << "        CHUONG TRINH QUAN LY BAN HANG  \n";
        cout << "========================================\n";
        cout << "  1. Quan ly San pham\n";
        cout << "  2. Quan ly Khach hang\n";
        cout << "  3. Quan ly ban hang va hoa don\n";
        cout << "  4. Bao cao va thong ke\n";
        cout << "  0. Luu va Thoat\n";
        cout << "========================================\n";
        luaChon = nhapSoNguyen("Lua chon cua ban: ");

        switch (luaChon) {
            case 1: menuSanPham(pm);        break;
            case 2: menuKhachHang(cm, sm);      break;
            case 3: menuBanHang(sm,cm,pm);  break;
            case 4: menuBaoCao(rm,sm,pm);   break;
            case 0: cout << "\nDang luu du lieu...\n"; break;
            default: cout << "=> Lua chon khong hop le! Vui long thu lai.\n";
        }
    } while (luaChon != 0);

    // Lưu dữ liệu vào file trước khi thoát
    pm.saveToFile("../data/sanpham.txt");
    cm.saveToFile("../data/khachhang.txt");
    sm.saveToFile("../data/hoadon.txt", "../data/chitiet.txt");
    cout << "=> Da luu xong. Tam biet!\n";
    return 0;
}