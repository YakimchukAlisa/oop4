#pragma once
#include <iostream>

class CheckoutScale {
protected:
    int id;
    double expectedWeight;
    double precision;
public:
    CheckoutScale(int id, double prec = 1.0);
    void setExpectedWeight(double w) { expectedWeight = w; }
    virtual bool verifyWeight() = 0;
    virtual ~CheckoutScale() = default;
};

class HighPrecisionScale : public CheckoutScale {
public:
    HighPrecisionScale(int id);
    bool verifyWeight() override;
};