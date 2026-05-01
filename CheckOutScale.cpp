#include "CheckoutScale.h"
#include <cmath>
#include <cstdlib>
#include <thread>
#include <chrono>

CheckoutScale::CheckoutScale(int id, double prec) : id(id), expectedWeight(0), precision(prec) {}

HighPrecisionScale::HighPrecisionScale(int id) : CheckoutScale(id, 0.1) {}

bool HighPrecisionScale::verifyWeight() {
    std::cout << "\nВесы " << id << ": проверка веса (ожидается " << expectedWeight << " г)\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    int r = rand() % 100;
    double actual = (r < 70) ? expectedWeight : expectedWeight + (rand() % 500) - 250;
    if (actual < 0) actual = 0;

    std::cout << "  Фактический вес: " << actual << " г\n";
    double diff = std::abs(actual - expectedWeight);
    if (diff <= precision) {
        std::cout << "  Вес подтверждён\n";
        return true;
    }
    std::cout << "  Расхождение веса!\n";
    return false;
}

