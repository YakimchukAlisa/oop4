#pragma once
#include <memory>
#include <vector>
#include "Customer.h"
#include "Product.h"
#include "ShoppingCart.h"
#include "Turnstile.h"
#include "CheckoutScale.h"
#include "PaymentSystem.h"
#include "AccessController.h"
#include "Configurator.h"

class ShopSimulation {
    std::vector<std::shared_ptr<Customer>> customers;
    std::vector<std::shared_ptr<Product>> products;
    std::shared_ptr<Turnstile> entryTurnstile, exitTurnstile;
    std::shared_ptr<CheckoutScale> scales;
    std::shared_ptr<AccessController> accessController;
    std::shared_ptr<Configurator> config;
    int nextCartId, nextCustomerId;
public:
    ShopSimulation();
    void initialize(const Configurator& cfg);
    void runSimulation();
private:
    void createCustomers();
    void createProducts();
    void createEquipment();
    std::shared_ptr<ShoppingCart> createCartForCustomer(int custId);
    void scenarioProxy();
    void scenarioDelegation();
};