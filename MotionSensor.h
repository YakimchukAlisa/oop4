#pragma once
#include <string>
#include <iostream>
#include <ctime>

// Класс датчика движения
class MotionSensor {
private:
    int sensorId;
    std::string zone; // зона магазина (вход, проход, молочная секция и т.д.)
    bool motionDetected;
    time_t lastMotionTime;

public:
    MotionSensor(int id, const std::string& zoneName);

    // Событие обнаружения движения
    bool detectMotion();

    // Получить время бездействия (в секундах)
    double getIdleTime() const;

    // Получить идентификатор зоны
    std::string getZoneId() const { return zone; }

    void displayInfo() const;

    // Сброс состояния
    void reset();
};