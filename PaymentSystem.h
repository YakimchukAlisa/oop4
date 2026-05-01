#pragma once
#include <string>
#include <iostream>
#include <map>

class PaymentSystem {
public:
    virtual ~PaymentSystem() = default;
    virtual bool processPayment(double amount, const std::string& details) = 0;
    virtual std::string generateReceipt(int id) = 0;
};

class BankCardPayment: public PaymentSystem {
    std::string endpoint;
    std::string merchantId;
    bool connected;
    bool connectToBank();
    bool sendRequest(double amount, const std::string& card);
private:
    std::map<std::string, double> cardBalances;  
    bool checkBalance(const std::string& cardNumber, double amount); 

public:
    BankCardPayment(const std::string& ep, const std::string& merchant);
    bool processPayment(double amount, const std::string& cardNumber) override;
    std::string generateReceipt(int id) override;
    void setCardBalance(const std::string& cardNumber, double balance);  
};

class LoyaltyPointsPayment : public PaymentSystem {
public:
    bool processPayment(double amount, const std::string& customerId) override;
    std::string generateReceipt(int id) override;
};