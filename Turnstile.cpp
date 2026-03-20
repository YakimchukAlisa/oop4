#include "Turnstile.h"
#include <thread>
#include <chrono>

Turnstile::Turnstile(int id, const std::string& loc)
    : turnstileId(id), location(loc), isLocked(true), entriesCount(0), exitsCount(0) {}

void Turnstile::unlockForEntry() {
    std::cout << "\n=== ТУРНИКЕТ " << turnstileId << " (" << location << ") ===" << std::endl;
    if (isLocked) {
        std::cout << "Открытие турникета для ВХОДА" << std::endl;
        isLocked = false;
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        std::cout << "Покупатель проходит..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        entriesCount++;
        lock();
    }
    else {
        std::cout << "Турникет уже открыт" << std::endl;
    }
}

void Turnstile::unlockForExit() {
    std::cout << "\n=== ТУРНИКЕТ " << turnstileId << " (" << location << ") ===" << std::endl;
    if (isLocked) {
        std::cout << "Открытие турникета для ВЫХОДА (после оплаты)" << std::endl;
        isLocked = false;
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        std::cout << "Покупатель выходит..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        exitsCount++;
        lock();
    }
    else {
        std::cout << "Турникет уже открыт" << std::endl;
    }
}

void Turnstile::lock() {
    std::cout << "Турникет заблокирован" << std::endl;
    isLocked = true;
}

void Turnstile::displayInfo() const {
    std::cout << "Турникет ID: " << turnstileId << ", Расположение: " << location
        << ", Статус: " << (isLocked ? "Закрыт" : "Открыт")
        << ", Проходов: вход " << entriesCount << ", выход " << exitsCount << std::endl;
}