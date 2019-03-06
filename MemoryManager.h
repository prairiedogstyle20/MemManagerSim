#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H

#include <vector>
#include "Process.h"
#include "MemSpaces.h"
#include <random>
#include <string>

class MemoryManager {

  public:
    MemoryManager();
  //  ~MemoryManager();
    void gen_processes();
    void gen_single_process(int);

    void set_beginFree(int);
    void set_endFree(int);

    void first_mem_part();
    void gen_new_part(int, int, int);

    int get_beginFree();
    int get_endFree();

    void request_memory(int, int);

    std::vector<Process> processList;
    std::vector<Process>::iterator pIT;
    std::vector<MemSpaces> freeList;
    std::vector<MemSpaces>::iterator flIT;

  private:
    int absoluteBeginFree;
    int absoluteEndFree;
    int relativeBeginFree;
    int relativeEndFree;
};

#endif
