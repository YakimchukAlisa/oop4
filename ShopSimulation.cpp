#include "ShopSimulation.h"
#include <iostream>
#include <thread>
#include <chrono>

ShopSimulation::ShopSimulation() : nextCartId(1000), nextCustomerId(1) {}

void ShopSimulation::initialize(const Configurator& cfg) {
    config = std::make_shared<Configurator>(cfg);

    std::cout << "\n=== ИНИЦИАЛИЗАЦИЯ МАГАЗИНА ===" << std::endl;

    createProducts();
    createCustomers();     // Создаем обоих покупателей
    createEquipment(cfg);

    std::cout << "\nМагазин готов к работе!" << std::endl;
}

void ShopSimulation::createCustomers() {
    // Обычный покупатель (для Proxy)
    customers.push_back(std::make_shared<GuestCustomer>(nextCustomerId++, "Иван Петров", "+7-999-123-45-67"));

    // Постоянный покупатель со скидкой (для Делегирования)
    customers.push_back(std::make_shared<LoyaltyCustomer>(nextCustomerId++, "Анна Смирнова", "+7-999-234-56-78", 0.1));
}

void ShopSimulation::createProducts() {
    // Минимум товаров
    products.push_back(std::make_shared<RegularProduct>("460000000001", "Молоко", "Молочный комбинат", 85.0, 1000));
    products.push_back(std::make_shared<RegularProduct>("460000000002", "Хлеб", "Хлебозавод", 45.0, 400));
    products.push_back(std::make_shared<RegularProduct>("460000000003", "Шоколад", "Mondelez", 120.0, 90));
}

void ShopSimulation::createEquipment(const Configurator& cfg) {
    // Только самое необходимое
    entryTurnstile = std::make_shared<Turnstile>(301, "Вход");
    exitTurnstile = std::make_shared<Turnstile>(302, "Выход");
    scales = std::make_shared<HighPrecisionScale>(401, "Зона выхода");

    accessController = std::make_shared<AccessController>(entryTurnstile, exitTurnstile, scales);
}

std::shared_ptr<ShoppingCart> ShopSimulation::createCartForCustomer(int customerId) {
    return std::make_shared<ShoppingCart>(nextCartId++, customerId);
}

void ShopSimulation::runSimulation() {
    std::cout << "\n\n========== ЗАПУСК СИМУЛЯЦИИ ==========\n" << std::endl;

    // СЦЕНАРИЙ 1: PROXY (BankCardPayment + AccessController)
    scenarioProxy();

    std::this_thread::sleep_for(std::chrono::seconds(1));

    // СЦЕНАРИЙ 2: ДЕЛЕГИРОВАНИЕ (расчет скидки)
    scenarioDelegation();
}

// ========== СЦЕНАРИЙ 1: PROXY ==========
void ShopSimulation::scenarioProxy() {
    std::cout << "\n\n---------- СЦЕНАРИЙ 1: ПАТТЕРН PROXY ----------\n" << std::endl;
    std::cout << "Демонстрация:" << std::endl;
    std::cout << "  1. BankCardPayment - удаленный прокси для банка" << std::endl;
    std::cout << "  2. AccessController - защищающий прокси для турникета\n" << std::endl;

    auto customer = customers[0]; // GuestCustomer
    auto cart = createCartForCustomer(customer->getId());

    // Вход в магазин
    accessController->requestEntry(customer, "QR-CODE-12345");

    // Покупатель берет товары
    std::cout << "\n--- Покупатель выбирает товары ---" << std::endl;
    cart->addItem(products[0]); // Молоко
    cart->addItem(products[1]); // Хлеб

    cart->displayCart();

    // Выход и оплата через Proxy
    std::cout << "\n--- Демонстрация Proxy: BankCardPayment ---" << std::endl;
    auto paymentMethod = std::make_shared<BankCardPayment>("https://api.bank.ru/v1", "MERCHANT-001");

    std::cout << "\n>>> BankCardPayment ПРОКСИ: скрывает соединение с банком, отправку запроса, обработку ответа" << std::endl;
    std::cout << ">>> AccessController ПРОКСИ: проверяет оплату и вес перед открытием двери\n" << std::endl;

    accessController->requestExit(customer, cart, paymentMethod, "4111111111111111");
}

// ========== СЦЕНАРИЙ 2: ДЕЛЕГИРОВАНИЕ ==========
void ShopSimulation::scenarioDelegation() {
    std::cout << "\n\n---------- СЦЕНАРИЙ 2: ПАТТЕРН ДЕЛЕГИРОВАНИЕ ----------\n" << std::endl;
    std::cout << "Демонстрация: ShoppingCart делегирует расчет скидки объекту LoyaltyCustomer\n" << std::endl;

    auto customer = customers[1]; // LoyaltyCustomer со скидкой 10%
    auto cart = createCartForCustomer(customer->getId());

    // Вход в магазин
    accessController->requestEntry(customer, "QR-CODE-12345");

    // Покупка товаров
    std::cout << "\n--- Покупатель выбирает товары ---" << std::endl;
    cart->addItem(products[2]); // Шоколад - 120 руб.

    cart->displayCart();

    double baseTotal = cart->calculateTotal();
    std::cout << "\nБазовая стоимость: " << baseTotal << " руб." << std::endl;

    // Делегирование
    double finalPrice = cart->calculateFinalPrice(customer);

    std::cout << "\nИтоговая стоимость со скидкой 10%: " << finalPrice << " руб." << std::endl;
    std::cout << "   (скидку применил метод LoyaltyCustomer::applyDiscount())" << std::endl;

    // Оплата
    auto paymentMethod = std::make_shared<LoyaltyPointsPayment>();
    accessController->requestExit(customer, cart, paymentMethod, std::to_string(customer->getId()));
}