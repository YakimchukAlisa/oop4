#pragma once
#include <string>
#include <vector>
#include <memory>
#include <map>
#include "Product.h"

// Абстрактный базовый класс SmartShelf
class SmartShelf {
protected:
    int shelfId;
    std::string location; // например, "Ряд А, Полка 3"
    double currentWeight;
    std::map<std::string, std::shared_ptr<Product>> products; // товары на полке

public:
    SmartShelf(int id, const std::string& loc, double initialWeight = 0);
    virtual ~SmartShelf() = default;

    // События, которые генерирует полка
    virtual void onWeightChanged(double newWeight) = 0;

    // Базовые методы
    virtual double getCurrentWeight() const { return currentWeight; }
    virtual int getShelfId() const { return shelfId; }
    virtual std::string getLocation() const { return location; }
    virtual void addProduct(std::shared_ptr<Product> product);
    virtual void displayInfo() const;
};

// Полка с тензодатчиками
class WeightBasedShelf : public SmartShelf {
private:
    double tareWeight; // вес самой полки
    bool isCalibrated;
    double weightPerUnit; // вес одной единицы товара

public:
    WeightBasedShelf(int id, const std::string& loc, double tare, double weightPerUnit = 0);

    void onWeightChanged(double newWeight) override;
    void calibrateSensors();
    double getTareWeight() const { return tareWeight; }
    std::shared_ptr<Product> detectProductTaken(double weightDelta);
    void displayInfo() const override;
};

// Полка с RFID-метками
class RFIDBasedShelf : public SmartShelf {
private:
    std::vector<std::string> currentTags; // текущие RFID-метки

public:
    RFIDBasedShelf(int id, const std::string& loc, double initialWeight = 0);

    void onWeightChanged(double newWeight) override;
    std::vector<std::string> scanRFIDTags();
    std::vector<std::string> getDetectedTags() const { return currentTags; }
    void addProductWithTag(std::shared_ptr<Product> product, const std::string& tag);
    void displayInfo() const override;
};