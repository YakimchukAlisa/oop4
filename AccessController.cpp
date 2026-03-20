#include "AccessController.h"

AccessController::AccessController(std::shared_ptr<Turnstile> entry,
    std::shared_ptr<Turnstile> exit,
    std::shared_ptr<CheckoutScale> scale)
    : entryTurnstile(entry), exitTurnstile(exit), scales(scale) {}

bool AccessController::requestEntry(std::shared_ptr<Customer> cust, const std::string& cred) {
    std::cout << "\n=== КОНТРОЛЛЕР ДОСТУПА: ВХОД ===\n";
    if (!cust->authenticate(cred)) return false;
    entryTurnstile->unlockForEntry();
    return true;
}

bool AccessController::requestExit(std::shared_ptr<Customer> cust,
    std::shared_ptr<ShoppingCart> cart,
    std::shared_ptr<PaymentSystem> payment,
    const std::string& details) {
    std::cout << "\n=== КОНТРОЛЛЕР ДОСТУПА: ВЫХОД ===\n";

    double price = cart->calculateFinalPrice(cust);
    if (!payment->processPayment(price, details)) {
        std::cout << "Оплата не прошла — выход ЗАПРЕЩЁН (Proxy)\n";
        return false;
    }

    double expectedWeight = cart->calculateTotalWeight();
    scales->setExpectedWeight(expectedWeight);
    if (!scales->verifyWeight()) {
        std::cout << "Вес не совпадает — выход ЗАПРЕЩЁН (Proxy)\n";
        return false;
    }

    exitTurnstile->unlockForExit();
    std::cout << payment->generateReceipt(rand() % 10000) << "\n";
    return true;
}