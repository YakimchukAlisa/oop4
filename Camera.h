#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Customer.h"

// Абстрактный базовый класс Camera
class Camera {
protected:
    int cameraId;
    std::string location;
    bool isActive;
    std::string videoStream; // условный поток

public:
    Camera(int id, const std::string& loc);
    virtual ~Camera() = default;

    virtual void startTracking(const std::string& customerId) = 0;
    virtual bool detectMotion() = 0;
    virtual void captureFrame() = 0;

    void activate() { isActive = true; }
    void deactivate() { isActive = false; }
    bool isActiveCamera() const { return isActive; }
    virtual void displayInfo() const;

    int getCameraId() const { return cameraId; }
    std::string getLocation() const { return location; }
};

// Базовая камера (только запись)
class BasicCamera : public Camera {
public:
    BasicCamera(int id, const std::string& loc);

    void startTracking(const std::string& customerId) override;
    bool detectMotion() override;
    void captureFrame() override;
    void displayInfo() const override;
};

// Камера с распознаванием лиц
class FaceRecognitionCamera : public Camera {
private:
    std::vector<std::string> recognizedFaces;

public:
    FaceRecognitionCamera(int id, const std::string& loc);

    void startTracking(const std::string& customerId) override;
    bool detectMotion() override;
    void captureFrame() override;
    std::string recognizeFace();
    int getRecognizedCustomerId();
    void displayInfo() const override;
};

// Камера с распознаванием товаров
class ProductRecognitionCamera : public Camera {
private:
    std::string lastDetectedAction;
    std::string lastDetectedBarcode;

public:
    ProductRecognitionCamera(int id, const std::string& loc);

    void startTracking(const std::string& customerId) override;
    bool detectMotion() override;
    void captureFrame() override;
    std::string detectTakeProduct();
    std::string detectPutProduct();
    std::string recognizeProductBarcode();
    void displayInfo() const override;
};