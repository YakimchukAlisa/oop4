#pragma once
#include <string>
//#include <iostream>

class IExitDevice {
public:
    virtual ~IExitDevice() = default;
    virtual void open() = 0;
    virtual void close() = 0;
    virtual bool isOpen() const = 0;
    virtual std::string getType() const = 0;
};