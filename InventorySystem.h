#pragma once
#include <string>
#include <vector>
#include <map>
#include <memory>
#include "Product.h"

// Класс системы учета товаров
class InventorySystem {
private:
    std::map<std::string, std::shared_ptr<Product>> stock; // текущие остатки
    std::map<std::string, int> stockQuantity; // количество каждого товара
    double reorderThreshold; // порог для заказа (в %)

public:
    InventorySystem(double threshold = 20.0);

    // Основные методы
    void updateStock(const std::string& barcode, int quantityDelta);
    void checkExpiryDates();
    bool createReorderRequest(const std::string& barcode);

    // Администрирование
    void addProduct(std::shared_ptr<Product> product, int initialQuantity);
    int getStockLevel(const std::string& barcode) const;
    void displayStock() const;
    void displayExpiringSoon() const;
};