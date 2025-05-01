#include "metrobaku.h"
#include <iostream>
#include <chrono>
#include <iomanip>
#include <mutex>
#include <sstream>
#include <ctime>
#include <thread>

int travel_time = 2;
int stop_time = 1;
int turnaround_time = 3;
int train_start_delay = 2;
int max_round = 1;
int max_round_2 = 1;

std::mutex print_mutex;

std::vector<std::string> Redline = {
    "Hazi Aslanov", "Ahmadli", "Xalqlar Dostlugu", "Nefchiler", "Qara Qarayev",
    "Koroglu", "Ulduz", "Bakmil", "Nariman Narimanov", "Ganjlik",
    "28 May", "Sahil", "Icherisheher"
};

std::vector<std::string> Greenline = {
    "Hazi Aslanov", "Ahmadli", "Xalqlar Dostlugu", "Nefchiler", "Qara Qarayev",
    "Koroglu", "Ulduz", "Bakmil", "Nariman Narimanov", "Ganjlik", "28 May",
    "Nizami", "Elmler Akademiyasi", "Inshaatcilar", "20 Yanvar", "Memar Ajami",
    "Nasimi", "Azadliq", "Darnagul"
};

std::string current_time() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    std::tm *parts = std::localtime(&now_c);

    std::ostringstream oss;
    oss << "[" << std::put_time(parts, "%H:%M:%S") << "]";
    return oss.str();
}

void print_log(const std::string& message) {
    std::lock_guard<std::mutex> lock(print_mutex);
    std::cout << current_time() << " " << message << std::endl;
}

void RedmetroTrain(int id) {
    std::this_thread::sleep_for(std::chrono::seconds(static_cast<int>(1.2 * id * train_start_delay)));

    for (int m = 0; m < max_round; m++) {
        for (std::size_t i = 7; i < Redline.size(); i++) {
            print_log("RedlineMetro " + std::to_string(id) + " - Arrived at: " + Redline[i]);
            std::this_thread::sleep_for(std::chrono::seconds(stop_time));

            if (i < Redline.size() - 1) {
                print_log("RedlineMetro " + std::to_string(id) + " - Departing for " + Redline[i + 1] + "...");
                std::this_thread::sleep_for(std::chrono::seconds(travel_time));
            }
        }

        print_log("RedlineMetro " + std::to_string(id) + " - Turning around at " + Redline.back());
        std::this_thread::sleep_for(std::chrono::seconds(turnaround_time));

        for (int i = static_cast<int>(Redline.size()) - 1; i >= 0; i--) {
            if (Redline[i] == "Bakmil") continue;
            print_log("RedlineMetro " + std::to_string(id) + " - Arrived at: " + Redline[i]);
            std::this_thread::sleep_for(std::chrono::seconds(stop_time));

            if (Redline[i] == "Nariman Narimanov") {
                print_log("RedlineMetro " + std::to_string(id) + " - Departing for Ulduz...");
                std::this_thread::sleep_for(std::chrono::seconds(travel_time));
            }

            if (i > 0 && Redline[i - 1] != "Bakmil") {
                print_log("RedlineMetro " + std::to_string(id) + " - Departing for " + Redline[i - 1] + "...");
                std::this_thread::sleep_for(std::chrono::seconds(travel_time));
            }
        }

        print_log("RedlineMetro " + std::to_string(id) + " - Turning around at Hazi Aslanov");
        std::this_thread::sleep_for(std::chrono::seconds(turnaround_time));
    }

    print_log("RedlineMetro " + std::to_string(id) + " - Heading to depo: Bakmil.");
    for (int i = static_cast<int>(Redline.size()) - 1; i >= 7; i--) {
        if (i != static_cast<int>(Redline.size()) - 1)
            print_log("RedlineMetro " + std::to_string(id) + " - Departing for " + Redline[i]);
        std::this_thread::sleep_for(std::chrono::seconds(travel_time));
        print_log("RedlineMetro " + std::to_string(id) + " - Arrived at: " + Redline[i]);
        std::this_thread::sleep_for(std::chrono::seconds(stop_time));
    }

    print_log("RedlineMetro " + std::to_string(id) + " - Arrived at depo: Bakmil.");
}

void GreenmetroTrain(int id) {
    std::this_thread::sleep_for(std::chrono::seconds(static_cast<int>(1.2 * id * train_start_delay)));

    for (int m = 0; m < max_round_2; m++) {
        for (std::size_t i = 7; i < Greenline.size(); i++) {
            print_log("GreenlineMetro " + std::to_string(id) + " - Arrived at: " + Greenline[i]);
            std::this_thread::sleep_for(std::chrono::seconds(stop_time));

            if (i < Greenline.size() - 1) {
                print_log("GreenlineMetro " + std::to_string(id) + " - Departing for " + Greenline[i + 1] + "...");
                std::this_thread::sleep_for(std::chrono::seconds(travel_time));
            }
        }

        print_log("GreenlineMetro " + std::to_string(id) + " - Turning around at Darnagul");
        std::this_thread::sleep_for(std::chrono::seconds(turnaround_time));

        for (int i = static_cast<int>(Greenline.size()) - 1; i >= 0; i--) {
            if (Greenline[i] == "Bakmil") continue;

            print_log("GreenlineMetro " + std::to_string(id) + " - Arrived at: " + Greenline[i]);
            std::this_thread::sleep_for(std::chrono::seconds(stop_time));

            if (Greenline[i] == "Nariman Narimanov") {
                print_log("GreenlineMetro " + std::to_string(id) + " - Departing for Ulduz...");
                std::this_thread::sleep_for(std::chrono::seconds(travel_time));
            }

            if (i > 0 && Greenline[i - 1] != "Bakmil") {
                print_log("GreenlineMetro " + std::to_string(id) + " - Departing for " + Greenline[i - 1] + "...");
                std::this_thread::sleep_for(std::chrono::seconds(travel_time));
            }
        }

        print_log("GreenlineMetro " + std::to_string(id) + " - Turning around at Hazi Aslanov");
        std::this_thread::sleep_for(std::chrono::seconds(turnaround_time));
    }

    print_log("GreenlineMetro " + std::to_string(id) + " - Heading to depo: Bakmil.");
    for (std::size_t i = 0; i <= 7; i++) {
        if (i != 0)
            print_log("GreenlineMetro " + std::to_string(id) + " - Departing for " + Greenline[i]);
        std::this_thread::sleep_for(std::chrono::seconds(travel_time));
        print_log("GreenlineMetro " + std::to_string(id) + " - Arrived at: " + Greenline[i]);
        std::this_thread::sleep_for(std::chrono::seconds(stop_time));
    }

    print_log("GreenlineMetro " + std::to_string(id) + " - Arrived at depo: Bakmil.");
}
