#include "ShoppingCart.h"
#include <iostream>
#include <iomanip>

ShoppingCart::ShoppingCart(int id, int custId)
    : cartId(id), customerId(custId), totalWeight(0), totalPrice(0) {}

void ShoppingCart::addItem(std::shared_ptr<Product> product) {
    items.push_back(product);
    totalWeight += product->getWeight();
    totalPrice += product->getPrice();

    std::cout << "Корзина " << cartId << ": добавлен товар \""
        << product->getName() << "\" (" << product->getPrice() << " руб.)" << std::endl;
}

void ShoppingCart::removeItem(const std::string& barcode) {
    for (auto it = items.begin(); it != items.end(); ++it) {
        if ((*it)->getBarcode() == barcode) {
            totalWeight -= (*it)->getWeight();
            totalPrice -= (*it)->getPrice();
            std::cout << "Корзина " << cartId << ": удален товар \""
                << (*it)->getName() << "\"" << std::endl;
            items.erase(it);
            return;
        }
    }
    std::cout << "Товар со штрих-кодом " << barcode << " не найден в корзине" << std::endl;
}

double ShoppingCart::calculateTotal() {
    totalPrice = 0;
    for (const auto& item : items) {
        totalPrice += item->getPrice();
    }
    return totalPrice;
}

double ShoppingCart::calculateTotalWeight() {
    totalWeight = 0;
    for (const auto& item : items) {
        totalWeight += item->getWeight();
    }
    return totalWeight;
}

// Делегирование - передаем расчет скидки объекту Customer
double ShoppingCart::calculateFinalPrice(std::shared_ptr<Customer> customer) {
    double baseTotal = calculateTotal();

    std::cout << "\n=== Делегирование: расчет цены со скидкой ===" << std::endl;
    std::cout << "Корзина делегирует расчет скидки объекту Customer" << std::endl;

    // Пытаемся привести к LoyaltyCustomer (dynamic_cast - это форма RTTI)
    std::shared_ptr<LoyaltyCustomer> loyaltyCust =
        std::dynamic_pointer_cast<LoyaltyCustomer>(customer);

    if (loyaltyCust) {
        // Делегируем расчет скидки покупателю
        double finalPrice = loyaltyCust->applyDiscount(baseTotal);
        std::cout << "Корзина: делегировала расчет скидки постоянному покупателю" << std::endl;
        std::cout << "Базовая сумма: " << baseTotal << " руб., "
            << "со скидкой: " << finalPrice << " руб." << std::endl;
        return finalPrice;
    }
    else {
        std::cout << "Корзина: скидка не применяется (не постоянный покупатель)" << std::endl;
        return baseTotal;
    }
}

void ShoppingCart::displayCart() const {
    std::cout << "\n=== Корзина ID: " << cartId << " (Покупатель ID: " << customerId << ") ===" << std::endl;
    if (items.empty()) {
        std::cout << "Корзина пуста" << std::endl;
        return;
    }

    std::cout << std::left << std::setw(30) << "Товар"
        << std::setw(10) << "Цена"
        << std::setw(10) << "Вес(г)" << std::endl;
    std::cout << std::string(50, '-') << std::endl;

    for (const auto& item : items) {
        std::cout << std::left << std::setw(30) << item->getName()
            << std::right << std::setw(8) << item->getPrice() << " руб."
            << std::setw(8) << item->getWeight() << " г" << std::endl;
    }

    std::cout << std::string(50, '-') << std::endl;
    std::cout << "Итого: " << totalPrice << " руб.  Вес: " << totalWeight << " г" << std::endl;
}

void ShoppingCart::clear() {
    items.clear();
    totalWeight = 0;
    totalPrice = 0;
    std::cout << "Корзина " << cartId << " очищена" << std::endl;
}