#pragma once
#include <memory>
#include "Turnstile.h"
#include "PaymentSystem.h"
#include "CheckoutScale.h"
#include "ShoppingCart.h"
#include "Customer.h"

class AccessController {
    std::shared_ptr<Turnstile> entryTurnstile;
    std::shared_ptr<Turnstile> exitTurnstile;
    std::shared_ptr<CheckoutScale> scales;
public:
    AccessController(std::shared_ptr<Turnstile> entry,
        std::shared_ptr<Turnstile> exit,
        std::shared_ptr<CheckoutScale> scale);
    bool requestEntry(std::shared_ptr<Customer> cust, const std::string& cred);
    bool requestExit(std::shared_ptr<Customer> cust,
        std::shared_ptr<ShoppingCart> cart,
        std::shared_ptr<PaymentSystem> payment,
        const std::string& details);
};