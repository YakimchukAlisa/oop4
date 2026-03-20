#include "ShopSimulation.h"
#include <thread>
#include <chrono>

ShopSimulation::ShopSimulation() : nextCartId(1000), nextCustomerId(1) {}

void ShopSimulation::initialize(const Configurator& cfg) {
    config = std::make_shared<Configurator>(cfg);
    std::cout << "\n=== ИНИЦИАЛИЗАЦИЯ ===\n";
    createProducts();
    createCustomers();
    createEquipment();
    std::cout << "Магазин готов\n";
}

void ShopSimulation::createCustomers() {
    customers.push_back(std::make_shared<GuestCustomer>(nextCustomerId++, "Иван Петров"));
    customers.push_back(std::make_shared<LoyaltyCustomer>(nextCustomerId++, "Анна Смирнова", 0.1));
}

void ShopSimulation::createProducts() {
    products.push_back(std::make_shared<RegularProduct>("Молоко", 85.0, 1000));
    products.push_back(std::make_shared<RegularProduct>("Хлеб", 45.0, 400));
    products.push_back(std::make_shared<RegularProduct>("Шоколад", 120.0, 90));
}

void ShopSimulation::createEquipment() {
    entryTurnstile = std::make_shared<Turnstile>(301, "Вход");
    exitTurnstile = std::make_shared<Turnstile>(302, "Выход");
    scales = std::make_shared<HighPrecisionScale>(401);
    accessController = std::make_shared<AccessController>(entryTurnstile, exitTurnstile, scales);
}

std::shared_ptr<ShoppingCart> ShopSimulation::createCartForCustomer(int custId) {
    return std::make_shared<ShoppingCart>(nextCartId++, custId);
}

void ShopSimulation::runSimulation() {
    scenarioProxy();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    scenarioDelegation();
}

void ShopSimulation::scenarioProxy() {
    std::cout << "\n\n--- СЦЕНАРИЙ 1: PROXY ---\n";
    auto cust = customers[0];
    auto cart = createCartForCustomer(cust->getId());

    accessController->requestEntry(cust, "QR");
    cart->addItem(products[0]);
    cart->addItem(products[1]);
    cart->displayCart();

    auto payment = std::make_shared<BankCardPayment>("https://bank.ru/api", "MERCH");
    accessController->requestExit(cust, cart, payment, "4111111111111111");
}

void ShopSimulation::scenarioDelegation() {
    std::cout << "\n\n--- СЦЕНАРИЙ 2: ДЕЛЕГИРОВАНИЕ ---\n";
    auto cust = customers[1];
    auto cart = createCartForCustomer(cust->getId());

    accessController->requestEntry(cust, "BIOMETRY");
    cart->addItem(products[2]);
    cart->displayCart();

    double base = cart->calculateTotal();
    double final = cart->calculateFinalPrice(cust);
    std::cout << "Базовая цена: " << base << " руб., итого: " << final << " руб. (скидка применена через делегирование)\n";

    auto payment = std::make_shared<LoyaltyPointsPayment>();
    accessController->requestExit(cust, cart, payment, std::to_string(cust->getId()));
}