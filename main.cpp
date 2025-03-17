#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <mutex>
#include <fstream>

const int numst = 6;
const int numtr = 2;
std::mutex mutexS[numst];
std::string stationNames[numst] = {"Бакмил", "Нариман Нариманов", "Гянджлик", "28 мая", "Сахиль", "Ичеришехер"};

void trainBaku(int trainID, const std::string &filename) {
    int station = 0;
    int direction = 1;
    std::ofstream logFile(filename);
    if (!logFile.is_open()) {
        std::cerr << "Не удалось открыть файл для записи: " << filename << std::endl;
        return;
    }

    for (int i = 0; i < 12; i++) {
        mutexS[station].lock();
        logFile << "Поезд " << trainID << " на станции " << stationNames[station] << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        logFile << "Поезд " << trainID << " покидает " << stationNames[station] << std::endl;
        mutexS[station].unlock();

        station += direction;
        if (station == 0 || station == numst - 1) {
            direction = -direction;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    // Возвращаем поезд в депо "Бакмил"
    while (station != 0) {
        mutexS[station].lock();
        logFile << "Поезд " << trainID << " на станции " << stationNames[station] << " (возвращение в депо)" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        logFile << "Поезд " << trainID << " покидает " << stationNames[station] << " (возвращение в депо)" << std::endl;
        mutexS[station].unlock();
        station--;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    logFile << "Поезд " << trainID << " прибыл в депо Бакмил" << std::endl;
    logFile.close();
}

int main() {
    std::vector<std::thread> trains;
    for (int i = 0; i < numtr; i++) {
        std::string filename = "train_" + std::to_string(i) + "_log.txt";
        trains.emplace_back(trainBaku, i, filename);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    for (auto& train : trains) {
        train.join();
    }

    return 0;
}
