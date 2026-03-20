#include "InventorySystem.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

InventorySystem::InventorySystem(double threshold) : reorderThreshold(threshold) {}

void InventorySystem::addProduct(std::shared_ptr<Product> product, int initialQuantity) {
    std::string barcode = product->getBarcode();
    stock[barcode] = product;
    stockQuantity[barcode] = initialQuantity;

    std::cout << "Система учета: добавлен товар \"" << product->getName()
        << "\" в количестве " << initialQuantity << " шт." << std::endl;
}

void InventorySystem::updateStock(const std::string& barcode, int quantityDelta) {
    auto it = stockQuantity.find(barcode);
    if (it != stockQuantity.end()) {
        it->second += quantityDelta;
        std::cout << "Система учета: остаток товара " << stock[barcode]->getName()
            << " изменен на " << quantityDelta
            << ". Текущий остаток: " << it->second << std::endl;

        // Проверка необходимости заказа
        if (it->second < reorderThreshold) {
            createReorderRequest(barcode);
        }
    }
    else {
        std::cout << "Товар со штрих-кодом " << barcode << " не найден в системе учета" << std::endl;
    }
}

void InventorySystem::checkExpiryDates() {
    std::cout << "\n=== ПРОВЕРКА СРОКОВ ГОДНОСТИ ===" << std::endl;
    time_t currentTime = std::time(nullptr);
    bool hasExpired = false;

    for (const auto& pair : stock) {
        if (pair.second->isExpired()) {
            std::cout << "!!! ПРОСРОЧЕН товар: " << pair.second->getName()
                << " (штрих-код: " << pair.first << ")" << std::endl;
            hasExpired = true;
        }
    }

    if (!hasExpired) {
        std::cout << "Просроченных товаров нет" << std::endl;
    }
}

bool InventorySystem::createReorderRequest(const std::string& barcode) {
    auto it = stock.find(barcode);
    if (it != stock.end()) {
        std::cout << "\n=== ЗАЯВКА ПОСТАВЩИКУ ===" << std::endl;
        std::cout << "Товар: " << it->second->getName() << std::endl;
        std::cout << "Производитель: " << it->second->getManufacturer() << std::endl;
        std::cout << "Текущий остаток: " << stockQuantity[barcode] << " шт." << std::endl;
        std::cout << "Порог заказа: " << reorderThreshold << " шт." << std::endl;
        std::cout << "Рекомендуемое количество к заказу: 50 шт." << std::endl;
        return true;
    }
    return false;
}

int InventorySystem::getStockLevel(const std::string& barcode) const {
    auto it = stockQuantity.find(barcode);
    return (it != stockQuantity.end()) ? it->second : 0;
}

void InventorySystem::displayStock() const {
    std::cout << "\n=== ТЕКУЩИЕ ОСТАТКИ ТОВАРОВ ===" << std::endl;
    if (stock.empty()) {
        std::cout << "Склад пуст" << std::endl;
        return;
    }

    std::cout << std::left << std::setw(30) << "Товар"
        << std::setw(15) << "Производитель"
        << std::setw(10) << "Цена"
        << std::setw(10) << "Остаток" << std::endl;
    std::cout << std::string(65, '-') << std::endl;

    for (const auto& pair : stock) {
        std::cout << std::left << std::setw(30) << pair.second->getName()
            << std::setw(15) << pair.second->getManufacturer()
            << std::right << std::setw(8) << pair.second->getPrice() << " руб."
            << std::setw(8) << stockQuantity.at(pair.first) << " шт." << std::endl;
    }
}

void InventorySystem::displayExpiringSoon() const {
    std::cout << "\n=== ТОВАРЫ С ИСТЕКАЮЩИМ СРОКОМ ГОДНОСТИ ===" << std::endl;
    time_t currentTime = std::time(nullptr);
    time_t weekFromNow = currentTime + 7 * 24 * 60 * 60;

    for (const auto& pair : stock) {
        if (pair.second->isExpired()) {
            std::cout << "!!! ПРОСРОЧЕН: " << pair.second->getName() << std::endl;
        }
        // Здесь можно добавить проверку на скорую просрочку
    }
}