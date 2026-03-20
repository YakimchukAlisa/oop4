#include <iostream>
#include <memory>
#include "Configurator.h"
#include "ShopSimulation.h"

int main() {
    setlocale(LC_ALL, "Russian");

    std::cout << "=== Система автоматизации магазина самообслуживания ===\n\n";

    // Конфигурирование системы
    Configurator config;
    config.loadConfiguration("shop_config.ini");
    config.displayConfiguration();

    // Запуск симуляции работы магазина
    ShopSimulation shop;
    shop.initialize(config);
    shop.runSimulation();

    return 0;
}