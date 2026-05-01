#pragma once
#include "IExitDevice.h"
#include <iostream>

class AutoDoor : public IExitDevice {
private:
    int id;
    std::string location;
    bool opened;
    int sensorId;  // датчик движения

public:
    AutoDoor(int id, const std::string& loc, int sensorId = 0);

    void open() override;
    void close() override;
    bool isOpen() const override;
    std::string getType() const override;

    void displayInfo() const;
};