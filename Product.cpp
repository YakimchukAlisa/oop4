#include "Product.h"
#include <sstream>

RegularProduct::RegularProduct(const std::string& name, double price, double weight)
    : name(name), price(price), weight(weight) {}

std::string RegularProduct::getName() const { return name; }
double RegularProduct::getPrice() const { return price; }
double RegularProduct::getWeight() const { return weight; }

std::string RegularProduct::getDescription() const {
    std::ostringstream desc;
    desc << name << " (" << price << " руб., " << weight << " г)";
    return desc.str();
}

WeightedProduct::WeightedProduct(const std::string& name, double pricePerKg)
    : name(name), pricePerKg(pricePerKg), actualWeight(0) {}

std::string WeightedProduct::getName() const { return name; }

double WeightedProduct::getPrice() const {
    return pricePerKg * actualWeight / 1000.0;
}

double WeightedProduct::getWeight() const { return actualWeight; }

std::string WeightedProduct::getDescription() const {
    std::ostringstream desc;
    desc << name << " (развесной, " << actualWeight << " г, "
        << pricePerKg << " руб./кг)";
    return desc.str();
}

void WeightedProduct::setWeight(double grams) {
    actualWeight = grams;
}

double WeightedProduct::getPricePerKg() const {
    return pricePerKg;
}

double WeightedProduct::calculatePrice() const {
    return pricePerKg * actualWeight / 1000.0;
}