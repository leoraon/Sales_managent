#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>   // rand(), srand()
#include <ctime>     // time()
#include <cmath>     // ceil()
#include <iomanip>   // setw(), setfill()
#include <map>      // ← thiếu, dùng cho map<string, vector<string>>
#include <sstream>  // ← thiếu, dùng cho ostringstream
using namespace std;

// Hàm tiện ích: số ngẫu nhiên trong [min, max]
int randInt(int min, int max) {
    return min + rand() % (max - min + 1);
}

struct GenSP {
    string maSP;
    string tenSP;
    string donVi;
    double donGia;
};
struct MauSP {
    string tenGoc;
    string donVi;
    int giaMin; // nghìn đồng / đơn vị nhỏ nhất
    int giaMax;
};
MauSP khoMau[] = {

// ═══════════════════════════════════════════════
// NHÓM 1: ĐỒ UỐNG VÀ NƯỚC GIẢI KHÁT
// ═══════════════════════════════════════════════

// -- Bia lon --
{"Bia Saigon Special",   "Lon",  10, 16},
{"Bia Saigon Export",    "Lon",   9, 14},
{"Bia Tiger",            "Lon",  12, 18},
{"Bia Heineken",         "Lon",  14, 22},
{"Bia 333",              "Lon",   9, 14},
{"Bia Ha Noi",           "Lon",   8, 13},
{"Bia Budweiser",        "Lon",  15, 24},
{"Bia Carlsberg",        "Lon",  13, 20},
{"Bia Sapporo",          "Lon",  14, 22},
{"Bia Corona",           "Lon",  22, 35},

// -- Bia thùng --
{"Bia Saigon Thung",     "Thung",240,320},
{"Bia Tiger Thung",      "Thung",280,380},
{"Bia Heineken Thung",   "Thung",320,440},
{"Bia 333 Thung",        "Thung",220,300},
{"Bia Ha Noi Thung",     "Thung",200,280},

// -- Rượu --
{"Ruou Vodka Hanoi",     "Chai",  55, 90},
{"Ruou Vodka Nep Moi",   "Chai",  45, 75},
{"Ruou Vang Do Dalat",   "Chai",  80,140},
{"Ruou Vang Trang Dalat","Chai",  80,140},
{"Ruou Whisky JW Red",   "Chai", 400,600},
{"Ruou Nep Bau Da",      "Chai",  30, 60},
{"Ruou Can Tay Nguyen",  "Chai",  25, 50},

// -- Nước ngọt có ga --
{"Nuoc ngot Pepsi",      "Lon",    8, 14},
{"Nuoc ngot Coca Cola",  "Lon",    8, 14},
{"Nuoc ngot 7UP",        "Lon",    8, 14},
{"Nuoc ngot Sprite",     "Lon",    8, 14},
{"Nuoc ngot Fanta Cam",  "Lon",    8, 14},
{"Nuoc ngot Fanta Dau",  "Lon",    8, 14},
{"Nuoc ngot Mirinda",    "Lon",    7, 13},
{"Nuoc ngot Pepsi",      "Chai",   9, 18},
{"Nuoc ngot Coca Cola",  "Chai",   9, 18},
{"Nuoc ngot 7UP",        "Chai",   9, 18},

// -- Nước tăng lực --
{"Nuoc tang luc Redbull","Lon",   10, 18},
{"Nuoc tang luc Sting",  "Lon",    8, 14},
{"Nuoc tang luc Number1","Lon",    7, 13},
{"Nuoc tang luc Warrior","Lon",    8, 14},
{"Nuoc tang luc Wake-up","Lon",    8, 14},

// -- Nước ép trái cây --
{"Nuoc ep Tropicana Cam","Hop",   12, 22},
{"Nuoc ep Tropicana Tao","Hop",   12, 22},
{"Nuoc ep Twister Cam",  "Chai",  10, 18},
{"Nuoc ep Minute Maid",  "Hop",   11, 20},
{"Nuoc ep Co Gai Ha Lan","Hop",   10, 18},
{"Nuoc ep Chuoi Vinamilk","Hop",  10, 16},

// -- Sữa tươi --
{"Sua tuoi Vinamilk ItDuong","Hop",25, 38},
{"Sua tuoi Vinamilk CoThem", "Hop",26, 40},
{"Sua tuoi TH True Milk",    "Hop",28, 42},
{"Sua tuoi Moc Chau",        "Hop",24, 36},
{"Sua tuoi Dalat Milk",      "Hop",26, 40},
{"Sua tuoi Co Gai Ha Lan",   "Hop",27, 41},

// -- Sữa trái cây --
{"Sua Trai Cay Vinamilk Dau","Hop", 8, 15},
{"Sua Trai Cay Vinamilk Xoai","Hop",8, 15},
{"Sua Trai Cay TH",          "Hop",10, 18},

// -- Sữa đặc --
{"Sua dac Ong Tho",      "Hop",   18, 28},
{"Sua dac Ngoi Sao",     "Hop",   17, 26},
{"Sua dac Co Gai",       "Hop",   18, 28},

// -- Sữa bột --
{"Sua bot Dielac Alpha", "Hop",   95,180},
{"Sua bot Dielac Grow",  "Hop",  110,200},
{"Sua bot Nan Optipro",  "Hop",  120,230},
{"Sua bot Similac",      "Hop",  130,250},
{"Sua bot Friso Gold",   "Hop",  140,270},
{"Sua bot Enfamil",      "Hop",  125,240},
{"Sua bot Aptamil",      "Hop",  135,260},

// -- Trà --
{"Tra Lipton Tui Loc",   "Hop",   18, 35},
{"Tra Dilmah Tui Loc",   "Hop",   22, 42},
{"Tra Cozy Tui Loc",     "Hop",   15, 30},
{"Tra O Long Phuc Long", "Goi",   25, 50},
{"Tra Xanh Thai Nguyen", "Goi",   30, 60},
{"Tra Den Biet Thu",     "Hop",   20, 40},
{"Tra Hoa Tan Lipton IceTea","Goi",15, 28},
{"Tra Hoa Tan Nestea",   "Goi",   14, 26},

// -- Cà phê --
{"Ca phe Trung Nguyen G7",  "Goi", 25, 55},
{"Ca phe Nescafe 3in1",     "Goi", 20, 45},
{"Ca phe Vinacafe",         "Goi", 18, 40},
{"Ca phe Highlands Hoa Tan","Goi", 30, 60},
{"Ca phe Trung Nguyen Rang Xay","Goi",35,70},
{"Ca phe Giang",            "Goi", 40, 80},

// -- Nước suối --
{"Nuoc suoi Aquafina",   "Chai",   5, 10},
{"Nuoc suoi Lavie",      "Chai",   6, 11},
{"Nuoc suoi Vinh Hao",   "Chai",   5,  9},
{"Nuoc suoi Joy",        "Chai",   4,  8},
{"Nuoc suoi Dasani",     "Chai",   5, 10},
{"Binh nuoc loc 20L Aquafina","Binh",40,60},
{"Binh nuoc loc 20L Lavie",  "Binh",42,65},

// ═══════════════════════════════════════════════
// NHÓM 2: THỰC PHẨM ĂN LIỀN VÀ ĐỒ KHÔ
// ═══════════════════════════════════════════════

// -- Mì gói --
{"Mi Hao Hao Tom Chua Cay","Goi",  4,  7},
{"Mi Hao Hao Suon Heo",    "Goi",  4,  7},
{"Mi 3 Mien Bo",           "Goi",  4,  7},
{"Mi 3 Mien Ga",           "Goi",  4,  7},
{"Mi 3 Mien Hai San",      "Goi",  4,  7},
{"Mi Omachi Tom",          "Goi",  6, 10},
{"Mi Omachi Bo Sot Tieu",  "Goi",  6, 10},
{"Mi Omachi Kho Sot Tieu", "Goi",  6, 10},
{"Mi Kokomi Tom",          "Goi",  3,  6},
{"Mi Lau Thai",            "Goi",  7, 12},
{"Mi Kawa Bo Ham",         "Goi",  5,  9},
{"Mi Hao Hao Thung",       "Thung",80,130},
{"Mi Omachi Thung",        "Thung",110,180},
{"Mi 3 Mien Thung",        "Thung",75,120},

// -- Phở - Bún - Cháo ăn liền --
{"Pho bo An Lien Acecook","Goi",   6, 11},
{"Pho ga An Lien",        "Goi",   6, 11},
{"Bun Bo Hue An Lien",    "Goi",   6, 11},
{"Bun Rieu An Lien",      "Goi",   5, 10},
{"Chao Sau Rieng An Lien","Goi",   5,  9},
{"Chao Trung An Lien",    "Goi",   5,  9},
{"Mien Ga An Lien",       "Goi",   5, 10},
{"Mien Tom An Lien",      "Goi",   5, 10},

// -- Nguyên liệu khô --
{"Nam Huong Kho",         "Goi",  25, 55},
{"Nam Dong Co Kho",       "Goi",  30, 65},
{"Moc Nhi Kho",           "Goi",  20, 45},
{"Mang Kho",              "Goi",  15, 35},
{"Hanh Tim Kho",          "Kg",   30, 60},
{"Toi Kho Boc Vo",        "Goi",  20, 45},
{"Ca Kho Viet Nam",       "Goi",  35, 80},
{"Muc Kho",               "Goi",  80,180},
{"Tom Kho",               "Goi",  60,140},
{"Thit Bo Kho",           "Goi",  50,120},

// -- Các loại hạt --
{"Dau Phong Rang Muoi",   "Goi",  15, 30},
{"Dau Xanh Nguyen Hat",   "Kg",   20, 40},
{"Dau Den Nguyen Hat",    "Kg",   18, 35},
{"Dau Do Nguyen Hat",     "Kg",   22, 42},
{"Dau Nanh Nguyen Hat",   "Kg",   16, 30},
{"Hat Di",                "Goi",  40, 90},
{"Hat Mac Ca",            "Goi",  60,130},
{"Hat Bie",               "Goi",  30, 70},

// ═══════════════════════════════════════════════
// NHÓM 3: GIA VỊ
// ═══════════════════════════════════════════════
{"Bot ngot Ajinomoto",    "Goi",  15, 28},
{"Bot ngot Miwon",        "Goi",  13, 24},
{"Bot ngot Vedan",        "Goi",  12, 22},
{"Muoi I-ot",             "Goi",   4, 10},
{"Muoi bien sach",        "Kg",    8, 18},
{"Duong Bien Hoa",        "Kg",   18, 26},
{"Duong Quang Ngai",      "Kg",   17, 25},
{"Duong nau",             "Kg",   20, 30},
{"Tieu den xay",          "Goi",  20, 45},
{"Tieu trang xay",        "Goi",  22, 48},
{"Bot nghe",              "Goi",  15, 35},
{"Ot bot",                "Goi",  15, 35},
{"Bot cari",              "Goi",  12, 28},
{"Bot toi",               "Goi",  10, 22},
{"Dau an Simply",         "Lit",  38, 55},
{"Dau an Neptune",        "Lit",  35, 52},
{"Dau an Tuong An",       "Lit",  32, 48},
{"Dau an Meizan",         "Lit",  30, 46},
{"Dau an Cai Lan",        "Lit",  33, 50},
{"Nuoc mam Chin Su",      "Chai", 22, 38},
{"Nuoc mam Phu Quoc",     "Chai", 28, 50},
{"Nuoc mam Nam Ngu",      "Chai", 18, 32},
{"Nuoc mam Ca Com",       "Chai", 30, 55},
{"Nuoc tuong Maggi",      "Chai", 18, 32},
{"Nuoc tuong Chin Su",    "Chai", 15, 28},
{"Nuoc tuong Tam Thai Tu","Chai", 14, 26},
{"Tuong ot Chin Su",      "Chai", 15, 30},
{"Tuong ot Cholimex",     "Chai", 12, 25},
{"Tuong ca Chin Su",      "Chai", 14, 28},
{"Dau hao Lee Kum Kee",   "Chai", 30, 60},
{"Hat nem Knorr",         "Goi",  18, 38},
{"Hat nem Maggi",         "Goi",  16, 32},
{"Hat nem Aji-ngon",      "Goi",  14, 28},
{"Giam gao",              "Chai", 10, 22},
{"Mu tat Yellow",         "Tuyp", 15, 30},
{"Sot mayonnaise Hellmann","Chai",25, 50},

// ═══════════════════════════════════════════════
// NHÓM 4: ĐỒ DÙNG SINH HOẠT THIẾT YẾU
// ═══════════════════════════════════════════════

// -- Chăm sóc tóc --
{"Dau goi Sunsilk",       "Chai", 28, 55},
{"Dau goi Pantene",       "Chai", 32, 65},
{"Dau goi Clear",         "Chai", 30, 62},
{"Dau goi Dove",          "Chai", 35, 70},
{"Dau goi Head Shoulders","Chai", 33, 68},
{"Dau goi Rejoice",       "Chai", 25, 50},
{"Dau xa Pantene",        "Chai", 30, 60},
{"Dau xa Dove",           "Chai", 32, 65},
{"Dau xa Sunsilk",        "Chai", 28, 55},

// -- Sữa tắm - rửa tay - mặt --
{"Sua tam Dove",          "Chai", 30, 60},
{"Sua tam Lifebuoy",      "Chai", 25, 50},
{"Sua tam Enchanteur",    "Chai", 28, 55},
{"Sua tam Palmolive",     "Chai", 26, 52},
{"Sua rua mat Ponds",     "Tuyp", 30, 65},
{"Sua rua mat Garnier",   "Tuyp", 35, 75},
{"Sua rua mat Cetaphil",  "Tuyp", 55,120},
{"Nuoc rua tay Lifebuoy","Chai",  20, 45},
{"Nuoc rua tay Dettol",   "Chai", 22, 48},
{"Xa phong Lifebuoy",     "Banh",  8, 18},
{"Xa phong Dove",         "Banh", 12, 22},
{"Xa phong Lux",          "Banh", 10, 20},

// -- Giặt tẩy --
{"Bot giat Omo",          "Kg",   25, 75},
{"Bot giat Tide",         "Kg",   22, 70},
{"Bot giat Ariel",        "Kg",   28, 80},
{"Bot giat Surf",         "Kg",   20, 65},
{"Nuoc giat Omo Matic",   "Chai", 35, 85},
{"Nuoc giat Ariel Matic", "Chai", 38, 90},
{"Nuoc xa vai Comfort",   "Chai", 28, 60},
{"Nuoc xa vai Downy",     "Chai", 30, 65},
{"Nuoc xa vai Lenor",     "Chai", 32, 68},
{"Nuoc tay Javen Vim",    "Chai", 15, 35},

// -- Vệ sinh nhà cửa --
{"Nuoc rua chen Sunlight","Chai", 20, 45},
{"Nuoc rua chen Vim",     "Chai", 18, 40},
{"Nuoc rua chen My Hao",  "Chai", 15, 35},
{"Nuoc rua chen Fairy",   "Chai", 25, 52},
{"Nuoc lau nha Flash",    "Chai", 20, 45},
{"Nuoc lau nha Vim",      "Chai", 18, 40},
{"Nuoc lau kinh Windex",  "Chai", 22, 48},
{"Nuoc lau bep Mr Muscle","Chai", 25, 52},

// -- Giấy - khăn --
{"Giay ve sinh Pulppy",   "Goi",  18, 40},
{"Giay ve sinh Bless You","Goi",  15, 35},
{"Giay ve sinh Tisue",    "Goi",  12, 28},
{"Khan giay Kleenex",     "Hop",  18, 35},
{"Khan giay Tempo",       "Hop",  20, 38},
{"Khan uot Bobby",        "Goi",  12, 25},
{"Khan uot Huggies",      "Goi",  15, 30},
{"Khan uot Diana",        "Goi",  13, 28},

// -- Trẻ em --
{"Ta Huggies Newborn",    "Goi",  80,160},
{"Ta Huggies Size M",     "Goi",  90,180},
{"Ta Huggies Size L",     "Goi",  95,190},
{"Ta Pampers Size M",     "Goi",  88,175},
{"Ta Pampers Size L",     "Goi",  92,185},
{"Ta Bobby Size M",       "Goi",  70,145},
{"Phan rom Johnson Baby", "Goi",  20, 45},
{"Khan uot tre em Bobby", "Goi",  18, 38},

// -- Diệt côn trùng --
{"Thuoc xin Raid",        "Chai", 35, 70},
{"Thuoc xin Baygon",      "Chai", 32, 65},
{"Nhang muoi Vape",       "Goi",  15, 30},
{"Nhang muoi Raid",       "Goi",  18, 35},
{"Keo dinh chuot",        "Goi",  10, 22},

// -- Vệ sinh cá nhân --
{"Kem danh rang Colgate", "Tuyp", 18, 42},
{"Kem danh rang P/S",     "Tuyp", 15, 35},
{"Kem danh rang Close-Up","Tuyp", 16, 38},
{"Kem danh rang Sensodyne","Tuyp",35, 75},
{"Ban chai danh rang Oral-B","Cai",18, 38},
{"Ban chai danh rang Colgate","Cai",15,32},
{"Dao cao rau Gillette",  "Cai",  25, 55},
{"Dao cao rau Schick",    "Cai",  22, 48},
{"Bang ve sinh Diana",    "Goi",  18, 38},
{"Bang ve sinh Kotex",    "Goi",  20, 42},
{"Khau trang 3M",         "Goi",  25, 55},
{"Khau trang y te",       "Goi",  15, 30},
{"Ao mua 1 lan",          "Cai",  15, 30},
{"Bat lua gas",           "Cai",   5, 15},
{"The cao Viettel 50k",   "The",  48, 50},
{"The cao Mobi 50k",      "The",  48, 50},
{"The cao Vina 50k",      "The",  48, 50},
{"The cao Viettel 100k",  "The",  98,100},
{"Thuoc la Vinataba",     "Goi",  25, 30},
{"Thuoc la Marlboro",     "Goi",  28, 35},

// ═══════════════════════════════════════════════
// NHÓM 5: ĐỒ ĂN VẶT
// ═══════════════════════════════════════════════
{"Bim bim Oishi Tom",     "Goi",   8, 15},
{"Bim bim Oishi BBQ",     "Goi",   8, 15},
{"Bim bim Poca Cheese",   "Goi",   8, 15},
{"Bim bim Poca BBQ",      "Goi",   8, 15},
{"Bim bim Swing Tom",     "Goi",   7, 14},
{"Que cay Tay Ninh",      "Goi",  10, 20},
{"Que cay sa te",         "Goi",  10, 20},
{"Banh trang nuong",      "Goi",  12, 25},
{"Chan ga cay",           "Goi",  15, 30},
{"Xuc xich cocktail",     "Goi",  20, 45},
{"Xuc xich Vissan",       "Goi",  25, 55},
{"Keo mem Alpenliebe",    "Goi",  10, 22},
{"Keo cao su Mentos",     "Goi",   8, 18},
{"Keo Kopiko ca phe",     "Goi",  12, 24},
{"Socola KitKat",         "Goi",  15, 32},
{"Socola Snickers",       "Goi",  18, 38},
{"Socola Milky",          "Goi",  10, 22},
{"Banh Oreo",             "Goi",  12, 25},
{"Banh Cosy",             "Goi",  10, 22},
{"Banh Hura Kem",         "Goi",   8, 18},
{"Banh bong lan Kinh Do", "Goi",  15, 30},
{"Banh trung thu Kinh Do","Goi",  35, 80},
{"Banh quy Marie",        "Goi",   9, 20},
{"Banh snack Oishi Prawn","Goi",   8, 16},
{"Sua chua Vinamilk",     "Hop",   6, 12},
{"Sua chua co duong TH",  "Hop",   7, 14},
{"Sua chua Yakult",       "Goi",  12, 22},

// ═══════════════════════════════════════════════
// NHÓM 6: VĂN PHÒNG PHẨM
// ═══════════════════════════════════════════════
{"Vo o ly Thien Long",    "Quyen",  5, 12},
{"Vo ke ngang",           "Quyen",  5, 12},
{"So ghi chep bi cung",   "Quyen", 20, 45},
{"So tay A5 bi cung",     "Quyen", 25, 55},
{"Giay A4 Double A",      "Ream",  55, 80},
{"Giay A4 IK Plus",       "Ream",  48, 72},
{"Giay kiem tra",         "Tap",   10, 20},
{"But bi Thien Long TL-027","Cai",  4,  8},
{"But bi Thien Long TL-036","Cai",  5,  9},
{"But bi Ben Nghe",       "Cai",    3,  7},
{"But bi Pentel",         "Cai",    6, 12},
{"But chi 2B Thien Long", "Cai",    4,  9},
{"But chi HB Staedtler",  "Cai",    6, 14},
{"Cuc tay Nataraj",       "Cai",    3,  7},
{"Cuc tay Staedtler",     "Cai",    5, 10},
{"But mau Crayola 12",    "Hop",   30, 60},
{"But mau Colokit 24",    "Hop",   40, 80},
{"But highlight Stabilo", "Cai",    8, 18},
{"But long Artline",      "Cai",   10, 22},
{"Bang keo trong 3M",     "Cuon",   8, 18},
{"Bang keo doi",          "Cuon",  10, 22},
{"Keo ho UHU",            "Tuyp",  10, 22},
{"Keo dan giay",          "Binh",   8, 18},
{"Dao roc giay",          "Cai",    8, 18},
{"Keo thu cong",          "Cai",    8, 18},
};

