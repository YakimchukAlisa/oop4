#pragma once
#include <memory>
#include "IExitDevice.h"  // ← добавить
#include "PaymentSystem.h"
#include "CheckoutScale.h"
#include "ShoppingCart.h"
#include "Customer.h"

class AccessController : public IExitDevice { 
private:
    std::shared_ptr<IExitDevice> realExitDevice;  
    std::shared_ptr<CheckoutScale> scales;

    std::shared_ptr<Customer> currentCustomer;
    std::shared_ptr<ShoppingCart> currentCart;
    std::shared_ptr<PaymentSystem> currentPayment;
    std::string currentPaymentDetails;

    bool checkPayment();
    bool checkWeight();

public:
    AccessController(std::shared_ptr<IExitDevice> realExitDevice,
        std::shared_ptr<CheckoutScale> scale,
        std::shared_ptr<Customer> customer,
        std::shared_ptr<ShoppingCart> cart,
        std::shared_ptr<PaymentSystem> payment,
        const std::string& details);

    // Методы из IExitDevice
    void open() override;      
    void close() override;
    bool isOpen() const override;
    std::string getType() const override;
};