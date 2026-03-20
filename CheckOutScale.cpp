#include "CheckoutScale.h"
#include <iostream>
#include <cmath>
#include <thread>
#include <chrono>
#include <cstdlib>

// Реализация CheckoutScale
CheckoutScale::CheckoutScale(int id, const std::string& loc, double prec)
    : scaleId(id), location(loc), currentWeight(0), precision(prec), expectedWeight(0) {}

void CheckoutScale::displayInfo() const {
    std::cout << "Весы ID: " << scaleId << ", Расположение: " << location
        << ", Точность: " << precision << " г" << std::endl;
}

void CheckoutScale::setExpectedWeight(double weight) {
    expectedWeight = weight;
    std::cout << "Весы " << scaleId << ": установлен ожидаемый вес " << expectedWeight << " г" << std::endl;
}

// Реализация HighPrecisionScale
HighPrecisionScale::HighPrecisionScale(int id, const std::string& loc)
    : CheckoutScale(id, loc, 0.1) {}

double HighPrecisionScale::weighProducts() {
    std::cout << "\nВысокоточные весы " << scaleId << ": взвешивание..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    // Генерируем случайное число от 0 до 99
    int random = rand() % 100;

    // С вероятностью 95% возвращаем правильный вес
    if (random < 95) {
        currentWeight = expectedWeight;
        std::cout << "  -> Вес: " << currentWeight << " г (верно)" << std::endl;
    }
    else {
        // Ошибка - случайный вес с отклонением до 250 г в обе стороны
        double deviation = (rand() % 500) - 250; // от -250 до +250
        currentWeight = expectedWeight + deviation;
        if (currentWeight < 0) currentWeight = 0;
        std::cout << "  -> Вес: " << currentWeight << " г (ОШИБКА! Отклонение: "
            << (deviation > 0 ? "+" : "") << deviation << " г)" << std::endl;
    }

    return currentWeight;
}

bool HighPrecisionScale::verifyWeight(double expectedWeightParam) {
    // Используем установленный ожидаемый вес, если параметр не передан
    double expected = (expectedWeightParam > 0) ? expectedWeightParam : expectedWeight;

    std::cout << "\nВысокоточные весы " << scaleId << ": проверка веса" << std::endl;
    std::cout << "  Ожидаемый вес: " << expected << " г" << std::endl;

    double actualWeight = weighProducts();
    double difference = std::abs(actualWeight - expected);

    std::cout << "  Погрешность: " << difference << " г (допустимо: " << precision << " г)" << std::endl;

    if (difference <= precision) {
        std::cout << "  ВЕС ПОДТВЕРЖДЕН" << std::endl;
        return true;
    }
    else {
        std::cout << "  РАСХОЖДЕНИЕ ВЕСА! Требуется верификация" << std::endl;
        return false;
    }
}

void HighPrecisionScale::calibrateWithReference(double referenceWeight) {
    std::cout << "Калибровка высокоточных весов эталонным грузом "
        << referenceWeight << " г..." << std::endl;
    currentWeight = referenceWeight;
    std::cout << "Калибровка завершена" << std::endl;
}

void HighPrecisionScale::displayInfo() const {
    CheckoutScale::displayInfo();
    std::cout << "  Тип: Высокоточные весы" << std::endl;
}