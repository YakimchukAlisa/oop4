#include "PostalScale.h"

PostalScale::PostalScale(int id)
    : id(id), expectedWeight(0), precision(10.0), maxWeight(30000.0), isRounded(true) {}

double PostalScale::weigh() {
    int random = rand() % 100;
    double actual = expectedWeight;

    if (random >= 95) {
        actual = expectedWeight + (rand() % 20);
        if (actual < 0) actual = 0;
    }

    // Округление вверх (как на почте)
    if (isRounded) {
        actual = std::ceil(actual / 10.0) * 10.0;
    }

    std::cout << "  [Почтовые весы] " << actual << " г";
    if (isRounded) std::cout << " (округлено вверх)";
    std::cout << "\n";
    return actual;
}

bool PostalScale::verifyWeight(double expected) {
    expectedWeight = expected;
    std::cout << "\n=== Почтовые весы " << id << " ===\n";
    std::cout << "  Ожидаемый вес: " << expected << " г\n";

    double actual = weigh();
    double diff = std::abs(actual - expected);

    // Автоматически выводим стоимость доставки
    double postage = calculatePostage();
    std::cout << "  Стоимость доставки: " << postage << " руб. (тариф 150 руб/кг)\n";

    if (diff <= precision) {
        std::cout << "  [OK] ВЕС ПОДТВЕРЖДЁН\n";
        return true;
    }
    else {
        std::cout << "  [ERROR] РАСХОЖДЕНИЕ ВЕСА!\n";
        return false;
    }
}

void PostalScale::setExpectedWeight(double weight) {
    expectedWeight = weight;
}

double PostalScale::getMaxWeight() const {
    return maxWeight;
}

double PostalScale::getPrecision() const {
    return precision;
}

std::string PostalScale::getType() const {
    return "Почтовые весы";
}

double PostalScale::calculatePostage() const {
    double weightKg = expectedWeight / 1000.0;
    return weightKg * 150.0;
}