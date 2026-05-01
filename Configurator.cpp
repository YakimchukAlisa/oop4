#include "Configurator.h"
#include <iostream>
#include <fstream>
#include <sstream>

void Configurator::loadConfiguration(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Конфиг не найден, используются значения по умолчанию\n";
        settings["shop_name"] = "Магазин-автомат";
        return;
    }
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == ';') continue;
        std::istringstream iss(line);
        std::string key, val;
        if (std::getline(iss, key, '=') && std::getline(iss, val))
            settings[key] = val;
    }
    std::cout << "Конфигурация загружена\n";
}

void Configurator::displayConfiguration() const {
    std::cout << "\n=== КОНФИГУРАЦИЯ ===\n";
    for (auto it = settings.begin(); it != settings.end(); ++it) {
        std::cout << it->first << " = " << it->second << "\n";
    }
}

std::string Configurator::getSetting(const std::string& key) const {
    auto it = settings.find(key);
    return it != settings.end() ? it->second : "";
}