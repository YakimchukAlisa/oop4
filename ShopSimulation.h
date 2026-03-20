#pragma once
#include <memory>
#include <vector>
#include "Customer.h"
#include "Product.h"
#include "Turnstile.h"
#include "CheckoutScale.h"
#include "ShoppingCart.h"
#include "PaymentSystem.h"
#include "AccessController.h"
#include "Configurator.h"

class ShopSimulation {
private:
    // Покупатели (только два нужных)
    std::vector<std::shared_ptr<Customer>> customers;

    // Товары
    std::vector<std::shared_ptr<Product>> products;

    // Оборудование (только самое необходимое)
    std::shared_ptr<Turnstile> entryTurnstile;
    std::shared_ptr<Turnstile> exitTurnstile;
    std::shared_ptr<CheckoutScale> scales;
    std::shared_ptr<AccessController> accessController;

    // Конфигурация
    std::shared_ptr<Configurator> config;

    // Счетчики
    int nextCartId;
    int nextCustomerId;

public:
    ShopSimulation();

    // Инициализация и запуск
    void initialize(const Configurator& cfg);
    void runSimulation();

private:
    // Вспомогательные методы
    void createCustomers();
    void createProducts();
    void createEquipment(const Configurator& cfg);
    std::shared_ptr<ShoppingCart> createCartForCustomer(int customerId);

    // Два сценария для демонстрации паттернов
    void scenarioProxy();        // Показывает BankCardPayment и AccessController
    void scenarioDelegation();   // Показывает делегирование скидки LoyaltyCustomer
};