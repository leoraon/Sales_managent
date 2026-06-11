#pragma once
#include "SaleManager.h"
#include "ProductManager.h"
class ReportManager {
public:  
    void reportRevenueByDate(const std::string& thoiGianLap , const SaleManager& sm);
    void getTop10BestSellers(const SaleManager& sm, const ProductManager& pm);
};