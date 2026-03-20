#pragma once
#include <iostream>

class Turnstile {
    int id;
    std::string location;
    bool locked;
public:
    Turnstile(int id, const std::string& loc);
    void unlockForEntry();
    void unlockForExit();
    void lock();
    void displayInfo() const;
};