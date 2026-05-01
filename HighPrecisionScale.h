#pragma once
#include "CheckoutScale.h"
#include <iostream>
#include <cmath>
#include <cstdlib>

class HighPrecisionScale : public CheckoutScale {
private:
    int id;
    double expectedWeight;
    double precision;
    double maxWeight;

public:
    HighPrecisionScale(int id);

    double weigh() override;
    bool verifyWeight(double expected) override;
    void setExpectedWeight(double weight) override;
    double getMaxWeight() const override;
    double getPrecision() const override;
    std::string getType() const override;

    void calibrate();
};