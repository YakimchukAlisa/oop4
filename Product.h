#pragma once
#include <string>


class Product {
public:
    virtual ~Product() = default;
    virtual std::string getName() const = 0;
    virtual double getPrice() const = 0;
    virtual double getWeight() const = 0;
    virtual std::string getDescription() const = 0;
};


class IWeightedProduct : public Product {
public:
    virtual void setWeight(double grams) = 0;
};


class RegularProduct : public Product {
private:
    std::string name;
    double price;
    double weight;

public:
    RegularProduct(const std::string& name, double price, double weight);

    std::string getName() const override;
    double getPrice() const override;
    double getWeight() const override;
    std::string getDescription() const override;
};


class WeightedProduct : public IWeightedProduct {
private:
    std::string name;
    double pricePerKg;
    double actualWeight;

public:
    WeightedProduct(const std::string& name, double pricePerKg);

    std::string getName() const override;
    double getPrice() const override;
    double getWeight() const override;
    std::string getDescription() const override;

    void setWeight(double grams) override;
    double getPricePerKg() const;
    double calculatePrice() const;
};