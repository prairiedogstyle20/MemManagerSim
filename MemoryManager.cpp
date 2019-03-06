#include <vector>
#include "MemoryManager.h"
#include "Process.h"
#include "MemSpaces.h"
#include <iostream>
#include <string>

//#include <QDebug>

MemoryManager::MemoryManager(){
  absoluteBeginFree = 0;
  absoluteEndFree = 20;
  relativeBeginFree = 0;
  relativeEndFree = 20;
}

void MemoryManager::gen_processes(){
  int i = 0;
  for(i; i < 7; i++){
    Process* tempProcess = new Process(i);
    this -> processList.push_back(*tempProcess);
  }
}

void MemoryManager:: first_mem_part(){
  this -> gen_new_part(this -> get_beginFree(), this -> get_endFree(),0);
}

void MemoryManager::gen_new_part(int startPos, int endPos, int pname = 0){
  MemSpaces *tempSpace = new MemSpaces(startPos, endPos);
  tempSpace -> set_pid(pname);
  this -> freeList.push_back(*tempSpace);
}

void MemoryManager::request_memory(int requestSize, int requestId){
  std::vector<MemSpaces>::iterator it = this -> freeList.begin();
  while(it != freeList.end()){
    if(it -> get_size() > requestSize && it -> get_pid() == 0){
      this -> gen_new_part(it -> get_begin(), requestSize, requestId);
      this -> gen_new_part(it -> get_begin() + requestSize, it ->get_end(),0);
      //it = freeList.erase(it);
      break;
    }
    else if(it ->get_size() == requestSize && it ->get_pid() == 0){
      it ->set_pid(it ->get_pid());
      break;
    }
    else{
      ++it;
    }
  }
}

void MemoryManager::gen_single_process(int p_size){
  Process* tempProcess = new Process(p_size);
  this -> request_memory(tempProcess -> get_size(), std::stoi(tempProcess -> get_name()));
  this -> processList.push_back(*tempProcess);
}

void MemoryManager::set_beginFree(int newBegin){
  this -> relativeBeginFree = newBegin;
}

void MemoryManager::set_endFree(int newEnd){
  this -> relativeEndFree = newEnd;
}

int MemoryManager::get_beginFree(){
  return this -> relativeBeginFree;
}

int MemoryManager::get_endFree(){
  return this -> relativeEndFree;
}
