#include "Customer.h"

Customer::Customer(int id, const std::string& name) : id(id), name(name) {}

GuestCustomer::GuestCustomer(int id, const std::string& name) : Customer(id, name) {}
bool GuestCustomer::authenticate(const std::string&) {
    std::cout << "Гостевой покупатель " << name << " аутентифицирован\n";
    return true;
}

LoyaltyCustomer::LoyaltyCustomer(int id, const std::string& name, double discount)
    : Customer(id, name), discountRate(discount) {}
bool LoyaltyCustomer::authenticate(const std::string&) {
    std::cout << "Постоянный покупатель " << name << " аутентифицирован. Скидка: " << discountRate * 100 << "%\n";
    return true;
}
double LoyaltyCustomer::applyDiscount(double price) const {
    return price * (1.0 - discountRate);
}