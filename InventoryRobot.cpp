#include "InventoryRobot.h"
#include <iostream>
#include <thread>
#include <chrono>

// Реализация InventoryRobot
InventoryRobot::InventoryRobot(int id, const std::string& model)
    : robotId(id), modelName(model), isActive(false), batteryLevel(100) {}

void InventoryRobot::displayInfo() const {
    std::cout << "Робот ID: " << robotId << ", Модель: " << modelName
        << ", Заряд батареи: " << batteryLevel << "%, Статус: "
        << (isActive ? "Активен" : "В режиме ожидания") << std::endl;
}

// Реализация AutonomousNavigationRobot
AutonomousNavigationRobot::AutonomousNavigationRobot(int id)
    : InventoryRobot(id, "AutoNav-X200"), currentPosition("Зарядная станция") {}

void AutonomousNavigationRobot::scanShelf(std::shared_ptr<SmartShelf> shelf) {
    isActive = true;
    std::cout << "\n=== АВТОНОМНЫЙ РОБОТ " << robotId << " ===" << std::endl;
    std::cout << "Сканирование полки " << shelf->getShelfId()
        << " в локации " << shelf->getLocation() << std::endl;

    navigateTo(shelf->getLocation());

    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << "Сканирование завершено. Проверка соответствия..." << std::endl;

    batteryLevel -= 5;
    isActive = false;
}

void AutonomousNavigationRobot::navigateTo(const std::string& shelfLocation) {
    std::cout << "Построение маршрута к " << shelfLocation << "..." << std::endl;
    updateMap();
    std::cout << "Перемещение..." << std::endl;
    currentPosition = shelfLocation;
    std::cout << "Робот прибыл на позицию: " << currentPosition << std::endl;
}

void AutonomousNavigationRobot::avoidObstacle() {
    std::cout << "Обнаружено препятствие! Объезд..." << std::endl;
}

void AutonomousNavigationRobot::updateMap() {
    std::cout << "Обновление карты магазина..." << std::endl;
    mapData = "MAP_v" + std::to_string(rand() % 100);
}

void AutonomousNavigationRobot::reportDiscrepancy(const std::string& productId,
    int expectedCount, int actualCount) {
    std::cout << "\n!!! РАСХОЖДЕНИЕ ОБНАРУЖЕНО !!!" << std::endl;
    std::cout << "Товар ID: " << productId << std::endl;
    std::cout << "Ожидаемое количество: " << expectedCount << std::endl;
    std::cout << "Фактическое количество: " << actualCount << std::endl;
    std::cout << "Отправка отчета в систему учета..." << std::endl;
}

void AutonomousNavigationRobot::displayInfo() const {
    InventoryRobot::displayInfo();
    std::cout << "  Тип: Автономный робот, Текущая позиция: " << currentPosition << std::endl;
}

// Реализация RailGuidedRobot
RailGuidedRobot::RailGuidedRobot(int id, const std::string& rail)
    : InventoryRobot(id, "RailBot-100"), railId(rail), railPosition(0) {}

void RailGuidedRobot::scanShelf(std::shared_ptr<SmartShelf> shelf) {
    isActive = true;
    std::cout << "\n=== РЕЛЬСОВЫЙ РОБОТ " << robotId << " ===" << std::endl;
    std::cout << "Сканирование полки " << shelf->getShelfId() << std::endl;

    moveAlongRail("FORWARD");

    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    std::cout << "Сканирование завершено" << std::endl;

    batteryLevel -= 2;
    isActive = false;
}

void RailGuidedRobot::moveAlongRail(const std::string& direction) {
    if (direction == "FORWARD") {
        railPosition += 10;
        std::cout << "Движение вперед по рельсам. Текущая позиция: " << railPosition << std::endl;
    }
    else if (direction == "BACKWARD") {
        railPosition -= 10;
        std::cout << "Движение назад по рельсам. Текущая позиция: " << railPosition << std::endl;
    }
}

void RailGuidedRobot::reportDiscrepancy(const std::string& productId,
    int expectedCount, int actualCount) {
    std::cout << "\nРельсовый робот: обнаружено расхождение по товару " << productId << std::endl;
}

void RailGuidedRobot::displayInfo() const {
    InventoryRobot::displayInfo();
    std::cout << "  Тип: Рельсовый робот, Рельс: " << railId
        << ", Позиция: " << railPosition << std::endl;
}

// Реализация DroneInventoryRobot
DroneInventoryRobot::DroneInventoryRobot(int id)
    : InventoryRobot(id, "DroneScan-500"), altitude(0), isFlying(false) {}

void DroneInventoryRobot::takeoff() {
    std::cout << "\nДрон " << robotId << ": взлет..." << std::endl;
    isFlying = true;
    altitude = 50;
    std::cout << "Дрон на высоте " << altitude << " см" << std::endl;
}

void DroneInventoryRobot::land() {
    std::cout << "Дрон " << robotId << ": посадка..." << std::endl;
    isFlying = false;
    altitude = 0;
    std::cout << "Дрон приземлился" << std::endl;
}

void DroneInventoryRobot::flyToHeight(int height) {
    if (isFlying) {
        std::cout << "Дрон: изменение высоты с " << altitude << " см на " << height << " см" << std::endl;
        altitude = height;
    }
}

void DroneInventoryRobot::scanShelf(std::shared_ptr<SmartShelf> shelf) {
    std::cout << "\n=== ДРОН-ИНВЕНТАРИЗАТОР " << robotId << " ===" << std::endl;

    if (!isFlying) {
        takeoff();
    }

    flyToHeight(200); // поднимаемся для обзора верхних полок
    std::cout << "Сканирование верхней полки " << shelf->getShelfId() << " с высоты..." << std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(400));
    std::cout << "Фотосъемка полки завершена" << std::endl;

    batteryLevel -= 8;
    land();
}

void DroneInventoryRobot::reportDiscrepancy(const std::string& productId,
    int expectedCount, int actualCount) {
    std::cout << "\nДрон: зафиксировано несоответствие на верхней полке!" << std::endl;
    std::cout << "Товар " << productId << ": ожидалось " << expectedCount
        << ", обнаружено " << actualCount << std::endl;
}

void DroneInventoryRobot::displayInfo() const {
    InventoryRobot::displayInfo();
    std::cout << "  Тип: Дрон-инвентаризатор, Высота: " << altitude
        << " см, В полете: " << (isFlying ? "да" : "нет") << std::endl;
}