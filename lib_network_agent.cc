#include "utils.h"
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

void uploading_data_to_file(const std::vector<double> &data1,
                            const std::vector<double> &data2,
                            std::pair<bool, double> config) {
  std::ofstream file("config.conf");
  file << "Data1:" << std::endl;
  for (double d : data1) {
    file << d << std::endl;
  }
  file << "Data2:" << std::endl;
  for (double d : data2) {
    file << d << std::endl;
  }
  file << "Configuration:" << std::endl;
  file << "Option: " << config.first << std::endl;
  file << "Value: " << config.second << std::endl;
  file.close();
}

std::string validation_url(std::string url) {
  std::string command =
      "curl -I " + url + " -o /dev/null -s -w '%{http_code}\n'";
  int status = std::system(command.c_str());
  return (status == 0 ? "available" : " not available");
}

double speed_network() {
  std::string s1 = "netstat -bI en0 | grep -E \"en0|Bytes\" | grep -v \"Refs\" "
                   "| awk '{print $7}' | tail -1";
  std::string command = s1;
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
  //   std::smatch match;
  //   std::regex pattern("[a-z]+:\\s+(\\d+)\\s+(\\d+)");
  //   double inet_through = 0;
  //   while (std::regex_search(output, match, pattern)) {
  //     double rx = std::stod(match[1]);
  //     double tx = std::stod(match[2]);
  //     inet_through += rx + tx;
  //     output = match.suffix().str();
  //   }
  //   return inet_through;
  //   std::cout << output << std::endl;
  return std::stod(output) / 1024 / 1024 / 1024;
}

void starting_network_agent(std::string url, bool check) {
  std::string result;
  if (check) {
    double speed_network_ = speed_network();
    // std::cout << speed_network_ << std::endl;
    std::string url_ = validation_url(url);
    result = get_time() + " | " + url + " : " + url_ + " | " +
             "inet_throughput" + " : " + std::to_string(speed_network_);
  }
  input_file(result);
}
