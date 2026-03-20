#pragma once
#include <string>

class Product {
    std::string name;
    double price;
    double weight;
public:
    Product(const std::string& name, double price, double weight);
    std::string getName() const { return name; }
    double getPrice() const { return price; }
    double getWeight() const { return weight; }
};

class RegularProduct : public Product {
public:
    RegularProduct(const std::string& name, double price, double weight);
};