#ifndef MEMSPACES_H
#define MEMSPACES_H

#include <string>

class MemSpaces{

public:
  MemSpaces(int,int);
//  ~MemSpaces();

  void set_size(int newSize);
  void set_pid(int newPid);
  void set_begin(int newBegin);
  void set_end(int newEnd);

  int get_size() const;
  int get_pid() const;
  int get_begin() const;
  int get_end() const;

  friend bool operator < (MemSpaces const &lhs, MemSpaces const &rhs ){
      return lhs.begin < rhs.begin;
  }

  std::string get_all_info();

private:
  int size;
  int pid;
  int begin;
  int end;
};

#endif
