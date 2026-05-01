#pragma once
#include <string>

class CheckoutScale {
public:
    virtual ~CheckoutScale() = default;

    virtual double weigh() = 0;
    virtual bool verifyWeight(double expected) = 0;
    virtual void setExpectedWeight(double weight) = 0;
    virtual double getMaxWeight() const = 0;
    virtual double getPrecision() const = 0;
    virtual std::string getType() const = 0;
};