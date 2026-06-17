#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iomanip>
#include <sstream>

using namespace std;

int randInt(int min, int max) {
    return min + rand() % (max - min + 1);
}

struct GenSP {
    string maSP;
    string tenSP;
    string donVi;
    double donGia;
};

vector<GenSP> tatCaSP;

void addSP(string ten, string donVi, int giaMinK, int giaMaxK) {
    GenSP sp;
    sp.tenSP = ten;
    sp.donVi = donVi;
    sp.donGia = randInt(giaMinK, giaMaxK) * 1000.0;
    tatCaSP.push_back(sp);
}

void genCombos(vector<string> c1, vector<string> c2, string donVi, int minK, int maxK, string prefix = "", string suffix = "") {
    for (auto x : c1) {
        for (auto y : c2) {
            string name = prefix;
            if (name != "") name += " ";
            name += x + " " + y;
            if (suffix != "") name += " " + suffix;
            addSP(name, donVi, minK, maxK);
        }
    }
}
void genCombos3(vector<string> c1, vector<string> c2, vector<string> c3, string donVi, int minK, int maxK, string prefix = "") {
    for (auto x : c1) {
        for (auto y : c2) {
            for (auto z : c3) {
                string name = prefix;
                if (name != "") name += " ";
                name += x + " " + y + " " + z;
                addSP(name, donVi, minK, maxK);
            }
        }
    }
}

