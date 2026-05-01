#include "Turnstile.h"
#include <iostream>

Turnstile::Turnstile(int id, const std::string& loc)
    : id(id), location(loc), locked(true) {}

void Turnstile::open() {
    if (locked) {
        std::cout << "Òóðíèêåò " << id << " (" << location << "): ÐÀÇÁËÎÊÈÐÎÂÀÍ\n";
        locked = false;
    }
    else {
        std::cout << "Òóðíèêåò " << id << " (" << location << "): óæå îòêðûò\n";
    }
}

void Turnstile::close() {
    if (!locked) {
        std::cout << "Òóðíèêåò " << id << " (" << location << "): ÇÀÁËÎÊÈÐÎÂÀÍ\n";
        locked = true;
    }
}

bool Turnstile::isOpen() const {
    return !locked;
}

std::string Turnstile::getType() const {
    return "Òóðíèêåò";
}

void Turnstile::unlockForEntry() {
    std::cout << "Òóðíèêåò " << id << " (" << location << "): îòêðûò äëÿ ÂÕÎÄÀ\n";
    locked = false;
    close();  // ñðàçó çàêðûâàåì ïîñëå ïðîõîäà
}

void Turnstile::displayInfo() const {
    std::cout << "Òóðíèêåò " << id << " (" << location << ") — "
        << (locked ? "ÇÀÊÐÛÒ" : "ÎÒÊÐÛÒ") << "\n";
}