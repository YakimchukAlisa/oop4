#include "Configurator.h"
#include "ShopSimulation.h"

int main() {
    setlocale(LC_ALL, "Russian");

    std::cout << "=== Система автоматизации магазина ===\n";

    Configurator config;
    config.loadConfiguration("shop_config.ini");
    config.displayConfiguration();

    ShopSimulation shop;
    shop.initialize(config);
    shop.runSimulation();

    return 0;
}