int soMau = sizeof(khoMau) / sizeof(khoMau[0]);
map<string, vector<string>> quyCach = {

    // ── NHÓM KHỐI LƯỢNG ────────────────────────────
    {"Kg",    {"100g","200g","250g","400g","500g",
               "750g","1Kg","2Kg","3Kg","5Kg"}},          // 10 biến thể

    {"Goi",   {"30g","50g","75g","100g","150g",
               "200g","300g","500g","750g","1Kg"}},        // 10 biến thể

    {"Banh",  {"50g","75g","90g","100g","125g",
               "150g","180g","200g"}},                     //  8 biến thể

    // ── NHÓM THỂ TÍCH ───────────────────────────────
    {"Chai",  {"100ml","150ml","200ml","250ml","330ml",
               "500ml","750ml","1L","1.5L","2L"}},         // 10 biến thể

    {"Hop",   {"100ml","150ml","180ml","200ml","250ml",
               "330ml","500ml","750ml","1L","1.5L"}},      // 10 biến thể

    {"Lon",   {"150ml","200ml","250ml","270ml",
               "330ml","500ml","750ml","1L"}},             //  8 biến thể

    {"Lit",   {"250ml","500ml","750ml","1L",
               "1.5L","2L","3L","5L"}},                    //  8 biến thể

    {"Tuyp",  {"25g","40g","50g","75g","100g",
               "150g","175g","200g","250g"}},              //  9 biến thể

    // ── NHÓM SỐ LƯỢNG ───────────────────────────────
    {"Thung", {"6 lon","12 lon","18 lon","24 lon",
               "30 goi","48 goi","60 goi"}},               //  7 biến thể

    {"Cai",   {"1 cai","2 cai","3 cai","5 cai","10 cai"}}, //  5 biến thể

    {"Quyen", {"48 trang","72 trang","96 trang",
               "120 trang","200 trang"}},                  //  5 biến thể

    {"Cuon",  {"12mm","18mm","24mm","48mm"}},              //  4 biến thể

    {"Tap",   {"20 to","50 to","100 to"}},                 //  3 biến thể

    // ── ĐƠN VỊ ĐẶC THÙ (ít biến thể) ───────────────
    {"Binh",  {"20L"}},                                    //  1
    {"Ream",  {"500 to"}},                                 //  1
    {"The",   {"1 the"}},                                  //  1
};
vector<GenSP> sinhSanPham(ofstream& f, int soLuong) {
    vector<GenSP> ds;
    int dem = 1;

    for (int i = 0; i < soMau && dem <= soLuong; i++) {
        // Lấy danh sách quy cách theo đơn vị của mẫu này
        auto it = quyCach.find(khoMau[i].donVi);
        if (it == quyCach.end()) continue; // Đơn vị chưa có → bỏ qua

        for (auto& kichThuoc : it->second) {
            if (dem > soLuong) break;

            GenSP sp;

            // Sinh mã SP: SP0001, SP0002...
            ostringstream oss;
            oss << "SP" << setw(4) << setfill('0') << dem;
            sp.maSP  = oss.str();

            // Ghép tên: "Gao ST25" + " " + "1Kg" = "Gao ST25 1Kg"
            sp.tenSP = khoMau[i].tenGoc + " " + kichThuoc;
            sp.donVi = khoMau[i].donVi;

            // Giá ngẫu nhiên trong khoảng hợp lý, làm tròn đến 1,000đ
            sp.donGia = randInt(khoMau[i].giaMin,
                                khoMau[i].giaMax) * 1000.0;

            f << sp.maSP << "|" << sp.tenSP << "|"
              << sp.donVi << "|" << sp.donGia << "|\n";

            ds.push_back(sp);
            dem++;
        }
    }

    cout << "Da sinh " << ds.size() << " san pham.\n";
    return ds;
}

