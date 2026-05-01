#include "AccessController.h"
#include <iostream>

AccessController::AccessController(std::shared_ptr<IExitDevice> realExitDevice,
    std::shared_ptr<CheckoutScale> scale,
    std::shared_ptr<Customer> customer,
    std::shared_ptr<ShoppingCart> cart,
    std::shared_ptr<PaymentSystem> payment,
    const std::string& details)
    : realExitDevice(realExitDevice), scales(scale),
    currentCustomer(customer), currentCart(cart),
    currentPayment(payment), currentPaymentDetails(details) {}

bool AccessController::checkPayment() {
    double price = currentCart->calculateTotal();
    std::cout << "Сумма к оплате: " << price << " руб.\n";

    if (!currentPayment->processPayment(price, currentPaymentDetails)) {
        std::cout << "[ERROR] ОПЛАТА НЕ ПРОШЛА! Выход ЗАПРЕЩЁН\n";
        return false;
    }
    return true;
}

bool AccessController::checkWeight() {
    double expectedWeight = currentCart->calculateTotalWeight();
    scales->setExpectedWeight(expectedWeight);
    if (!scales->verifyWeight(expectedWeight)) {
        std::cout << "[ERROR] ВЕС НЕ СОВПАДАЕТ! Выход ЗАПРЕЩЁН\n";
        return false;
    }
    return true;
}

void AccessController::open() {
    std::cout << "\n=== AccessController (PROXY) ===\n";
    std::cout << "Реальное устройство выхода: " << realExitDevice->getType() << "\n\n";

    if (checkPayment() && checkWeight()) {
        std::cout << "[OK] ВСЕ ПРОВЕРКИ ПРОЙДЕНЫ\n";
        realExitDevice->open();  // делегируем реальному устройству
        std::cout << "Покупатель успешно вышел\n";
        realExitDevice->close();
    }
    else {
        std::cout << "Выход ЗАПРЕЩЁН! Проверки не пройдены.\n";
    }
}

void AccessController::close() {
    // Прокси ничего не делает при закрытии, делегирует реальному
    realExitDevice->close();
}

bool AccessController::isOpen() const {
    return realExitDevice->isOpen();
}

std::string AccessController::getType() const {
    return "Прокси для " + realExitDevice->getType();
}