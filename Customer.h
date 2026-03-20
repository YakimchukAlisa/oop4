#pragma once
#include <string>
#include <vector>
#include <memory>
#include <iostream>

// Перечисление статусов покупателя
enum class CustomerStatus {
    ACTIVE,
    BLOCKED,
    SESSION_EXPIRED
};

// Абстрактный базовый класс Customer
class Customer {
protected:
    int id;
    std::string name;
    std::string phoneNumber;
    CustomerStatus status;

public:
    Customer(int id, const std::string& name, const std::string& phone);
    virtual ~Customer() = default;

    // Чисто виртуальный метод - обязательный для всех наследников
    virtual bool authenticate(const std::string& credentials) = 0;

    // Геттеры
    int getId() const { return id; }
    std::string getName() const { return name; }
    CustomerStatus getStatus() const { return status; }

    // Сеттеры
    void setStatus(CustomerStatus newStatus) { status = newStatus; }

    // Виртуальный метод для вывода информации
    virtual void displayInfo() const;
};

// Класс гостевого покупателя
class GuestCustomer : public Customer {
private:
    time_t sessionStartTime;
    int sessionDurationMinutes; // максимальная длительность сессии в минутах

public:
    GuestCustomer(int id, const std::string& name, const std::string& phone);

    bool authenticate(const std::string& credentials) override;
    void extendSession(int minutes);
    bool isSessionExpired() const;
    void displayInfo() const override;
};

// Класс постоянного покупателя
class LoyaltyCustomer : public Customer {
private:
    std::vector<std::string> purchaseHistory;
    std::string defaultPaymentMethod;
    double discountRate; // персональная скидка (0.0 - 1.0)

public:
    LoyaltyCustomer(int id, const std::string& name, const std::string& phone,
        double discount = 0.05);

    bool authenticate(const std::string& credentials) override;
    std::string getPaymentMethod() const { return defaultPaymentMethod; }
    std::vector<std::string> getPurchaseHistory() const { return purchaseHistory; }
    double applyDiscount(double price) const { return price * (1.0 - discountRate); }
    void addPurchase(const std::string& purchase);
    void displayInfo() const override;
};

// Класс корпоративного покупателя
class CorporateCustomer : public Customer {
private:
    std::string companyName;
    std::string companyTaxId;
    bool invoiceRequired;

public:
    CorporateCustomer(int id, const std::string& name, const std::string& phone,
        const std::string& company, const std::string& taxId);

    bool authenticate(const std::string& credentials) override;
    std::string getCompanyDetails() const { return companyName + " (ИНН: " + companyTaxId + ")"; }
    void setInvoiceRequired(bool required) { invoiceRequired = required; }
    std::string generateInvoice(int orderId) const;
    void displayInfo() const override;
};