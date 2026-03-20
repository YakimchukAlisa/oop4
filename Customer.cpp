#include "Customer.h"
#include <ctime>
#include <sstream>

// Реализация Customer
Customer::Customer(int id, const std::string& name, const std::string& phone)
    : id(id), name(name), phoneNumber(phone), status(CustomerStatus::ACTIVE) {}

void Customer::displayInfo() const {
    std::cout << "ID: " << id << ", Имя: " << name
        << ", Телефон: " << phoneNumber << std::endl;
}

// Реализация GuestCustomer
GuestCustomer::GuestCustomer(int id, const std::string& name, const std::string& phone)
    : Customer(id, name, phone), sessionDurationMinutes(30) {
    sessionStartTime = std::time(nullptr);
}

bool GuestCustomer::authenticate(const std::string& credentials) {
    // Гость аутентифицируется по QR-коду или банковской карте
    std::cout << "Гостевой покупатель " << name
        << " аутентифицирован по временному пропуску" << std::endl;
    return true;
}

void GuestCustomer::extendSession(int minutes) {
    sessionDurationMinutes += minutes;
    std::cout << "Сессия гостя " << name << " продлена на " << minutes << " минут" << std::endl;
}

bool GuestCustomer::isSessionExpired() const {
    time_t currentTime = std::time(nullptr);
    double elapsedSeconds = std::difftime(currentTime, sessionStartTime);
    return (elapsedSeconds / 60) > sessionDurationMinutes;
}

void GuestCustomer::displayInfo() const {
    Customer::displayInfo();
    std::cout << "Тип: Гость, Сессия: " << (isSessionExpired() ? "Истекла" : "Активна") << std::endl;
}

// Реализация LoyaltyCustomer
LoyaltyCustomer::LoyaltyCustomer(int id, const std::string& name, const std::string& phone, double discount)
    : Customer(id, name, phone), discountRate(discount), defaultPaymentMethod("Банковская карта") {}

bool LoyaltyCustomer::authenticate(const std::string& credentials) {
    // Постоянный покупатель может входить по лицу или отпечатку пальца
    std::cout << "Постоянный покупатель " << name
        << " аутентифицирован по биометрии. Персональная скидка: "
        << (discountRate * 100) << "%" << std::endl;
    return true;
}

void LoyaltyCustomer::addPurchase(const std::string& purchase) {
    purchaseHistory.push_back(purchase);
}

void LoyaltyCustomer::displayInfo() const {
    Customer::displayInfo();
    std::cout << "Тип: Постоянный покупатель, Скидка: " << (discountRate * 100)
        << "%, История покупок: " << purchaseHistory.size() << " записей" << std::endl;
}

// Реализация CorporateCustomer
CorporateCustomer::CorporateCustomer(int id, const std::string& name, const std::string& phone,
    const std::string& company, const std::string& taxId)
    : Customer(id, name, phone), companyName(company), companyTaxId(taxId), invoiceRequired(true) {}

bool CorporateCustomer::authenticate(const std::string& credentials) {
    std::cout << "Корпоративный клиент " << name << " от компании "
        << companyName << " аутентифицирован" << std::endl;
    return true;
}

std::string CorporateCustomer::generateInvoice(int orderId) const {
    std::ostringstream invoice;
    invoice << "СЧЕТ №" << orderId << "\n"
        << "Покупатель: " << companyName << "\n"
        << "ИНН: " << companyTaxId << "\n"
        << "Представитель: " << name;
    return invoice.str();
}

void CorporateCustomer::displayInfo() const {
    Customer::displayInfo();
    std::cout << "Тип: Корпоративный клиент, Компания: " << companyName
        << ", ИНН: " << companyTaxId << std::endl;
}