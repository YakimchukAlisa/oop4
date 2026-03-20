#pragma once
#include <string>
#include <iostream>

// Класс турникета/умной двери
class Turnstile {
private:
    int turnstileId;
    std::string location; // "Вход" или "Выход"
    bool isLocked;
    int entriesCount; // счетчик проходов
    int exitsCount;

public:
    Turnstile(int id, const std::string& loc);

    // Команды управления
    void unlockForEntry();
    void unlockForExit();
    void lock();

    // Состояние
    bool isLockedStatus() const { return isLocked; }
    int getEntriesCount() const { return entriesCount; }
    int getExitsCount() const { return exitsCount; }

    void displayInfo() const;
};