#include "AutoDoor.h"
#include <iostream>

AutoDoor::AutoDoor(int id, const std::string& loc, int sensorId)
    : id(id), location(loc), opened(false), sensorId(sensorId) {}

void AutoDoor::open() {
    if (!opened) {
        std::cout << "Автоматическая дверь " << id << " (" << location << "): ";
        if (sensorId != 0) {
            std::cout << "датчик " << sensorId << " обнаружил движение  ";
        }
        std::cout << "ДВЕРИ ОТКРЫВАЮТСЯ\n";
        opened = true;
    }
    else {
        std::cout << "Автоматическая дверь " << id << " (" << location << "): уже открыта\n";
    }
}

void AutoDoor::close() {
    if (opened) {
        std::cout << "Автоматическая дверь " << id << " (" << location << "): ДВЕРИ ЗАКРЫВАЮТСЯ\n";
        opened = false;
    }
}

bool AutoDoor::isOpen() const {
    return opened;
}

std::string AutoDoor::getType() const {
    return "Автоматическая дверь";
}

void AutoDoor::displayInfo() const {
    std::cout << "Автоматическая дверь " << id << " (" << location << ") — "
        << (opened ? "ОТКРЫТА" : "ЗАКРЫТА");
    if (sensorId != 0) {
        std::cout << ", датчик: " << sensorId;
    }
    std::cout << "\n";
}