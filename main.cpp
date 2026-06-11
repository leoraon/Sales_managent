#include "ProductManager.h"
#include <iostream>

using namespace std;

int main() {
    ProductManager pm;

    cout << "--- BAT DAU TEST HES THONG ---\n\n";

    // 1. Tạo sẵn dữ liệu giả
    Product sp1 = {"SP01", "Nuoc mam Nam Ngu", "Chai", 45000};
    Product sp2 = {"SP02", "Gao ST25", "Kg", 35000};
    Product sp3 = {"SP03", "Mi Hao Hao", "Goi", 4000};

    // 2. Test hàm Thêm (addProduct)
    // Lưu ý: Do ta thêm vào ĐẦU danh sách, 
    // kết quả in ra sẽ theo thứ tự ngược lại: SP03 -> SP02 -> SP01
    pm.addProduct(sp1);
    pm.addProduct(sp2);
    pm.addProduct(sp3);

    // 3. Test hàm Hiển thị (displayAll)
    pm.displayAll();

    return 0;
}