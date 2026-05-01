#include "PaymentSystem.h"
#include <thread>
#include <chrono>

BankCardPayment::BankCardPayment(const std::string& ep, const std::string& merchant)
    : endpoint(ep), merchantId(merchant), connected(false) {
    // Инициализация балансов тестовых карт
    cardBalances["4111111111111111"] = 10000.0;
    cardBalances["5555555555554444"] = 5000.0;
    cardBalances["378282246310005"] = 2000.0;
    cardBalances["0000000000000000"] = 0.0;
}

bool BankCardPayment::checkBalance(const std::string& cardNumber, double amount) {
    auto it = cardBalances.find(cardNumber);
    if (it == cardBalances.end()) {
        std::cout << "Карта " << cardNumber.substr(0, 4) << "**** не найдена\n";
        return false;
    }

    double balance = it->second;
    std::cout << " Баланс карты " << cardNumber.substr(0, 4) << "****: "
        << balance << " руб.\n";

    if (balance >= amount) {
        std::cout << "Средств достаточно\n";
        return true;
    }
    else {
        std::cout << "НЕДОСТАТОЧНО СРЕДСТВ! Нужно: " << amount
            << ", доступно: " << balance << "\n";
        return false;
    }
}

bool BankCardPayment::sendRequest(double amount, const std::string& card) {
    std::cout << "Отправка запроса в банк. Списание " << amount
        << " руб. с карты " << card.substr(0, 4) << "****\n";

    if (!checkBalance(card, amount)) {
        return false;
    }

    cardBalances[card] -= amount;
    std::cout << " Средства списаны. Новый баланс: " << cardBalances[card] << " руб.\n";

    return true;
}

void BankCardPayment::setCardBalance(const std::string& cardNumber, double balance) {
    cardBalances[cardNumber] = balance;
}

bool BankCardPayment::connectToBank() {
    std::cout << "Соединение с " << endpoint << "...\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    connected = true;
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