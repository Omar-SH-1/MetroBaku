#include "metrobaku.h"

int main() {
    std::vector<std::thread> metros;
    int total_trains = 4;

    for (int i = 0; i < total_trains; i++) {
        if (i % 2 == 0)
            metros.emplace_back(GreenmetroTrain, i);
        else
            metros.emplace_back(RedmetroTrain, i);
    }

    for (auto &t : metros) {
        t.join();
    }

    return 0;
}