void sinhKhoSanPham() {
    // 1. ĐỒ UỐNG (Mục tiêu ~30%)
    vector<string> brands_nuocsuoi = {"Aquafina", "Lavie", "Dasani", "Vĩnh Hảo", "Thạch Bích"};
    vector<string> sizes_nuocsuoi = {"Chai 350ml", "Chai 500ml", "Chai 1.5L"};
    genCombos(brands_nuocsuoi, sizes_nuocsuoi, "Chai", 5, 15, "Nước suối");

    vector<string> brands_nuocngot = {"Coca-Cola", "Pepsi", "7Up", "Sprite", "Mirinda", "Fanta"};
    vector<string> sizes_nuocngot = {"Lon 330ml", "Chai 390ml", "Chai 1.5L"};
    genCombos(brands_nuocngot, sizes_nuocngot, "Chai/Lon", 8, 22, "Nước ngọt");

    vector<string> brands_tangluc = {"Red Bull", "Sting", "Monster", "Warrior", "Wake-up 247"};
    vector<string> sizes_tangluc = {"Lon 250ml", "Chai 330ml"};
    genCombos(brands_tangluc, sizes_tangluc, "Chai/Lon", 10, 30, "Nước tăng lực");

    vector<string> brands_tra = {"C2", "Không Độ", "Trà Xanh 0 Độ", "TEA+ Plus", "TH true TEA"};
    vector<string> sizes_tra = {"Chai 330ml", "Chai 455ml"};
    genCombos(brands_tra, sizes_tra, "Chai", 8, 15, "Trà");

    vector<string> brands_cafe = {"Nescafe", "Highlands", "Birdy", "King Coffee"};
    vector<string> types_cafe = {"Lon 170ml Đen", "Lon 170ml Sữa", "Chai 330ml Đen"};
    genCombos(brands_cafe, types_cafe, "Chai/Lon", 12, 25, "Cà phê");
    
    vector<string> brands_cafegoi = {"G7", "Nescafe 3in1", "Vinacafe", "Wake-up"};
    vector<string> sizes_cafegoi = {"Hộp 15 gói", "Bịch 50 gói"};
    genCombos(brands_cafegoi, sizes_cafegoi, "Hộp/Bịch", 40, 150, "Cà phê hòa tan");

    vector<string> brands_sua = {"Vinamilk", "TH True Milk", "Mộc Châu", "Dalad Milk"};
    vector<string> types_sua = {"Có đường", "Không đường", "Hương Dâu", "Hương Socola"};
    vector<string> sizes_sua = {"Hộp 180ml", "Hộp 1L"};
    genCombos3(brands_sua, types_sua, sizes_sua, "Hộp", 8, 40, "Sữa tươi");

    vector<string> brands_bia = {"Heineken", "Tiger", "Saigon", "Hà Nội", "Sapporo", "Budweiser"};
    vector<string> types_bia = {"Lon 330ml Lẻ", "Thùng 24 Lon 330ml"};
    genCombos(brands_bia, types_bia, "Lon/Thùng", 15, 400, "Bia");

    vector<string> brands_suachua = {"Yakult", "Probi", "TH True Yogurt", "Betagen"};
    vector<string> types_suachua = {"Lốc 5 chai 65ml", "Chai 400ml", "Lốc 4 chai 130ml"};
    genCombos(brands_suachua, types_suachua, "Lốc/Chai", 20, 45, "Sữa chua uống");

    vector<string> brands_traicay = {"Tropicana", "Vfresh", "Twister", "Minute Maid"};
    vector<string> types_traicay = {"Cam", "Táo", "Nho", "Đào"};
    vector<string> sizes_traicay = {"Chai 350ml", "Hộp 1L"};
    genCombos3(brands_traicay, types_traicay, sizes_traicay, "Chai/Hộp", 10, 45, "Nước ép trái cây");

    // 2. THỰC PHẨM KHÔ & ĂN VẶT (Mục tiêu ~25%)
    vector<string> brands_mi = {"Hảo Hảo", "Omachi", "Kokomi", "3 Miền", "Cung Đình", "Indomie"};
    vector<string> flavors_mi = {"Tôm Chua Cay", "Sườn Heo", "Bò Hầm", "Lẩu Thái"};
    genCombos(brands_mi, flavors_mi, "Gói", 4, 15, "Mì");

    vector<string> brands_pho = {"Vifon", "Đệ Nhất", "Acecook"};
    vector<string> types_pho = {"Phở Bò", "Phở Gà", "Bún Bò Huế", "Hủ Tiếu Nam Vang"};
    genCombos(brands_pho, types_pho, "Gói", 7, 20);

    vector<string> brands_dohop = {"Vissan", "Seaspimex", "Hạ Long", "Đồ hộp Tulips"};
    vector<string> types_dohop = {"Cá mòi 150g", "Thịt heo xay 150g", "Pate gan 170g", "Xúc xích tiệt trùng 4 cây"};
    genCombos(brands_dohop, types_dohop, "Hộp/Gói", 20, 50);

    vector<string> brands_snack = {"Oishi", "Poca", "Lay's", "Swing", "Toonies", "Karamucho"};
    vector<string> flavors_snack = {"Vị Phô Mai", "Vị Mực Cay", "Vị BBQ", "Vị Hành Tự Nhiên"};
    vector<string> sizes_snack = {"Gói nhỏ 30g", "Gói lớn 70g"};
    genCombos3(brands_snack, flavors_snack, sizes_snack, "Gói", 6, 25, "Snack");

    vector<string> brands_hat = {"Tân Tân", "Oishi", "Tài Tài"};
    vector<string> types_hat = {"Đậu phộng cốt dừa", "Hạt điều rang muối", "Hướng dương"};
    vector<string> sizes_hat = {"Gói 50g", "Gói 150g"};
    genCombos3(brands_hat, types_hat, sizes_hat, "Gói", 10, 60);

    vector<string> brands_banh = {"Kinh Đô", "Orion", "Oreo", "ChocoPie", "Danisa"};
    vector<string> types_banh = {"Bánh quy bơ", "Bánh xốp sôcôla", "Bánh bông lan", "Bánh quế"};
    genCombos(brands_banh, types_banh, "Hộp/Gói", 15, 120);

    // 3. GIA VỊ & LƯƠNG THỰC (Mục tiêu ~20%)
    vector<string> brands_nuocmam = {"Chinsu", "Nam Ngư", "Hưng Thịnh", "Phú Quốc", "Liên Thành"};
    vector<string> sizes_nuocmam = {"Chai 500ml", "Chai 750ml", "Chai 1L"};
    genCombos(brands_nuocmam, sizes_nuocmam, "Chai", 20, 80, "Nước mắm");

    vector<string> brands_xidau = {"Chinsu", "Maggi", "Tam Thái Tử", "Knorr"};
    vector<string> sizes_xidau = {"Chai 250ml", "Chai 500ml"};
    genCombos(brands_xidau, sizes_xidau, "Chai", 15, 40, "Nước tương");

    vector<string> brands_tuongot = {"Chinsu", "Cholimex", "O'Food", "Knorr"};
    vector<string> types_tuongot = {"Tương ớt 250g", "Tương cà 250g", "Tương ớt 500g"};
    genCombos(brands_tuongot, types_tuongot, "Chai", 12, 35);

    vector<string> brands_dauan = {"Simply", "Neptune", "Meizan", "Cái Lân", "Tường An"};
    vector<string> sizes_dauan = {"Chai 1L", "Can 2L", "Can 5L"};
    genCombos(brands_dauan, sizes_dauan, "Chai/Can", 40, 250, "Dầu ăn");

    vector<string> brands_giavi = {"Ajinomoto", "Miwon", "Vedan", "Knorr", "Aji-ngon"};
    vector<string> types_giavi = {"Bột ngọt 400g", "Bột ngọt 1kg", "Hạt nêm thịt heo 400g", "Hạt nêm thịt heo 900g"};
    genCombos(brands_giavi, types_giavi, "Gói", 25, 90);

    vector<string> brands_duong = {"Biên Hòa", "TTC", "An Khê"};
    vector<string> types_duong = {"Đường tinh luyện 500g", "Đường tinh luyện 1kg", "Đường vàng 1kg"};
    genCombos(brands_duong, types_duong, "Gói", 15, 30);

    vector<string> brands_gao = {"Hạt Ngọc Trời", "Vua Gạo", "Neptune", "Gạo Quê", "Gạo Thái"};
    vector<string> types_gao = {"ST25", "Tám Thơm", "Hương Lài"};
    vector<string> sizes_gao = {"Túi 2kg", "Túi 5kg"};
    genCombos3(brands_gao, types_gao, sizes_gao, "Túi", 50, 200, "Gạo");

    // 4. HÓA MỸ PHẨM & CHĂM SÓC CÁ NHÂN (Mục tiêu ~15%)
    vector<string> brands_giat = {"Omo", "Ariel", "Surf", "Tide", "LIX"};
    vector<string> types_giat = {"Bột giặt 800g", "Bột giặt 3kg", "Nước giặt 1.2kg", "Nước giặt 3.6kg"};
    genCombos(brands_giat, types_giat, "Túi/Chai", 35, 180);

    vector<string> brands_xavai = {"Comfort", "Downy", "Hygiene"};
    vector<string> scents_xavai = {"Hương Ban Mai", "Hương Đam Mê", "Hương Hoa Hồng"};
    vector<string> sizes_xavai = {"Túi 800ml", "Can 3L"};
    genCombos3(brands_xavai, scents_xavai, sizes_xavai, "Túi/Can", 45, 200, "Nước xả vải");

    vector<string> brands_vesinh = {"Sunlight", "Vim", "Gift", "Duck"};
    vector<string> types_vesinh = {"Nước lau nhà 1L", "Nước lau nhà 3.8L", "Nước tẩy bồn cầu 900ml", "Nước rửa chén 750g", "Nước rửa chén 3.8kg"};
    genCombos(brands_vesinh, types_vesinh, "Chai/Can", 25, 120);

    vector<string> brands_daugoi = {"Sunsilk", "Clear", "Pantene", "Head & Shoulders"};
    vector<string> types_daugoi = {"Chai 170g", "Chai 650g", "Dây 10 gói nhỏ"};
    genCombos(brands_daugoi, types_daugoi, "Chai/Dây", 15, 150, "Dầu gội");

    vector<string> brands_suatam = {"Lifebuoy", "Dove", "Enchanteur"};
    vector<string> types_suatam = {"Chai 250g", "Chai 850g"};
    genCombos(brands_suatam, types_suatam, "Chai", 45, 200, "Sữa tắm");

    vector<string> brands_kemdanhrang = {"P/S", "Colgate", "Close-Up", "Sensodyne"};
    vector<string> types_kemdanhrang = {"Trà xanh 180g", "Bảo vệ nướu 180g", "Than hoạt tính 180g"};
    genCombos(brands_kemdanhrang, types_kemdanhrang, "Tuýp", 25, 80, "Kem đánh răng");

    // 5. HÀNG HÓA GIA DỤNG CƠ BẢN & KHÁC (Mục tiêu ~10%)
    vector<string> brands_giay = {"Pulppy", "Bless You", "Watersilk", "Hà Nội"};
    vector<string> types_giay = {"Giấy vệ sinh lốc 6 cuộn", "Giấy vệ sinh lốc 10 cuộn", "Khăn giấy hộp 100 tờ", "Khăn giấy ướt 80 miếng"};
    genCombos(brands_giay, types_giay, "Lốc/Hộp", 20, 80);

    vector<string> brands_pin = {"Panasonic", "Energizer", "Con Ó"};
    vector<string> types_pin = {"Pin AA Vỉ 2 viên", "Pin AAA Vỉ 2 viên"};
    genCombos(brands_pin, types_pin, "Vỉ", 10, 45);

    vector<string> list_khac = {
        "Bật lửa gas Thống Nhất", "Bật lửa BIC",
        "Áo mưa tiện lợi 1 lần", "Áo mưa dơi cánh dơi",
        "Tăm bông Jomi hộp vuông", "Tăm bông Niva hộp tròn",
        "Bao rác đen cuộn nhỏ 1kg", "Bao rác sinh học phân hủy 1kg",
        "Dao cạo râu Gillette 1 lưỡi", "Dao cạo râu Gillette 2 lưỡi",
        "Băng vệ sinh Diana Siêu mỏng", "Băng vệ sinh Kotex Hàng ngày"
    };
    for(auto x : list_khac) addSP(x, "Cái/Cuộn/Gói", 5, 45);

    vector<string> brands_the = {"Viettel", "Mobifone", "Vinaphone"};
    vector<string> values_the = {"Mệnh giá 20K", "Mệnh giá 50K", "Mệnh giá 100K", "Mệnh giá 200K", "Mệnh giá 500K"};
    genCombos(brands_the, values_the, "Thẻ", 20, 500, "Thẻ cào điện thoại");
}

