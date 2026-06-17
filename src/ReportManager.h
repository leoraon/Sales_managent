#pragma once
#include "SaleManager.h"
#include "ProductManager.h"
#include <iomanip>

class ReportManager {
public:
    // Bao cao doanh thu theo thang/nam (hoi nguoi dung ben trong ham)
    void reportRevenue(const SaleManager& sm);

    // Top 10 san pham ban chay nhat (tu cai dat Bubble Sort, khong dung STL)
    void getTop10BestSellers(const SaleManager& sm, const ProductManager& pm);
};