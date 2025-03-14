#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <mutex>
const int numst = 6;
const int numtr = 2;
std::mutex mutexS[numst];
std::string stationNames[numst] = {"Бакмил", "Нариман Нариманов", "Гянджлик", "28 мая", "Сахиль", "Ичеришехер"};

void trainBaku(int trainID) {
    int station = 0;
    int direction = 1;
    while (true) {
        mutexS[station].lock();

        std::cout << "Поезд " << trainID << " на станции " << stationNames[station] << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "Поезд " << trainID << " покидает " << stationNames[station] << std::endl;
        mutexS[station].unlock();
        station += direction;
        if (station == 0 || station == numst - 1) {
            direction = -1;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

int main() {
    std::vector<std::thread> trains;
    for (int i = 0; i < numtr; i++) {
        trains.emplace_back(trainBaku, i);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    for (auto& train : trains) {
        train.join();
    }
}
