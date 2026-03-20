#pragma once
#include <string>
#include <iostream>
#include <memory>

// Интерфейс PaymentSystem (Proxy для внешних платежных систем)
class PaymentSystem {
public:
    virtual ~PaymentSystem() = default;

    // Основные методы для всех платежных систем
    virtual bool processPayment(double amount, const std::string& paymentDetails) = 0;
    virtual std::string generateReceipt(int transactionId) = 0;
    virtual std::string getPaymentType() const = 0;
};

// Proxy для банковской карты (работает с внешним банком)
class BankCardPayment : public PaymentSystem {
private:
    std::string bankApiEndpoint;
    std::string merchantId;
    bool connectionEstablished;

    // Приватные методы - детали реализации, скрытые от клиента
    bool connectToBank();
    bool sendPaymentRequest(double amount, const std::string& cardNumber);
    std::string processBankResponse(const std::string& response);

public:
    BankCardPayment(const std::string& endpoint, const std::string& merchant);
    ~BankCardPayment();

    bool processPayment(double amount, const std::string& cardNumber) override;
    std::string generateReceipt(int transactionId) override;
    std::string getPaymentType() const override { return "Банковская карта"; }
};

// Внутренняя система оплаты бонусами (не требует внешнего шлюза)
class LoyaltyPointsPayment : public PaymentSystem {
private:
    double pointsBalance;

    bool checkPointsBalance(int customerId, double amount);
    double calculatePointsDiscount(double amount);

public:
    LoyaltyPointsPayment();

    bool processPayment(double amount, const std::string& customerId) override;
    std::string generateReceipt(int transactionId) override;
    std::string getPaymentType() const override { return "Бонусы лояльности"; }
};

// Оплата через мобильное приложение (Google Pay / Apple Pay)
class MobileAppPayment : public PaymentSystem {
private:
    std::string appToken;
    bool sendPushConfirmation(const std::string& message);
    bool processMobileToken(const std::string& token);

public:
    MobileAppPayment();

    bool processPayment(double amount, const std::string& token) override;
    std::string generateReceipt(int transactionId) override;
    std::string getPaymentType() const override { return "Мобильное приложение"; }
};