#include "Turnstile.h"

Turnstile::Turnstile(int id, const std::string& loc) : id(id), location(loc), locked(true) {}

void Turnstile::unlockForEntry() {
    std::cout << "“урникет " << id << " (" << location << "): открыт дл€ входа\n";
    locked = false;
    lock();
}

void Turnstile::unlockForExit() {
    std::cout << "“урникет " << id << " (" << location << "): открыт дл€ выхода\n";
    locked = false;
    lock();
}

void Turnstile::lock() {
    std::cout << "“урникет заблокирован\n";
    locked = true;
}

void Turnstile::displayInfo() const {
    std::cout << "“урникет " << id << " (" << location << ") Ч " << (locked ? "закрыт" : "открыт") << "\n";
}