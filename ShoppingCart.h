#pragma once
#include <vector>
#include <memory>
#include "Product.h"
#include "Customer.h"

// Класс виртуальной корзины (применяет делегирование для скидок)
class ShoppingCart {
private:
    int cartId;
    int customerId;
    std::vector<std::shared_ptr<Product>> items;
    double totalWeight;
    double totalPrice;

public:
    ShoppingCart(int id, int custId);

    // Основные методы работы с корзиной
    void addItem(std::shared_ptr<Product> product);
    void removeItem(const std::string& barcode);
    double calculateTotal();
    double calculateTotalWeight();

    // Делегирование - передаем расчет скидки объекту Customer
    double calculateFinalPrice(std::shared_ptr<Customer> customer);

    // Геттеры
    int getCartId() const { return cartId; }
    int getCustomerId() const { return customerId; }
    const std::vector<std::shared_ptr<Product>>& getItems() const { return items; }
    int getItemCount() const { return items.size(); }
    double getTotalPrice() const { return totalPrice; }
    double getTotalWeight() const { return totalWeight; }

    void displayCart() const;
    void clear();
};