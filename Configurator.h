#pragma once
#include <string>
#include <map>

class Configurator {
    std::map<std::string, std::string> settings;
public:
    void loadConfiguration(const std::string& filename);
    void displayConfiguration() const;
    std::string getSetting(const std::string& key) const;
};