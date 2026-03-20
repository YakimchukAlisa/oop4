#pragma once
#include <string>
#include <iostream>
#include <ctime>

// Абстрактный базовый класс Product
class Product {
protected:
    std::string barcode;
    std::string name;
    std::string manufacturer;
    double price;
    double weight;  // вес в граммах
    time_t expirationDate;

public:
    Product(const std::string& barcode, const std::string& name,
        const std::string& manufacturer, double price, double weight);
    virtual ~Product() = default;

    // Геттеры
    std::string getBarcode() const { return barcode; }
    std::string getName() const { return name; }
    std::string getManufacturer() const { return manufacturer; }
    double getPrice() const { return price; }
    double getWeight() const { return weight; }

    // Сеттеры
    void setPrice(double newPrice) { price = newPrice; }
    void setExpirationDate(time_t date) { expirationDate = date; }

    // Виртуальные методы
    virtual void displayInfo() const;
    virtual bool isExpired() const;
    virtual std::string getProductType() const = 0; // чистый виртуальный
};

// Обычный товар с фиксированными характеристиками
class RegularProduct : public Product {
private:
    int quantityInPackage; // количество в упаковке

public:
    RegularProduct(const std::string& barcode, const std::string& name,
        const std::string& manufacturer, double price,
        double weight, int quantity = 1);

    std::string getProductType() const override { return "Обычный товар"; }
    void displayInfo() const override;
    int getQuantity() const { return quantityInPackage; }
};

// Товар на развес
class WeightedProduct : public Product {
private:
    double pricePerKg;
    double actualWeight; // фактический вес при покупке

public:
    WeightedProduct(const std::string& barcode, const std::string& name,
        const std::string& manufacturer, double pricePerKg);

    std::string getProductType() const override { return "Развесной товар"; }
    double getPricePerKg() const { return pricePerKg; }
    void setActualWeight(double weight) { actualWeight = weight; }
    double getActualWeight() const { return actualWeight; }
    double calculateFinalPrice() const { return pricePerKg * actualWeight / 1000; }
    void displayInfo() const override;
};

// Товар с возрастным ограничением
class AgeRestrictedProduct : public Product {
private:
    int minimumAge; // минимальный возраст для покупки

public:
    AgeRestrictedProduct(const std::string& barcode, const std::string& name,
        const std::string& manufacturer, double price,
        double weight, int minAge);

    std::string getProductType() const override { return "Товар с возрастным ограничением"; }
    int getMinimumAge() const { return minimumAge; }
    bool verifyAge(int customerAge) const;
    void displayInfo() const override;
};