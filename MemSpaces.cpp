#include "MemSpaces.h"
#include <string>

MemSpaces::MemSpaces(int beginPos, int endPos){
  size = endPos - beginPos;
  pid = 0;
  begin = beginPos;
  end = endPos;
}

std::string MemSpaces::get_all_info(){
  std::string memSpaceInfo = "\nBegin: " + std::to_string(this -> begin) + "\nEnd: " + std::to_string(this -> end)
                             + "\npid: " + std::to_string(this -> pid) + "\n Size: " + std::to_string(this -> size);
  return memSpaceInfo;
}

void MemSpaces::set_size(int newSize){
  this -> size = newSize;
}

void MemSpaces::set_pid(int newPid){
  this -> pid = newPid;
}

void MemSpaces::set_begin(int newBegin){
  this -> begin = newBegin;
}

void MemSpaces::set_end(int newEnd){
  this -> end = newEnd;
}

int MemSpaces::get_size() const{
  return this -> size;
}

int MemSpaces::get_pid() const{
  return this -> pid;
}

int MemSpaces::get_begin() const{
  return this -> begin;
}

int MemSpaces::get_end() const{
  return this -> end;
}
