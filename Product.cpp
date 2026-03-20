#include "Product.h"

Product::Product(const std::string& name, double price, double weight)
    : name(name), price(price), weight(weight) {}

RegularProduct::RegularProduct(const std::string& name, double price, double weight)
    : Product(name, price, weight) {}