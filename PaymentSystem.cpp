#include "PaymentSystem.h"
#include <sstream>
#include <iomanip>
#include <thread>
#include <chrono>

// Реализация BankCardPayment
BankCardPayment::BankCardPayment(const std::string& endpoint, const std::string& merchant)
    : bankApiEndpoint(endpoint), merchantId(merchant), connectionEstablished(false) {
    std::cout << "Создан Proxy для банковской карты. Эндпоинт: " << endpoint << std::endl;
}

BankCardPayment::~BankCardPayment() {
    if (connectionEstablished) {
        std::cout << "Закрытие соединения с банком" << std::endl;
    }
}

bool BankCardPayment::connectToBank() {
    std::cout << "Proxy: Устанавливаю соединение с банком по адресу "
        << bankApiEndpoint << "..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(500)); // имитация задержки
    connectionEstablished = true;
    std::cout << "Proxy: Соединение установлено" << std::endl;
    return true;
}

bool BankCardPayment::sendPaymentRequest(double amount, const std::string& cardNumber) {
    std::cout << "Proxy: Отправка запроса в банк. Списание " << amount
        << " руб. с карты " << cardNumber.substr(0, 4) << "******" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    return true; // имитация успеха
}

std::string BankCardPayment::processBankResponse(const std::string& response) {
    std::cout << "Proxy: Обработка ответа от банка: " << response << std::endl;
    return "TRANSACTION_SUCCESS_" + std::to_string(rand() % 10000);
}

bool BankCardPayment::processPayment(double amount, const std::string& cardNumber) {
    std::cout << "\n=== Proxy (Банковская карта) ===" << std::endl;
    std::cout << "Получен запрос на оплату " << amount << " руб." << std::endl;

    // 1. Устанавливаем соединение (если нужно)
    if (!connectionEstablished) {
        connectToBank();
    }

    // 2. Отправляем запрос в банк
    if (!sendPaymentRequest(amount, cardNumber)) {
        std::cout << "Ошибка отправки запроса" << std::endl;
        return false;
    }

    // ПРОВЕРКА: неверный номер карты
    if (cardNumber == "0000000000000000" || cardNumber.length() != 16) {
        std::cout << "Proxy: БАНК ОТКЛОНИЛ операцию! Неверный номер карты." << std::endl;
        return false;  
    }

    // 3. Получаем и обрабатываем ответ
    std::string transactionId = processBankResponse("SUCCESS");

    std::cout << "Оплата прошла успешно! ID транзакции: " << transactionId << std::endl;
    return true;
}

std::string BankCardPayment::generateReceipt(int transactionId) {
    std::ostringstream receipt;
    receipt << "ЧЕК №" << transactionId << "\n"
        << "Способ оплаты: Банковская карта\n"
        << "Терминал: " << merchantId << "\n"
        << "Спасибо за покупку!";
    return receipt.str();
}

// Реализация LoyaltyPointsPayment
LoyaltyPointsPayment::LoyaltyPointsPayment() : pointsBalance(1000) {}

bool LoyaltyPointsPayment::checkPointsBalance(int customerId, double amount) {
    std::cout << "Проверка баланса бонусов для клиента " << customerId << ": ";
    std::cout << "доступно " << pointsBalance << " бонусов, нужно " << amount << std::endl;
    return pointsBalance >= amount;
}

double LoyaltyPointsPayment::calculatePointsDiscount(double amount) {
    return amount * 0.1; // 10% бонусами
}

bool LoyaltyPointsPayment::processPayment(double amount, const std::string& customerId) {
    std::cout << "\n=== Внутренняя система оплаты бонусами ===" << std::endl;
    std::cout << "Запрос на оплату " << amount << " руб. бонусами для клиента " << customerId << std::endl;

    int id = std::stoi(customerId);
    if (checkPointsBalance(id, amount)) {
        pointsBalance -= amount;
        std::cout << "Оплата бонусами прошла успешно. Остаток бонусов: " << pointsBalance << std::endl;
        return true;
    }
    else {
        std::cout << "Недостаточно бонусов!" << std::endl;
        return false;
    }
}

std::string LoyaltyPointsPayment::generateReceipt(int transactionId) {
    std::ostringstream receipt;
    receipt << "ЧЕК №" << transactionId << "\n"
        << "Способ оплаты: Бонусы лояльности\n"
        << "Списано бонусов: " << transactionId << "\n"
        << "Спасибо за использование программы лояльности!";
    return receipt.str();
}

// Реализация MobileAppPayment
MobileAppPayment::MobileAppPayment() : appToken("DEFAULT_TOKEN") {}

bool MobileAppPayment::sendPushConfirmation(const std::string& message) {
    std::cout << "Отправка push-уведомления в мобильное приложение: " << message << std::endl;
    return true;
}

bool MobileAppPayment::processMobileToken(const std::string& token) {
    std::cout << "Проверка токена мобильного приложения: " << token << std::endl;
    return token.length() > 5; // простая валидация
}

bool MobileAppPayment::processPayment(double amount, const std::string& token) {
    std::cout << "\n=== Оплата через мобильное приложение ===" << std::endl;
    std::cout << "Запрос на оплату " << amount << " руб. через мобильное приложение" << std::endl;

    if (!processMobileToken(token)) {
        std::cout << "Недействительный токен!" << std::endl;
        return false;
    }

    sendPushConfirmation("Подтвердите оплату на сумму " + std::to_string(amount) + " руб.");
    std::cout << "Оплата через мобильное приложение прошла успешно" << std::endl;
    return true;
}

std::string MobileAppPayment::generateReceipt(int transactionId) {
    std::ostringstream receipt;
    receipt << "ЧЕК №" << transactionId << "\n"
        << "Способ оплаты: Мобильное приложение\n"
        << "Электронный чек отправлен в приложение\n"
        << "Спасибо!";
    return receipt.str();
}