struct GenKH {
    string maKH;
    string tenKH;
    string SDT;
};

// 10 × 8 × 10 = 800 tổ hợp tên — vừa đúng
string dsHo[] = {
    "Nguyen","Tran","Le","Pham","Hoang",
    "Vu","Do","Bui","Dang","Ngo"
};
string dsDem[] = {
    "Van","Thi","Duc","Minh",
    "Thanh","Quoc","Tuan","Xuan"
};
string dsTen[] = {
    "An","Binh","Cuong","Dung","Em",
    "Phuc","Hoa","Nam","Lan","Khanh"
};

// Đầu số điện thoại hợp lệ tại Việt Nam
string dauSoDT[] = {
    "090","091","093","094","096","097","098",
    "032","033","034","035","036","038","039",
    "070","076","077","078","079"
};
int soDauSo = 19;

string sinhSDT() {
    // Chọn đầu số ngẫu nhiên
    string sdt = dauSoDT[randInt(0, soDauSo - 1)];

    // Thêm 7 chữ số ngẫu nhiên phía sau
    for (int i = 0; i < 7; i++)
        sdt += to_string(randInt(0, 9));

    return sdt;
}
vector<GenKH> sinhKhachHang(ofstream& f, int soLuong) {
    // Tạo toàn bộ tổ hợp tên
    vector<string> tatCaTen;
    for (auto& ho : dsHo)
        for (auto& dem : dsDem)
            for (auto& ten : dsTen)
                tatCaTen.push_back(ho + " " + dem + " " + ten);

    // Xáo trộn
    for (int i = tatCaTen.size() - 1; i > 0; i--) {
        int j = randInt(0, i);
        swap(tatCaTen[i], tatCaTen[j]);
    }

    vector<GenKH> ds;
    for (int i = 0; i < soLuong; i++) {
        GenKH kh;

        // Mã KH: KH0001, KH0002...
        ostringstream oss;
        oss << "KH" << setw(4) << setfill('0') << (i + 1);
        kh.maKH  = oss.str();
        kh.tenKH = tatCaTen[i];   // lấy từ danh sách đã xáo
        kh.SDT   = sinhSDT();

        // Ghi file đúng format loadFromFile
        f << kh.maKH << "|" << kh.tenKH << "|" << kh.SDT << "|\n";

        ds.push_back(kh);
    }

    cout << "Da sinh " << ds.size() << " khach hang.\n";
    return ds;
}

