#pragma once
#include "CheckoutScale.h"
#include <iostream>
#include <cmath>

class PostalScale : public CheckoutScale {
private:
    int id;
    double expectedWeight;
    double precision;   // 10 г
    double maxWeight;   // 30 кг
    bool isRounded;     // всегда true для почтовых весов

public:
    PostalScale(int id);

    double weigh() override;
    bool verifyWeight(double expected) override;
    void setExpectedWeight(double weight) override;
    double getMaxWeight() const override;
    double getPrecision() const override;
    std::string getType() const override;

    // Дополнительный метод для расчета доставки
    double calculatePostage() const;
};