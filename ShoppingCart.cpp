#include "ShoppingCart.h"
#include <iostream>
#include <iomanip>

ShoppingCart::ShoppingCart(int id, int custId)
    : cartId(id), customerId(custId), totalPrice(0), totalWeight(0) {}

void ShoppingCart::addItem(std::shared_ptr<Product> product) {
    items.push_back(product);
    totalPrice += product->getPrice();
    totalWeight += product->getWeight();
    std::cout << "Корзина: добавлен " << product->getName() << " (" << product->getPrice() << " руб.)\n";
}

double ShoppingCart::calculateTotal() {
    totalPrice = 0;
    for (auto& p : items) totalPrice += p->getPrice();
    return totalPrice;
}

double ShoppingCart::calculateTotalWeight() {
    totalWeight = 0;
    for (auto& p : items) totalWeight += p->getWeight();
    return totalWeight;
}

double ShoppingCart::calculateFinalPrice(std::shared_ptr<Customer> customer) {
    double base = calculateTotal();
    auto loyalty = std::dynamic_pointer_cast<LoyaltyCustomer>(customer);
    if (loyalty) {
        std::cout << "Корзина: делегирую расчёт скидки покупателю\n";
        return loyalty->applyDiscount(base);
    }
    return base;
}

void ShoppingCart::displayCart() const {
    std::cout << "\n=== Корзина ID " << cartId << " ===\n";
    for (auto& p : items)
        std::cout << "  " << p->getName() << " — " << p->getPrice() << " руб., " << p->getWeight() << " г\n";
    std::cout << "Итого: " << totalPrice << " руб., вес: " << totalWeight << " г\n";
}