#include "ShopSimulation.h"
#include <thread>
#include <chrono>

ShopSimulation::ShopSimulation() : nextCartId(1000), nextCustomerId(1) {}

void ShopSimulation::initialize(const Configurator& cfg) {
    config = std::make_shared<Configurator>(cfg);
    std::cout << "\n=== ИНИЦИАЛИЗАЦИЯ ===\n";
    createProducts();
    createCustomers();
    createEquipment();
    std::cout << "Магазин готов\n";
}

void ShopSimulation::createCustomers() {
    customers.push_back(std::make_shared<GuestCustomer>(nextCustomerId++, "Иван Петров"));
    customers.push_back(std::make_shared<LoyaltyCustomer>(nextCustomerId++, "Анна Смирнова", 0.1));
}

void ShopSimulation::createProducts() {
    // Обычные товары
    regularProducts.push_back(std::make_shared<RegularProduct>("Молоко", 85.0, 1000));
    regularProducts.push_back(std::make_shared<RegularProduct>("Хлеб", 45.0, 400));
    regularProducts.push_back(std::make_shared<RegularProduct>("Шоколад", 120.0, 90));

    // Развесные товары
    std::shared_ptr<WeightedProduct> candies = std::make_shared<WeightedProduct>("Конфеты", 400.0);
    weightedProducts.push_back(candies);

    std::cout << "\n--- Созданные товары ---\n";
    std::cout << "1. " << regularProducts[0]->getName() << " — " << regularProducts[0]->getPrice() << " руб.\n";
    std::cout << "2. " << regularProducts[1]->getName() << " — " << regularProducts[1]->getPrice() << " руб.\n";
    std::cout << "3. " << regularProducts[2]->getName() << " — " << regularProducts[2]->getPrice() << " руб.\n";
    std::cout << "4. Конфеты (развесной) — цена за кг: 400 руб.\n";
    std::cout << "   (вес выбирает покупатель при покупке)\n\n";
}

void ShopSimulation::createEquipment() {
    // Реальные турникеты
    std::shared_ptr<Turnstile> realEntry = std::make_shared<Turnstile>(301, "Вход");
    std::shared_ptr<Turnstile> realExit = std::make_shared<Turnstile>(302, "Выход");

    // Разные типы весов
    highPrecisionScale = std::make_shared<HighPrecisionScale>(401);
    postalScale = std::make_shared<PostalScale>(402);

    // По умолчанию используем высокоточные весы
    currentScale = postalScale;

    // Автоматические двери
    autoDoor = std::make_shared<AutoDoor>(501, "Центральный выход", 1001);

    // Для входа используем реальный турникет
    entryTurnstile = realEntry;

    // Для выхода по умолчанию — турникет
    defaultExit = autoDoor;
    altExit = autoDoor;

    std::cout << "\n--- Оборудование магазина ---\n";
    std::cout << "  Вход: Турникет #301\n";
    std::cout << "  Выход по умолчанию: Турникет #302\n";
    std::cout << "  Альтернативный выход: Автоматическая дверь #501\n";
    std::cout << "  Весы: Высокоточные (#401) и Почтовые (#402)\n\n";
}

std::shared_ptr<ShoppingCart> ShopSimulation::createCartForCustomer(int custId) {
    return std::make_shared<ShoppingCart>(nextCartId++, custId);
}

void ShopSimulation::runSimulation() {
    scenarioProxy();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    scenarioDelegation();
}

void ShopSimulation::scenarioProxy() {
    std::cout << "\n\n--- СЦЕНАРИЙ 1: ПАТТЕРН PROXY ---\n";

    std::shared_ptr<Customer> customer = customers[0];
    std::shared_ptr<ShoppingCart> cart = createCartForCustomer(customer->getId());

    entryTurnstile->unlockForEntry();

    // Добавляем обычные товары
    cart->addItem(regularProducts[0]);  // молоко
    cart->addItem(regularProducts[1]);  // хлеб

    // Добавляем развесные товары 
    std::shared_ptr<IWeightedProduct> candies = weightedProducts[0];
    candies->setWeight(300);  
    cart->addItem(candies);
    cart->displayCart();

    std::shared_ptr<BankCardPayment> payment = std::make_shared<BankCardPayment>("https://bank.ru/api", "MERCH");

    // Обычный выход через турникет с высокоточными весами
    std::cout << "\n--- Демонстрация 1: Выход через " << defaultExit->getType() << " -- - \n";
    std::shared_ptr<IExitDevice> exitProxy1 = std::make_shared<AccessController>(
        defaultExit, currentScale, customer, cart, payment, "4111111111111111"
    );
    exitProxy1->open();

    std::this_thread::sleep_for(std::chrono::seconds(1));

    // Выход через АВТОМАТИЧЕСКУЮ ДВЕРЬ 
    std::cout << "\n--- Демонстрация 2: Выход через " << altExit->getType() << " -- - \n";
    std::shared_ptr<IExitDevice> exitProxy2 = std::make_shared<AccessController>(
        autoDoor, currentScale, customer, cart, payment, "4111111111111111"
    );
    exitProxy2->open();

    std::this_thread::sleep_for(std::chrono::seconds(1));

    currentScale = postalScale;
    //Почтовые весы
    std::cout << "\n--- Демонстрация 3: " << currentScale->getType() << "\n";   
    std::shared_ptr<IExitDevice> exitProxy3 = std::make_shared<AccessController>(
        autoDoor, currentScale, customer, cart, payment, "4111111111111111"
    );
    exitProxy3->open();
}

    void ShopSimulation::scenarioDelegation() {
        std::cout << "\n\n--- СЦЕНАРИЙ 2: ПАТТЕРН ДЕЛЕГИРОВАНИЕ ---\n";
        std::cout << "Корзина ВСЕГДА делегирует расчет скидки объекту Customer\n\n";

        // ===== ПОСТОЯННЫЙ ПОКУПАТЕЛЬ =====
        std::cout << "1. Постоянный покупатель:\n";
        auto loyaltyCustomer = customers[1];
        auto cart1 = createCartForCustomer(loyaltyCustomer->getId());
        cart1->addItem(regularProducts[2]);

        double base1 = cart1->calculateTotal();
        double final1 = cart1->calculateFinalPrice(loyaltyCustomer);

        double discount1 = loyaltyCustomer->getDiscount(base1);

        std::cout << "   Базовая цена: " << base1 << " руб.\n";
        std::cout << "   Скидка:  "
            << discount1 << " руб.\n";
        std::cout << "   Итоговая цена: " << final1 << " руб.\n\n";

        // ===== ОБЫЧНЫЙ ПОКУПАТЕЛЬ =====
        std::cout << "2. Обычный покупатель (без скидки):\n";
        auto guestCustomer = customers[0];
        auto cart2 = createCartForCustomer(guestCustomer->getId());
        cart2->addItem(regularProducts[0]);
        cart2->addItem(regularProducts[1]);

        double base2 = cart2->calculateTotal();
        double final2 = cart2->calculateFinalPrice(guestCustomer);

        double discount2 = guestCustomer->getDiscount(base2);

        std::cout << "   Базовая цена: " << base2 << " руб.\n";
        std::cout << "   Скидка: "
            << discount2 << " руб.\n";
        std::cout << "   Итоговая цена: " << final2 << " руб.\n\n";
    }