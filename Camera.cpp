#include "Camera.h"
#include <iostream>

// Реализация Camera
Camera::Camera(int id, const std::string& loc)
    : cameraId(id), location(loc), isActive(false), videoStream("") {}

void Camera::displayInfo() const {
    std::cout << "Камера ID: " << cameraId << ", Расположение: " << location
        << ", Статус: " << (isActive ? "Активна" : "Неактивна") << std::endl;
}

// Реализация BasicCamera
BasicCamera::BasicCamera(int id, const std::string& loc) : Camera(id, loc) {}

void BasicCamera::startTracking(const std::string& customerId) {
    if (isActive) {
        std::cout << "Базовая камера " << cameraId << ": начало отслеживания покупателя "
            << customerId << std::endl;
    }
}

bool BasicCamera::detectMotion() {
    if (!isActive) return false;
    // Имитация обнаружения движения (50% вероятность)
    bool motion = (rand() % 2 == 0);
    if (motion) {
        std::cout << "Базовая камера " << cameraId << ": движение обнаружено" << std::endl;
    }
    return motion;
}

void BasicCamera::captureFrame() {
    if (isActive) {
        std::cout << "Базовая камера " << cameraId << ": кадр сохранен" << std::endl;
    }
}

void BasicCamera::displayInfo() const {
    Camera::displayInfo();
    std::cout << "  Тип: Базовая камера (только запись)" << std::endl;
}

// Реализация FaceRecognitionCamera
FaceRecognitionCamera::FaceRecognitionCamera(int id, const std::string& loc) : Camera(id, loc) {}

void FaceRecognitionCamera::startTracking(const std::string& customerId) {
    if (isActive) {
        std::cout << "FaceRecognition камера " << cameraId
            << ": начало отслеживания лица покупателя " << customerId << std::endl;
    }
}

bool FaceRecognitionCamera::detectMotion() {
    if (!isActive) return false;
    bool motion = (rand() % 2 == 0);
    return motion;
}

void FaceRecognitionCamera::captureFrame() {
    if (isActive) {
        std::cout << "FaceRecognition камера " << cameraId << ": кадр захвачен для анализа лица" << std::endl;
        recognizeFace();
    }
}

std::string FaceRecognitionCamera::recognizeFace() {
    std::string face = "Customer_" + std::to_string(rand() % 1000);
    recognizedFaces.push_back(face);
    std::cout << "  -> Распознано лицо: " << face << std::endl;
    return face;
}

int FaceRecognitionCamera::getRecognizedCustomerId() {
    return rand() % 1000; // имитация ID
}

void FaceRecognitionCamera::displayInfo() const {
    Camera::displayInfo();
    std::cout << "  Тип: Камера с распознаванием лиц" << std::endl;
}

// Реализация ProductRecognitionCamera
ProductRecognitionCamera::ProductRecognitionCamera(int id, const std::string& loc) : Camera(id, loc) {}

void ProductRecognitionCamera::startTracking(const std::string& customerId) {
    if (isActive) {
        std::cout << "ProductRecognition камера " << cameraId
            << ": отслеживание действий покупателя " << customerId << std::endl;
    }
}

bool ProductRecognitionCamera::detectMotion() {
    return (rand() % 2 == 0);
}

void ProductRecognitionCamera::captureFrame() {
    if (isActive) {
        std::cout << "ProductRecognition камера " << cameraId
            << ": анализ действий с товарами" << std::endl;
    }
}

std::string ProductRecognitionCamera::detectTakeProduct() {
    lastDetectedAction = "TAKE";
    std::cout << "  -> Обнаружено действие: ТОВАР ВЗЯТ" << std::endl;
    return lastDetectedAction;
}

std::string ProductRecognitionCamera::detectPutProduct() {
    lastDetectedAction = "PUT";
    std::cout << "  -> Обнаружено действие: ТОВАР ВОЗВРАЩЕН" << std::endl;
    return lastDetectedAction;
}

std::string ProductRecognitionCamera::recognizeProductBarcode() {
    std::vector<std::string> barcodes = { "123456789", "987654321", "555555555" };
    lastDetectedBarcode = barcodes[rand() % 3];
    std::cout << "  -> Распознан штрих-код товара: " << lastDetectedBarcode << std::endl;
    return lastDetectedBarcode;
}

void ProductRecognitionCamera::displayInfo() const {
    Camera::displayInfo();
    std::cout << "  Тип: Камера с распознаванием товаров" << std::endl;
}