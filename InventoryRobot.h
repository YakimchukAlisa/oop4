#pragma once
#include <string>
#include <memory>
#include "SmartShelf.h"
#include "InventorySystem.h"

// Абстрактный базовый класс InventoryRobot
class InventoryRobot {
protected:
    int robotId;
    std::string modelName;
    bool isActive;
    double batteryLevel;

public:
    InventoryRobot(int id, const std::string& model);
    virtual ~InventoryRobot() = default;

    virtual void scanShelf(std::shared_ptr<SmartShelf> shelf) = 0;
    virtual void reportDiscrepancy(const std::string& productId,
        int expectedCount, int actualCount) = 0;

    void charge() { batteryLevel = 100; }
    double getBatteryLevel() const { return batteryLevel; }
    virtual void displayInfo() const;
};

// Автономный робот со свободным перемещением
class AutonomousNavigationRobot : public InventoryRobot {
private:
    std::string currentPosition;
    std::string mapData;

public:
    AutonomousNavigationRobot(int id);

    void scanShelf(std::shared_ptr<SmartShelf> shelf) override;
    void reportDiscrepancy(const std::string& productId, int expectedCount, int actualCount) override;
    void navigateTo(const std::string& shelfLocation);
    void avoidObstacle();
    void updateMap();
    void displayInfo() const override;
};

// Робот, движущийся по рельсам
class RailGuidedRobot : public InventoryRobot {
private:
    int railPosition; // позиция на рельсах
    std::string railId;

public:
    RailGuidedRobot(int id, const std::string& rail);

    void scanShelf(std::shared_ptr<SmartShelf> shelf) override;
    void reportDiscrepancy(const std::string& productId, int expectedCount, int actualCount) override;
    void moveAlongRail(const std::string& direction);
    int getRailPosition() const { return railPosition; }
    void displayInfo() const override;
};

// Робот-дрон
class DroneInventoryRobot : public InventoryRobot {
private:
    int altitude; // высота в см
    bool isFlying;

public:
    DroneInventoryRobot(int id);

    void scanShelf(std::shared_ptr<SmartShelf> shelf) override;
    void reportDiscrepancy(const std::string& productId, int expectedCount, int actualCount) override;
    void takeoff();
    void land();
    void flyToHeight(int height);
    void displayInfo() const override;
};