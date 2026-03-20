#pragma once
#include <vector>
#include <memory>
#include "Product.h"
#include "Customer.h"

class ShoppingCart {
    int cartId;
    int customerId;
    std::vector<std::shared_ptr<Product>> items;
    double totalPrice;
    double totalWeight;
public:
    ShoppingCart(int id, int custId);
    void addItem(std::shared_ptr<Product> product);
    double calculateTotal();
    double calculateTotalWeight();
    double calculateFinalPrice(std::shared_ptr<Customer> customer);
    void displayCart() const;
};