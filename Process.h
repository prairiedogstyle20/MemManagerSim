#ifndef PROCESS_H
#define PROCESS_H

#include <vector>
#include <string>


class Process {

public:
  Process(int);

  void set_plocation(int);

  int get_plocation();

  std::string get_name();

  int get_size();

  void set_status(std::string);

  std::string get_status();

  //std::string pstatus;

private:

  int name;
  int pSize;
  int pLocation;
};

#endif
