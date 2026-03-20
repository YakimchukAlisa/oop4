#pragma once
#include <string>
#include <iostream>

class Customer {
protected:
    int id;
    std::string name;
public:
    Customer(int id, const std::string& name);
    virtual ~Customer() = default;
    virtual bool authenticate(const std::string& credentials) = 0;
    int getId() const { return id; }
    std::string getName() const { return name; }
};

class GuestCustomer : public Customer {
public:
    GuestCustomer(int id, const std::string& name);
    bool authenticate(const std::string& credentials) override;
};

class LoyaltyCustomer : public Customer {
    double discountRate;
public:
    LoyaltyCustomer(int id, const std::string& name, double discount);
    bool authenticate(const std::string& credentials) override;
    double applyDiscount(double price) const;
};