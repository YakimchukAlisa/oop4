#pragma once
#include <string>
#include <memory>
#include "Product.h"
#include "ShoppingCart.h"

// Абстрактный базовый класс CheckoutScale
class CheckoutScale {
protected:
    int scaleId;
    std::string location;
    double currentWeight;
    double precision;
    double expectedWeight;  // Добавляем поле для ожидаемого веса

public:
    CheckoutScale(int id, const std::string& loc, double prec = 1.0);
    virtual ~CheckoutScale() = default;

    virtual double weighProducts() = 0;
    virtual bool verifyWeight(double expectedWeight = 0) = 0;

    void setExpectedWeight(double weight);  // Новый метод

    double getCurrentWeight() const { return currentWeight; }
    int getScaleId() const { return scaleId; }
    virtual void displayInfo() const;
};

// Высокоточные весы
class HighPrecisionScale : public CheckoutScale {
public:
    HighPrecisionScale(int id, const std::string& loc);

    double weighProducts() override;
    bool verifyWeight(double expectedWeight = 0) override;
    void calibrateWithReference(double referenceWeight);
    void displayInfo() const override;
};

// ... остальные классы (IndustrialScale, BarcodeScale, SmartScale) ...