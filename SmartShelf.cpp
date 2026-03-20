#include "SmartShelf.h"
#include <iostream>

// Реализация SmartShelf
SmartShelf::SmartShelf(int id, const std::string& loc, double initialWeight)
    : shelfId(id), location(loc), currentWeight(initialWeight) {}

void SmartShelf::addProduct(std::shared_ptr<Product> product) {
    products[product->getBarcode()] = product;
    currentWeight += product->getWeight();
    std::cout << "Товар \"" << product->getName() << "\" добавлен на полку " << shelfId << std::endl;
}

void SmartShelf::displayInfo() const {
    std::cout << "Полка ID: " << shelfId << ", Расположение: " << location
        << ", Текущий вес: " << currentWeight << " г"
        << ", Товаров: " << products.size() << std::endl;
}

// Реализация WeightBasedShelf
WeightBasedShelf::WeightBasedShelf(int id, const std::string& loc, double tare, double weightPerUnit)
    : SmartShelf(id, loc, tare), tareWeight(tare), isCalibrated(false), weightPerUnit(weightPerUnit) {}

void WeightBasedShelf::onWeightChanged(double newWeight) {
    double oldWeight = currentWeight;
    currentWeight = newWeight;
    double delta = oldWeight - newWeight;

    std::cout << "Полка " << shelfId << ": изменение веса на " << delta << " г" << std::endl;

    if (std::abs(delta) > 5) { // игнорируем мелкие погрешности
        if (delta > 0) {
            std::cout << "  -> Товар ВЗЯТ с полки. Вес уменьшился на " << delta << " г" << std::endl;
        }
        else {
            std::cout << "  -> Товар ВОЗВРАЩЕН на полку. Вес увеличился на " << -delta << " г" << std::endl;
        }
    }
}

void WeightBasedShelf::calibrateSensors() {
    std::cout << "Калибровка тензодатчиков полки " << shelfId << "..." << std::endl;
    isCalibrated = true;
    std::cout << "Калибровка завершена" << std::endl;
}

std::shared_ptr<Product> WeightBasedShelf::detectProductTaken(double weightDelta) {
    for (auto& pair : products) {
        if (std::abs(pair.second->getWeight() - weightDelta) < 10) {
            std::cout << "Идентифицирован товар: " << pair.second->getName() << std::endl;
            return pair.second;
        }
    }
    return nullptr;
}

void WeightBasedShelf::displayInfo() const {
    SmartShelf::displayInfo();
    std::cout << "  Тип: Тензодатчики, Тарировка: " << tareWeight
        << " г, Калибровка: " << (isCalibrated ? "да" : "нет") << std::endl;
}

// Реализация RFIDBasedShelf
RFIDBasedShelf::RFIDBasedShelf(int id, const std::string& loc, double initialWeight)
    : SmartShelf(id, loc, initialWeight) {}

void RFIDBasedShelf::onWeightChanged(double newWeight) {
    // RFID-полка не использует вес как основной метод, но может его отслеживать
    currentWeight = newWeight;
    std::cout << "RFID-полка " << shelfId << ": вес изменен на " << newWeight << " г" << std::endl;
}

std::vector<std::string> RFIDBasedShelf::scanRFIDTags() {
    std::cout << "Сканирование RFID-меток на полке " << shelfId << "..." << std::endl;
    // Имитация сканирования
    std::vector<std::string> tags = { "RFID001", "RFID002", "RFID003" };
    currentTags = tags;
    std::cout << "Обнаружено " << tags.size() << " меток" << std::endl;
    return tags;
}

void RFIDBasedShelf::addProductWithTag(std::shared_ptr<Product> product, const std::string& tag) {
    addProduct(product);
    currentTags.push_back(tag);
    std::cout << "Товар привязан к RFID-метке " << tag << std::endl;
}

void RFIDBasedShelf::displayInfo() const {
    SmartShelf::displayInfo();
    std::cout << "  Тип: RFID, Меток на полке: " << currentTags.size() << std::endl;
}