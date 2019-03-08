#include <vector>
#include "MemoryManager.h"
#include "Process.h"
#include "MemSpaces.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <QMessageBox>

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

void MemoryManager::gen_new_part(int startPos, int endPos, int pname){
  MemSpaces *tempSpace = new MemSpaces(startPos, endPos);
  tempSpace -> set_pid(pname);
  this -> freeList.push_back(*tempSpace);
}

void MemoryManager::request_memory(int requestSize, int requestId){
  std::vector<MemSpaces>::iterator it = freeList.begin();
  bool task_done = false;
  while(it != freeList.end() && task_done == false){
    if(it -> get_size() > requestSize && it -> get_pid() == 0){
      int tempBegin = it -> get_begin();
      int tempEnd = it -> get_end();
      it = freeList.erase(it);
      this -> gen_new_part(tempBegin, tempBegin + requestSize, requestId);
      this -> gen_new_part(tempBegin + requestSize, tempEnd,0);
      std::sort(freeList.begin(), freeList.end());
      task_done = true;
    }
    else if(it ->get_size() == requestSize && it ->get_pid() == 0){
      it ->set_pid(requestId);
      task_done = true;
    }
    else{
      ++it;
    }
  }

  if(task_done == false){
    std:: cout << "here \n";

    this -> collect_garbage(requestSize, requestId);
    std::vector<Process>::iterator temp_pit = processList.begin();
    for(temp_pit; temp_pit < processList.end(); temp_pit++){
      if(temp_pit == processList.begin()){
        temp_pit -> set_plocation(0);
      }
      else {
        temp_pit -> set_plocation((temp_pit - 1) -> get_plocation() + temp_pit -> get_size());
        std:: cout << "new loc: " + (temp_pit - 1) -> get_plocation() + temp_pit -> get_size();
      }
    }

  }
}

void MemoryManager::collect_garbage(int reqsize, int reqID){
  std:: cout << "here \n";
  freeList.clear();
  this -> first_mem_part();
  int totalGarbage = 0;
  std::vector<Process>::iterator pit = processList.begin();
  for(pit; pit < processList.end(); pit ++){
    totalGarbage += pit -> get_size();
    pit -> set_plocation(totalGarbage);
    this -> request_memory(pit -> get_size(), std::stoi(pit -> get_name()));
  }
  if(totalGarbage + reqsize > 20)
  {
    QMessageBox messageBox;
    messageBox.critical(0,"Error","Not enough memory for process !");
    messageBox.setFixedSize(500,200);
  }
  else{
    this -> request_memory(reqsize, reqID);

  }
}

void MemoryManager::deallocate_memory(int id){
  std::vector<MemSpaces>::iterator it = freeList.begin();
  bool task_done = false;
  //printf("iterator %p\n", it);
//  printf("freeList begin %p\n", freeList.begin());
//  printf("PID %d\n",id);
//  printf("PID %d\n",it -> get_pid());
  int vector_index_adjuster = 0;
  while(it != freeList.end() && task_done == false){
    if(it -> get_pid() == id){
      // check if deallocating at start of list
      if(it == freeList.begin() && freeList.size() == 1 ){
        it -> set_pid(0);
      }
      else if(it == freeList.begin() && freeList.size() > 1){
        auto next_it = it + 1;
        printf("iterator %p\n", it);
        if(next_it -> get_pid() == 0){
          //int tempSize = it -> get_size() + next_it -> get_size();
          int tempBegin = it -> get_begin();
          int tempEnd = next_it -> get_end();
          MemSpaces *combinedSpace = new MemSpaces(tempBegin, tempEnd);
          freeList.erase(it, next_it + 1);
          freeList.insert(freeList.begin(), *combinedSpace);
        }
        else{
          it -> set_pid(0);
        }
      }
      else if(it != freeList.begin() && it!= freeList.end()){
        auto prev_it = it - 1;
        auto next_it = it + 1;
        if(next_it -> get_pid() != 0 && prev_it -> get_pid() != 0){
          it -> set_pid(0);
        }
        else if(next_it -> get_pid() == 0 && prev_it -> get_pid() != 0){
          int tempBegin = it -> get_begin();
          int tempEnd = next_it -> get_end();
          MemSpaces *combinedSpace = new MemSpaces(tempBegin, tempEnd);
          freeList.erase(it, next_it + 1);
          freeList.insert(freeList.begin()+vector_index_adjuster, *combinedSpace);
        }
        else if(next_it -> get_pid() != 0 && prev_it -> get_pid() == 0){
          int tempBegin = prev_it -> get_begin();
          int tempEnd = it -> get_end();
          MemSpaces *combinedSpace = new MemSpaces(tempBegin, tempEnd);
          freeList.erase(prev_it,it + 1);
          freeList.insert(freeList.begin()+vector_index_adjuster-1, *combinedSpace);

        }
        else if(next_it -> get_pid() == 0 && prev_it -> get_pid() == 0){
          int tempBegin = prev_it -> get_begin();
          int tempEnd = next_it -> get_end();
          MemSpaces *combinedSpace = new MemSpaces(tempBegin, tempEnd);
          freeList.erase(prev_it, next_it + 1);
          freeList.insert(freeList.begin()+vector_index_adjuster-1, *combinedSpace);
        }
      }
      else if(it == freeList.end()){
        auto prev_it = it - 1;
        if(prev_it -> get_pid() == 0){
          int tempBegin = prev_it -> get_begin();
          int tempEnd = it -> get_end();
          MemSpaces *combinedSpace = new MemSpaces(tempBegin, tempEnd);
          freeList.erase(prev_it, it + 1);
          freeList.insert(freeList.begin()+vector_index_adjuster-1, *combinedSpace);
        }
        else{
          it -> set_pid(0);
        }
      }
      else{
        it -> set_pid(0);
      }
      std::sort(freeList.begin(), freeList.end());
      task_done = true;
    }
    else{
      ++it;
      ++vector_index_adjuster;
    }
  }
}

void MemoryManager::gen_single_process(int p_size){
  Process* tempProcess = new Process(p_size);
  this -> request_memory(tempProcess -> get_size(), std::stoi(tempProcess -> get_name()));

  std::vector<MemSpaces>::iterator mit = freeList.begin();
  for(mit; mit < freeList.end(); mit++){
    if(std::to_string(mit -> get_pid()) == tempProcess -> get_name()){
      tempProcess -> set_plocation(mit -> get_begin());
    }
  }
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