vector<GenSP> sinhSanPham(ofstream& f) {
    sinhKhoSanPham(); // Tạo danh sách tatCaSP

    int dem = 1;
    for (auto& sp : tatCaSP) {
        ostringstream oss;
        oss << "SP" << setw(4) << setfill('0') << dem++;
        sp.maSP = oss.str();
        f << sp.maSP << "|" << sp.tenSP << "|" << sp.donVi << "|" << sp.donGia << "|\n";
    }

    cout << "Da sinh " << tatCaSP.size() << " san pham dac trung.\n";
    return tatCaSP;
}

struct GenKH {
    string maKH;
    string tenKH;
    string SDT;
};

string dsHo[] = {"Nguyen","Tran","Le","Pham","Hoang","Vu","Do","Bui","Dang","Ngo"};
string dsDem[] = {"Van","Thi","Duc","Minh","Thanh","Quoc","Tuan","Xuan"};
string dsTen[] = {"An","Binh","Cuong","Dung","Em","Phuc","Hoa","Nam","Lan","Khanh"};

string dauSoDT[] = {
    "090","091","093","094","096","097","098",
    "032","033","034","035","036","038","039",
    "070","076","077","078","079"
};

string sinhSDT() {
    string sdt = dauSoDT[randInt(0, 18)];
    for (int i = 0; i < 7; i++) sdt += to_string(randInt(0, 9));
    return sdt;
}

