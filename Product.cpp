#include "Product.h"
#include <iomanip>

// Реализация Product
Product::Product(const std::string& barcode, const std::string& name,
    const std::string& manufacturer, double price, double weight)
    : barcode(barcode), name(name), manufacturer(manufacturer),
    price(price), weight(weight) {
    expirationDate = std::time(nullptr) + 30 * 24 * 60 * 60; // +30 дней по умолчанию
}

void Product::displayInfo() const {
    std::cout << "Товар: " << name << ", Штрих-код: " << barcode
        << ", Производитель: " << manufacturer
        << ", Цена: " << price << " руб."
        << ", Вес: " << weight << " г";
}

bool Product::isExpired() const {
    time_t currentTime = std::time(nullptr);
    return currentTime > expirationDate;
}

// Реализация RegularProduct
RegularProduct::RegularProduct(const std::string& barcode, const std::string& name,
    const std::string& manufacturer, double price,
    double weight, int quantity)
    : Product(barcode, name, manufacturer, price, weight), quantityInPackage(quantity) {}

void RegularProduct::displayInfo() const {
    Product::displayInfo();
    std::cout << ", Тип: Обычный, Количество в упаковке: " << quantityInPackage << std::endl;
}

// Реализация WeightedProduct
WeightedProduct::WeightedProduct(const std::string& barcode, const std::string& name,
    const std::string& manufacturer, double pricePerKg)
    : Product(barcode, name, manufacturer, 0, 0), pricePerKg(pricePerKg), actualWeight(0) {}

void WeightedProduct::displayInfo() const {
    std::cout << "Товар: " << name << ", Штрих-код: " << barcode
        << ", Производитель: " << manufacturer
        << ", Цена за кг: " << pricePerKg << " руб.";
    if (actualWeight > 0) {
        std::cout << ", Факт. вес: " << actualWeight << " г, Итог: "
            << calculateFinalPrice() << " руб.";
    }
    std::cout << std::endl;
}

// Реализация AgeRestrictedProduct
AgeRestrictedProduct::AgeRestrictedProduct(const std::string& barcode, const std::string& name,
    const std::string& manufacturer, double price,
    double weight, int minAge)
    : Product(barcode, name, manufacturer, price, weight), minimumAge(minAge) {}

bool AgeRestrictedProduct::verifyAge(int customerAge) const {
    return customerAge >= minimumAge;
}

void AgeRestrictedProduct::displayInfo() const {
    Product::displayInfo();
    std::cout << ", Тип: 18+, Минимальный возраст: " << minimumAge << std::endl;
}