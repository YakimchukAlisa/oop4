#pragma once
#include <string>
#include <map>
#include <memory>
#include <vector>

// Класс для конфигурирования системы
class Configurator {
private:
    std::map<std::string, std::string> settings;
    std::map<std::string, bool> equipmentPresence;
    
public:
    Configurator();
    
    // Загрузка конфигурации
    void loadConfiguration(const std::string& filename);
    void displayConfiguration() const;
    
    // Геттеры для конфигурации
    bool hasEquipment(const std::string& equipment) const;
    std::string getSetting(const std::string& key) const;
    
    // Параметры конкретных подсистем
    double getWeightTolerance() const; // допустимая погрешность веса
    int getMotionTimeout() const; // таймаут датчика движения
    std::string getActivePaymentProvider() const; // активный платежный провайдер
    std::vector<std::string> getActiveCameras() const; // список активных камер
};