#include <random>
#include <cstdlib>
#include <ctime>
#include "Process.h"
#include <string>
#include <iostream>

Process::Process(int size){
  static std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(1,1000);
  name = dis(gen);
  pSize = size;
  pLocation = 0;
  //pstatus = std::str("waiting");
}

void Process:: set_plocation(int location){
  this-> pLocation = location;
}

int Process:: get_plocation(){
    return this -> pLocation;
}

std::string Process::get_name(){
  return std::to_string(this -> name);
}

int Process::get_size(){
  return this -> pSize;
}

/*
void Process::set_status(std::string newStatus){
  this -> status = newStatus;
}

std::string::get_status(){
  return this -> status;
}
*/
