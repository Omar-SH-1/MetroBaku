#ifndef METROBAKU_H
#define METROBAKU_H

#include <string>
#include <vector>
#include <thread>

// Глобальные параметры (можно позже убрать в структуру/класс)
extern int travel_time;
extern int stop_time;
extern int turnaround_time;
extern int train_start_delay;
extern int max_round;
extern int max_round_2;

void RedmetroTrain(int id);
void GreenmetroTrain(int id);
std::string current_time();
void print_log(const std::string& message);

#endif // METROBAKU_H

