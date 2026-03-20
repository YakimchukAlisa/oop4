#include "Configurator.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

Configurator::Configurator() {
 
}

void Configurator::loadConfiguration(const std::string& filename) {
    std::cout << "Загрузка конфигурации из файла: " << filename << std::endl;

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Файл конфигурации не найден. Используются настройки по умолчанию." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        // Пропускаем пустые строки и комментарии
        if (line.empty() || line[0] == ';' || line[0] == '#') continue;

        std::istringstream iss(line);
        std::string key, value;
        if (std::getline(iss, key, '=') && std::getline(iss, value)) {
            // Удаляем пробелы
            key.erase(0, key.find_first_not_of(" \t"));
            key.erase(key.find_last_not_of(" \t") + 1);
            value.erase(0, value.find_first_not_of(" \t"));
            value.erase(value.find_last_not_of(" \t") + 1);

            settings[key] = value;
        }
    }

    // Заполняем equipmentPresence из settings 
    for (const auto& pair : settings) {
        const std::string& key = pair.first;
        const std::string& value = pair.second;

        // Проверяем, относится ли ключ к оборудованию
        if (key.find("_shelves") != std::string::npos ||
            key.find("_cameras") != std::string::npos ||
            key.find("_scales") != std::string::npos ||
            key.find("_robot") != std::string::npos ||
            key.find("_sensors") != std::string::npos ||
            key.find("_recognition") != std::string::npos) {

            // Преобразуем строку в bool
            bool boolValue = (value == "true" || value == "1" || value == "yes");
            equipmentPresence[key] = boolValue;
            std::cout << "  Оборудование загружено: " << key << " = " << (boolValue ? "вкл" : "выкл") << std::endl;
        }
    }

    std::cout << "Конфигурация загружена успешно." << std::endl;
}
void Configurator::displayConfiguration() const {
    std::cout << "\n=== КОНФИГУРАЦИЯ СИСТЕМЫ ===" << std::endl;
    std::cout << "Магазин: " << settings.at("shop_name") << std::endl;
    std::cout << "\n--- Параметры ---" << std::endl;
    std::cout << "Допустимая погрешность веса: " << settings.at("weight_tolerance") << " г" << std::endl;
    std::cout << "Таймаут датчика движения: " << settings.at("motion_timeout") << " сек" << std::endl;
    std::cout << "Платежный провайдер: " << settings.at("payment_provider") << std::endl;
    std::cout << "Порог заказа товаров: " << settings.at("reorder_threshold") << " %" << std::endl;
    std::cout << "Энергосберегающий режим: " << settings.at("energy_saving_mode") << std::endl;

    std::cout << "\n--- Оборудование ---" << std::endl;
    for (const auto& eq : equipmentPresence) {
        std::cout << "  " << eq.first << ": " << (eq.second ? "есть" : "нет") << std::endl;
    }
}

bool Configurator::hasEquipment(const std::string& equipment) const {
    auto it = equipmentPresence.find(equipment);
    return (it != equipmentPresence.end()) && it->second;
}

std::string Configurator::getSetting(const std::string& key) const {
    auto it = settings.find(key);
    return (it != settings.end()) ? it->second : "";
}

double Configurator::getWeightTolerance() const {
    return std::stod(settings.at("weight_tolerance"));
}

int Configurator::getMotionTimeout() const {
    return std::stoi(settings.at("motion_timeout"));
}

std::string Configurator::getActivePaymentProvider() const {
    return settings.at("payment_provider");
}

std::vector<std::string> Configurator::getActiveCameras() const {
    std::vector<std::string> cameras;
    if (equipmentPresence.at("basic_cameras")) cameras.push_back("BasicCamera");
    if (equipmentPresence.at("face_recognition")) cameras.push_back("FaceRecognitionCamera");
    if (equipmentPresence.at("product_recognition")) cameras.push_back("ProductRecognitionCamera");
    return cameras;
}