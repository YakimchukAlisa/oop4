#include "MotionSensor.h"
#include <thread>
#include <chrono>

MotionSensor::MotionSensor(int id, const std::string& zoneName)
    : sensorId(id), zone(zoneName), motionDetected(false) {
    lastMotionTime = std::time(nullptr);
}

bool MotionSensor::detectMotion() {
    // Имитация обнаружения движения (30% вероятность)
    motionDetected = (rand() % 100) < 30;

    if (motionDetected) {
        lastMotionTime = std::time(nullptr);
        std::cout << "Датчик движения " << sensorId << " (зона: " << zone
            << "): ДВИЖЕНИЕ ОБНАРУЖЕНО" << std::endl;
    }
    else {
        std::cout << "Датчик движения " << sensorId << " (зона: " << zone
            << "): движение отсутствует" << std::endl;
    }

    return motionDetected;
}

double MotionSensor::getIdleTime() const {
    time_t currentTime = std::time(nullptr);
    return std::difftime(currentTime, lastMotionTime);
}

void MotionSensor::displayInfo() const {
    std::cout << "Датчик движения ID: " << sensorId << ", Зона: " << zone
        << ", Последнее движение: " << getIdleTime() << " сек назад" << std::endl;
}

void MotionSensor::reset() {
    motionDetected = false;
    lastMotionTime = std::time(nullptr);
    std::cout << "Датчик движения " << sensorId << " сброшен" << std::endl;
}