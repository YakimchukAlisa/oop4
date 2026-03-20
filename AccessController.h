#pragma once
#include <memory>
#include "Turnstile.h"
#include "PaymentSystem.h"
#include "CheckoutScale.h"
#include "ShoppingCart.h"
#include "Customer.h"

// Класс контроллера доступа (использует Proxy и Делегирование)
class AccessController {
private:
    std::shared_ptr<Turnstile> entryTurnstile;
    std::shared_ptr<Turnstile> exitTurnstile;
    std::shared_ptr<CheckoutScale> scales;

public:
    AccessController(std::shared_ptr<Turnstile> entry,
        std::shared_ptr<Turnstile> exit,
        std::shared_ptr<CheckoutScale> checkoutScales);

    // Методы управления доступом
    bool requestEntry(std::shared_ptr<Customer> customer, const std::string& credentials);
    bool requestExit(std::shared_ptr<Customer> customer,
        std::shared_ptr<ShoppingCart> cart,
        std::shared_ptr<PaymentSystem> paymentMethod,
        const std::string& paymentDetails);

    void emergencyUnlockAll();
    void displayInfo() const;
};