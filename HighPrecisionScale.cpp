#include "HighPrecisionScale.h"

HighPrecisionScale::HighPrecisionScale(int id)
    : id(id), expectedWeight(0), precision(0.1), maxWeight(5000.0) {}

double HighPrecisionScale::weigh() {
    int random = rand() % 100;
    double actual = expectedWeight;

    if (random >= 95) {
        actual = expectedWeight + (rand() % 100 - 50) / 10.0;
        if (actual < 0) actual = 0;
    }

    std::cout << "  [Высокоточные весы] " << actual << " г\n";
    return actual;
}

bool HighPrecisionScale::verifyWeight(double expected) {
    expectedWeight = expected;
    std::cout << "\n=== Высокоточные весы " << id << " ===\n";
    std::cout << "  Ожидаемый вес: " << expected << " г\n";

    double actual = weigh();
    double diff = std::abs(actual - expected);

    if (diff <= precision) {
        std::cout << "  [OK] ВЕС ПОДТВЕРЖДЁН\n";
        return true;
    }
    else {
        std::cout << "  [ERROR] РАСХОЖДЕНИЕ ВЕСА!\n";
        return false;
    }
}

void HighPrecisionScale::setExpectedWeight(double weight) {
    expectedWeight = weight;
}

double HighPrecisionScale::getMaxWeight() const {
    return maxWeight;
}

double HighPrecisionScale::getPrecision() const {
    return precision;
}

std::string HighPrecisionScale::getType() const {
    return "Высокоточные весы";
}

void HighPrecisionScale::calibrate() {
    std::cout << "  Калибровка высокоточных весов...\n";
}