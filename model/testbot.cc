#include "agents/lib_agents.h"
#include <array>
#include <chrono>
#include <cstdio>
#include <ctime>
#include <fstream>
#include <iostream>
#include <map>
#include <math.h>
#include <mutex>
#include <regex>
#include <string>
#include <thread>
#include <vector>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define TELEGRAM_BOT_TOKEN "5693025715:AAHibzvbweGmTZXs8mnRejUB8JxrnqGVq6VU"
#define TELEGRAM_USER_ID "2012446774"

#define URL                                                                    \
  "https://api.telegram.org/"                                                  \
  "bot$5693025715:AAHibzvbeGmTZXs8mnRejUB8JxrnqGVq6VU/sendMessage"
#define TEXT "Deploy status: "

// static constexpr std::string host_name = []() {
//     char hostname[1024];
//     gethostname(hostname, 1024);
//     std::string retVal(hostname);
//     return (hostname);
// };

namespace {

void bot_message(double &monitor, const std::string &fuck) {
  char hostname[1024];
  gethostname(hostname, 1024);
  std::string command =
      "curl -s -d "
      "\"chat_id=2012446774&disable_web_page_preview=1&text=" +
      std::string(hostname) + fuck + " " + std::to_string(monitor) +
      "\" "
      "https://api.telegram.org/"
      "bot5693025715:AAHibzvbeGmTZXs8mnRejUB8JxrnqGVq6VU/sendMessage";
  std::string output = "";
  char buffer[128];
  std::FILE *pipe = popen(command.c_str(), "r");
  if (!pipe) {
    throw std::runtime_error("popen() failed!");
  }
  while (!std::feof(pipe)) {
    if (std::fgets(buffer, 128, pipe) != NULL)
      output += buffer;
  }
  pclose(pipe);
}

void equal(double conf, double monitor, const std::string &metrics) {
  if (conf != monitor) {
    bot_message(monitor, metrics);
  }
}

void less(double conf, double monitor, const std::string &metrics) {
  if (conf >= monitor) {
    bot_message(monitor, metrics);
  }
}

void great(double conf, double monitor, const std::string &metrics) {
  if (conf <= monitor) {
    bot_message(monitor, metrics);
  }
}

void less_equal(double conf, double monitor, const std::string &metrics) {
  if (conf > monitor) {
    bot_message(monitor, metrics);
  }
}

void great_equal(double conf, double monitor, const std::string &metrics) {
  if (conf < monitor) {
    bot_message(monitor, metrics);
  }
}
} // namespace

void Lib_agent::compare_maps() {
  for (auto it = config_map.begin(), ite = config_map.end(); it != ite; ++it) {
    if ((*it).second.first == vec_operators.at(2)) {
      equal((*it).second.second, system_metrics[(*it).first], (*it).first);
    } else if ((*it).second.first == vec_operators.at(0)) {
      less((*it).second.second, system_metrics[(*it).first], (*it).first);
    } else if ((*it).second.first == vec_operators.at(1)) {
      less_equal((*it).second.second, system_metrics[(*it).first], (*it).first);
    } else if ((*it).second.first == vec_operators.at(3)) {
      great_equal((*it).second.second, system_metrics[(*it).first],
                  (*it).first);
    } else if ((*it).second.first == vec_operators.at(4)) {
      great((*it).second.second, system_metrics[(*it).first], (*it).first);
    }
  }
}

bool check_metric() {
  Lib_agent curr;

  curr.read_conf();
  curr.starting_agents("cpu_idle_usage", "https://edu.21-school.ru", 5);
  curr.compare_maps();

  return false;
}

int main() {
  check_metric();
  return 0;
}