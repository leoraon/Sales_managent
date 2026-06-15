#include <iostream>
#include <iomanip>
#include<string>
#include "CustomerManager.h"
#include "ProductManager.h"
#include "SaleManager.h"
#include "ReportManager.h"
using namespace std;

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
        cout << "Lua chon: ";
        cin >> luaChon;
        if (luaChon == 1) {
            Product sp;
            cout << "Ma SP: "; cin >> sp.maSP;
            cin.ignore();
            cout << "Ten SP: "; getline(cin, sp.tenSP);
            cout << "Don vi tinh: "; cin >> sp.donVi;
            cout << "Don gia: "; cin >> sp.donGia;
            cout << "Ti le khuyen mai: ";
            cin >> sp.tiLeKhuyenMai;
            pm.addProduct(sp);
            cout << "=> Da them san pham thanh cong!\n";
        }
        else if (luaChon==2){
            string maSP;
            cout<<"Nhap ma san pham can xoa:";
            cin >> maSP;
            if(pm.deleteProduct(maSP)){
                cout<<"Da xoa san pham "<<maSP<<"thanh cong!\n";
            }
            else{
                cout<<"Loi:Khong tim thay san pham"<<maSP<<"!\n";
            }
        }
        else if (luaChon==3){
            string maSP;
            cout<<"Nhap ma san pham can tim: ";
            cin>>maSP;
            pm.searchProduct(maSP);
        }
        else if(luaChon==4){
            string maSP;
            cout<<"Nhap ma san pham can cap nhat: ";cin>>maSP;
            Product newData;
            newData.maSP=maSP;
            cout << "Ten SP moi: "; getline(cin, newData.tenSP);
            cout << "Don vi moi: "; cin >> newData.donVi;
            cout << "Don gia moi: "; cin >> newData.donGia;
            cout << "Ti le khuyen mai moi: "; cin >> newData.tiLeKhuyenMai;
            if (pm.updateProduct(maSP, newData))
                cout << "=> Cap nhat thanh cong!\n";
            else
                cout << "=> Loi: Khong tim thay san pham!\n";
        }
        else if (luaChon==5){
            pm.displayAll();
        }
        else if (luaChon!=0){
             cout << "=> Lua chon khong hop le!\n";
        }
    } while (luaChon != 0);
}
void menuKhachHang(CustomerManager& cm) {
    int luaChon;
    do {
        cout << "\n--- QUAN LY KHACH HANG ---\n";
        cout << "1. Them khach hang moi\n";
        cout << "2. Xoa khach hang\n";
        cout << "3. Tim kiem khach hang\n";
        cout << "4. Cap nhat khach hang\n";
        cout << "5. Hien thi tat ca khach hang\n";
        cout << "0. Quay lai menu chinh\n";
        cout << "Lua chon: ";
        cin >> luaChon;
        if (luaChon == 1) {
            Customer kh;
            cout << "Ma KH: "; cin >> kh.maKH;
            cin.ignore();
            cout << "Ten KH: "; getline(cin, kh.tenKH);
            cout << "So dien thoai: "; cin >> kh.SDT;
            kh.diemTichLuy = 0; // Khách hàng mới bắt đầu với 0 điểm
            cm.addCustomer(kh);
            cout << "=> Da them khach hang thanh cong!\n";
        }
        else if (luaChon == 2) {
            string maKH;
            cout << "Nhap ma KH can xoa: "; cin >> maKH;
            if (cm.deleteCustomer(maKH))
                cout << "=> Da xoa khach hang " << maKH << "!\n";
            else
                cout << "=> Loi: Khong tim thay khach hang!\n";
        }
        else if (luaChon == 3) {
            string maKH;
            cout << "Nhap ma KH can tim: "; cin >> maKH;
            cm.searchCustomer(maKH);
        }
        else if (luaChon == 4) {
            string maKH;
            cout << "Nhap ma KH can cap nhat: "; cin >> maKH;
            Customer newData;
            newData.maKH = maKH;
            cin.ignore();
            cout << "Ten KH moi: "; getline(cin, newData.tenKH);
            cout << "SDT moi: "; cin >> newData.SDT;
            cout << "Diem tich luy moi: "; cin >> newData.diemTichLuy;
            if (cm.updateCustomer(maKH, newData))
                cout << "=> Cap nhat thanh cong!\n";
            else
                cout << "=> Loi: Khong tim thay khach hang!\n";
        }
        else if (luaChon == 5) {
            cm.displayAll();
        }
        else if (luaChon != 0) {
            cout << "=> Lua chon khong hop le!\n";
        }
    } while (luaChon != 0);
}

void menuBanHang(SaleManager& sm, CustomerManager& cm, const ProductManager& pm) {
    int luaChon;
    do {
        cout << "\n--- QUAN LY BAN HANG & HOA DON ---\n";
        cout << "  1. Tao hoa don moi\n";
        cout << "  2. Xem chi tiet mot hoa don\n";
        cout << "  3. Xem danh sach tat ca hoa don\n";
        cout << "  0. Quay lai menu chinh\n";
        cout << "Lua chon: ";
        cin >> luaChon;
        if      (luaChon == 1) { sm.createInvoice(cm, pm); }
        else if (luaChon == 2) {
            string maHD;
            cout << "Nhap ma hoa don: "; cin >> maHD;
            sm.displayInvoice(maHD);
        }
        else if (luaChon == 3) { sm.displayInvoice(); }
        else if (luaChon != 0) { cout << "=> Lua chon khong hop le!\n"; }
    } while (luaChon != 0);
}

// : Bao cao & Thong ke ──
void menuBaoCao(ReportManager& rm, const SaleManager& sm, const ProductManager& pm) {
    int luaChon;
    do {
        cout << "\n--- BAO CAO & THONG KE ---\n";
        cout << "  1. Doanh thu theo thang\n";
        cout << "  2. Top 10 san pham ban chay nhat\n";
        cout << "  0. Quay lai menu chinh\n";
        cout << "Lua chon: ";
        cin >> luaChon;
        if      (luaChon == 1) { rm.reportRevenue(sm); }
        else if (luaChon == 2) { rm.getTop10BestSellers(sm, pm); }
        else if (luaChon != 0) { cout << "=> Lua chon khong hop le!\n"; }
    } while (luaChon != 0);
}

int main (){
    ProductManager pm;
    CustomerManager cm;
    SaleManager sm;
    ReportManager rm;
    // đọc dữ liệu từ file khi khởi động
    pm.loadFromFile("sp.txt");
    cm.loadFromFile("kh.txt");
    sm.loadFromFile("hoadon.txt", "chitiet.txt");
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
        cout << "Lua chon cua ban: ";
        cin >> luaChon;

        switch (luaChon) {
            case 1: menuSanPham(pm);          break;
            case 2: menuKhachHang(cm);        break;
            case 3: menuBanHang(sm,cm,pm);    break;
            case 4: menuBaoCao(rm,sm,pm);     break;
            case 0: cout << "\nDang luu du lieu...\n"; break;
            default: cout << "=> Lua chon khong hop le! Vui long thu lai.\n";
        }
    } while (luaChon != 0);
    // ── Lưu dữ liệu vào file trước khi thoát ──
    pm.saveToFile("sanpham.txt");
    cm.saveToFile("khachhang.txt");
    sm.saveToFile("hoadon.txt", "chitiet.txt");
    cout << "=> Da luu xong. Tam biet!\n";
    return 0;
}