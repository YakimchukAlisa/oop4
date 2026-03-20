#include "PaymentSystem.h"
#include <thread>
#include <chrono>

BankCardPayment::BankCardPayment(const std::string& ep, const std::string& merchant)
    : endpoint(ep), merchantId(merchant), connected(false) {}

bool BankCardPayment::connectToBank() {
    std::cout << "Proxy: соединение с " << endpoint << "...\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    connected = true;
    return true;
}

bool BankCardPayment::sendRequest(double amount, const std::string& card) {
    std::cout << "Proxy: списание " << amount << " руб. с карты " << card.substr(0, 4) << "****\n";
    return true;
}

bool BankCardPayment::processPayment(double amount, const std::string& cardNumber) {
    std::cout << "=== Proxy BankCard ===\n";
    if (!connected) connectToBank();
    if (!sendRequest(amount, cardNumber)) return false;
    std::cout << "Оплата успешна\n";
    return true;
}

std::string BankCardPayment::generateReceipt(int id) {
    return "Чек #" + std::to_string(id) + " (банковская карта)";
}

bool LoyaltyPointsPayment::processPayment(double amount, const std::string& customerId) {
    std::cout << "=== Оплата бонусами ===\n";
    std::cout << "Списано " << amount << " бонусов у клиента " << customerId << "\n";
    return true;
}

std::string LoyaltyPointsPayment::generateReceipt(int id) {
    return "Чек #" + std::to_string(id) + " (бонусы)";
}