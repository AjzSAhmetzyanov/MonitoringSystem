#ifndef LIB_AGENTS_H_
#define LIB_AGENTS_H_

#ifdef __APPLE__
#define SYSTEM_CHECK 1
#endif // __APPLE__

#ifdef __linux__
#define SYSTEM_CHECK 0
#endif // __linux__

#include "../utilitys/utils.h"
#include <array>
#include <chrono>
#include <cstdio>
#include <ctime>
#include <fstream>
#include <iostream>
#include <math.h>
#include <mutex>
#include <regex>
#include <string>
#include <thread>
#include <vector>

double cpu_load();
int number_of_processes();
double ram_total();
double ram();
double hard_volume();
double hard_ops();
double hard_throughput();
std::string validation_url(std::string url);
double speed_network();
void input_file(std::string text);
std::vector<std::string> load_value_from_config();
std::vector<int> get_metric_from_file();

double cpu_load_privilege(std::string lvl_privilege);
double total_swap_volume();
double amount_of_swap_used();
int number_of_processes_in_queue();
std::pair<double, double> counting_full_and_free_virtual_memory();
int total_number_of_inodes();
double average_hard_disk_read_time();

std::vector<std::string> cpu_agent();
std::vector<std::string> memory_agent();
std::vector<std::string> network_agent(std::string url);
std::vector<std::string> special_agent(std::string lvl_privilege);
std::vector<std::string> starting_agents(std::string lvl_privilege,
                                         std::string url, int time);

#endif // LIB_AGENTS_H_