void sinhHoaDon(ofstream& fHD, ofstream& fCT,
                const vector<GenKH>& dsKH,
                const vector<GenSP>& dsSP,
                int soLuong) {

    int bangCK[] = {0, 0, 0, 5, 10}; // 60% khong CK, 20% CK 5%, 20% CK 10%

    for (int i = 1; i <= soLuong; i++) {

        // Sinh maHD: HD00001, HD00002...
        ostringstream oss;
        oss << "HD" << setw(5) << setfill('0') << i;
        string maHD = oss.str();

        string maKH = dsKH[randInt(0, dsKH.size() - 1)].maKH;
        int ngay  = randInt(1, 28);
        int thang = randInt(1, 6);   // 6 thang dau nam 2026
        int nam   = 2026;            // co dinh nam 2026

        int soSPtrongHD = randInt(1, 4);
        double tongTienHang = 0;
        vector<int> daDung; // danh sach index SP da chon trong HD nay

        for (int j = 0; j < soSPtrongHD; j++) {
            // Chon SP khong trung bang do-while
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

        if (i % 2000 == 0)
            cout << "Da sinh " << i << "/" << soLuong << " hoa don...\n";
    }

    cout << "Da sinh xong " << soLuong << " hoa don.\n";
}

int main() {
    srand(time(0));

    ofstream fKH("khachhang.txt");
    ofstream fSP("sanpham.txt");
    ofstream fHD("hoadon.txt");
    ofstream fCT("chitiet.txt");

    // Chạy theo thứ tự phụ thuộc
    vector<GenKH> dsKH = sinhKhachHang(fKH, 800);   // ← sinh trước
    vector<GenSP> dsSP = sinhSanPham(fSP, 2000);    // ← sinh trước
    sinhHoaDon(fHD, fCT, dsKH, dsSP, 10000);        // ← cần cả 2 vector trên

    fKH.close();
    fSP.close();
    fHD.close();
    fCT.close();

    cout << "Hoan tat sinh du lieu!\n";
    return 0;
}