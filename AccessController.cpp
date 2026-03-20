#include "AccessController.h"
#include <iostream>
#include <thread>

AccessController::AccessController(std::shared_ptr<Turnstile> entry,
    std::shared_ptr<Turnstile> exit,
    std::shared_ptr<CheckoutScale> checkoutScales)
    : entryTurnstile(entry), exitTurnstile(exit), scales(checkoutScales) {}

bool AccessController::requestEntry(std::shared_ptr<Customer> customer, const std::string& credentials) {
    std::cout << "\n=== КОНТРОЛЛЕР ДОСТУПА: ЗАПРОС НА ВХОД ===" << std::endl;

    // Делегирование: передаем аутентификацию объекту Customer
    std::cout << "Контроллер доступа: делегирую аутентификацию объекту Customer" << std::endl;
    bool authenticated = customer->authenticate(credentials);

    if (authenticated) {
        std::cout << "Аутентификация успешна. Открываю турникет..." << std::endl;
        entryTurnstile->unlockForEntry();
        return true;
    }
    else {
        std::cout << "ОШИБКА АУТЕНТИФИКАЦИИ! Доступ запрещен." << std::endl;
        return false;
    }
}

bool AccessController::requestExit(std::shared_ptr<Customer> customer,
    std::shared_ptr<ShoppingCart> cart,
    std::shared_ptr<PaymentSystem> paymentMethod,
    const std::string& paymentDetails) {
    std::cout << "\n=== КОНТРОЛЛЕР ДОСТУПА: ЗАПРОС НА ВЫХОД ===" << std::endl;

    // 1. Получаем финальную цену (с учетом делегирования скидки корзиной)
    double finalPrice = cart->calculateFinalPrice(customer);

    // 2. Делегирование оплаты платежной системе (Proxy)
    std::cout << "\nКонтроллер доступа: делегирую обработку платежа объекту PaymentSystem" << std::endl;
    bool paymentSuccess = paymentMethod->processPayment(finalPrice, paymentDetails);

    if (!paymentSuccess) {
        std::cout << "ОШИБКА ОПЛАТЫ! Выход заблокирован." << std::endl;
        return false;
    }

    // 3. Проверка веса через весы (делегирование)
    std::cout << "\nКонтроллер доступа: делегирую проверку веса объекту CheckoutScale" << std::endl;
    // 3. Устанавливаем ожидаемый вес в весы (обязательно!)
    double expectedWeight = cart->calculateTotalWeight();
    scales->setExpectedWeight(expectedWeight);  // ← ЭТО ВАЖНО!

    // 4. Проверка веса
    bool weightVerified = scales->verifyWeight();  // Без параметра

    if (!weightVerified) {
        std::cout << "РАСХОЖДЕНИЕ ВЕСА! Запуск процедуры верификации." << std::endl;
        // Здесь можно делегировать дополнительную проверку камерам
        return false;
    }

    // 4. Все проверки пройдены - открываем выход
    std::cout << "\nВСЕ ПРОВЕРКИ ПРОЙДЕНЫ. Открываю выходной турникет..." << std::endl;
    exitTurnstile->unlockForExit();

    // 5. Генерируем чек
    std::string receipt = paymentMethod->generateReceipt(rand() % 10000);
    std::cout << "\n" << receipt << std::endl;

    return true;
}

void AccessController::emergencyUnlockAll() {
    std::cout << "\n!!! АВАРИЙНАЯ СИТУАЦИЯ !!!" << std::endl;
    std::cout << "Контроллер доступа: экстренная разблокировка всех дверей" << std::endl;
    entryTurnstile->unlockForEntry();
    exitTurnstile->unlockForExit();
}

void AccessController::displayInfo() const {
    std::cout << "\n=== КОНТРОЛЛЕР ДОСТУПА ===" << std::endl;
    entryTurnstile->displayInfo();
    exitTurnstile->displayInfo();
    scales->displayInfo();
}