vector<GenKH> sinhKhachHang(ofstream& f, int soLuong) {
    vector<string> tatCaTen;
    for (auto& ho : dsHo)
        for (auto& dem : dsDem)
            for (auto& ten : dsTen)
                tatCaTen.push_back(ho + " " + dem + " " + ten);

    for (int i = tatCaTen.size() - 1; i > 0; i--) {
        int j = randInt(0, i);
        swap(tatCaTen[i], tatCaTen[j]);
    }

    vector<GenKH> ds;
    for (int i = 0; i < soLuong; i++) {
        GenKH kh;
        ostringstream oss;
        oss << "KH" << setw(4) << setfill('0') << (i + 1);
        kh.maKH  = oss.str();
        kh.tenKH = tatCaTen[i];
        kh.SDT   = sinhSDT();
        f << kh.maKH << "|" << kh.tenKH << "|" << kh.SDT << "|\n";
        ds.push_back(kh);
    }

    cout << "Da sinh " << ds.size() << " khach hang.\n";
    return ds;
}

void sinhHoaDon(ofstream& fHD, ofstream& fCT, const vector<GenKH>& dsKH, const vector<GenSP>& dsSP, int soLuong) {
    int bangCK[] = {0, 0, 0, 5, 10};

    for (int i = 1; i <= soLuong; i++) {
        ostringstream oss;
        oss << "HD" << setw(5) << setfill('0') << i;
        string maHD = oss.str();

        string maKH = dsKH[randInt(0, dsKH.size() - 1)].maKH;
        
        int thang = randInt(1, 6);
        int ngay;
        if (thang == 2) ngay = randInt(1, 28);
        else if (thang == 4) ngay = randInt(1, 30);
        else if (thang == 6) ngay = randInt(1, 17); // gioi han toi 17/06/2026
        else ngay = randInt(1, 31);
        int nam = 2026;

        int soSPtrongHD = randInt(1, 4);
        double tongTienHang = 0;
        vector<int> daDung;

        for (int j = 0; j < soSPtrongHD; j++) {
            int idx;
            bool trung;
            do {
                idx = randInt(0, dsSP.size() - 1);
                trung = false;
                for (int k : daDung)
                    if (k == idx) { trung = true; break; }
            } while (trung);

            daDung.push_back(idx);

            const GenSP& sp  = dsSP[idx];
            int    soLuongSP = randInt(1, 10);
            double ck        = bangCK[randInt(0, 4)];
            double chietKhau = soLuongSP * sp.donGia * ck / 100.0;
            double thanhTien = soLuongSP * sp.donGia - chietKhau;
            tongTienHang    += thanhTien;

            fCT << maHD      << "|"
                << sp.maSP   << "|"
                << soLuongSP << "|"
                << sp.donGia << "|"
                << chietKhau << "|"
                << thanhTien << "\n";
        }

        double thueVAT       = tongTienHang * 0.1;
        double tongThanhToan = tongTienHang + thueVAT;
        double tienKhachTra  = ceil(tongThanhToan / 10000.0) * 10000;
        double tienTraLai    = tienKhachTra - tongThanhToan;

        fHD << maHD          << "|"
            << maKH          << "|"
            << ngay          << "|"
            << thang         << "|"
            << nam           << "|"
            << tongTienHang  << "|"
            << thueVAT       << "|"
            << tongThanhToan << "|"
            << tienKhachTra  << "|"
            << tienTraLai    << "\n";

        if (i % 2000 == 0) cout << "Da sinh " << i << "/" << soLuong << " hoa don...\n";
    }
    cout << "Da sinh xong " << soLuong << " hoa don.\n";
}

int main() {
    srand(time(0));

    ofstream fKH("khachhang.txt");
    ofstream fSP("sanpham.txt");
    ofstream fHD("hoadon.txt");
    ofstream fCT("chitiet.txt");

    vector<GenKH> dsKH = sinhKhachHang(fKH, 800);
    vector<GenSP> dsSP = sinhSanPham(fSP); // KHONG truyen 2000 nua, lay size cua tatCaSP
    sinhHoaDon(fHD, fCT, dsKH, dsSP, 10000);

    fKH.close();
    fSP.close();
    fHD.close();
    fCT.close();

    cout << "Hoan tat sinh du lieu!\n";
    return 0;
}