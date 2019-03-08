#include <QtWidgets>
#include <QTextEdit>
#include <QString>
#include <QStringList>
#include "mainwidget.h"
#include "MemoryManager.h"
#include <string>
#include <iostream>

// Constructor for main widget
MainWidget::MainWidget(QWidget *parent) :QWidget(parent)
{
   button_new_process = new QPushButton(tr("New Process"));
   new_process_size = new QLineEdit();
   button_kill_process = new QPushButton(tr("Kill Process"));
   combo_kill_process = new QComboBox();
   button_process_status = new QPushButton(tr("Process Status"));
   combo_process_status = new QComboBox();
   textEdit_ = new QTextEdit();
   process_status_text = new QTextEdit();
   main_mem_manager = new MemoryManager();

   //main_mem_manager -> gen_processes();
   QGridLayout *mainLayout = new QGridLayout;
   mainLayout->addWidget(button_new_process,0,0);
   mainLayout->addWidget(new_process_size,0,1);

   mainLayout->addWidget(button_kill_process,1,0);
   mainLayout->addWidget(combo_kill_process,1,1);

   mainLayout->addWidget(button_process_status,2,0);
   mainLayout->addWidget(combo_process_status,2,1);

   mainLayout->addWidget(textEdit_,3,0);
   mainLayout->addWidget(process_status_text, 3,1);

   setLayout(mainLayout);
   setWindowTitle(tr("Memory Management"));
   QString placeHolderText = "Enter Process Size";
   new_process_size -> setPlaceholderText(placeHolderText);
   add_processes();
   this -> main_mem_manager -> first_mem_part();
   this -> set_textEdit();

   connect(button_kill_process,SIGNAL(pressed()), this, SLOT(remove_process()));
   connect(button_new_process,SIGNAL(pressed()), this, SLOT(add_single_process()));
   connect(button_process_status,SIGNAL(pressed()), this, SLOT(set_process_status_text()));
   //connect(new_process_size,SIGNAL(), this, SLOT(clear_process_size_line()));
}

// Destructor
MainWidget::~MainWidget()
{
   delete button_new_process;
   delete button_process_status;
   delete button_kill_process;
   delete new_process_size;
   delete combo_process_status;
   delete combo_kill_process;
   delete main_mem_manager;
   delete textEdit_;
   delete process_status_text;
}

void MainWidget:: add_processes(){
  QStringList tempList;
  std::vector<Process>::iterator tempPIT = this -> main_mem_manager -> pIT;

  for( tempPIT = this ->main_mem_manager -> processList.begin(); tempPIT < this-> main_mem_manager -> processList.end() ; tempPIT++ ){
    QString tempString = QString::fromStdString(tempPIT -> get_name());
    tempList.append(tempString);
  }

  this -> combo_kill_process -> insertItems(0, tempList);
  this -> combo_process_status -> insertItems(0, tempList);

}

void MainWidget::remove_process(){
  int currIndex = this -> combo_kill_process -> currentIndex();
  //std::vector<Process>::iterator tempPIT = this -> main_mem_manager -> pIT;
  std::string tempID = (this -> main_mem_manager -> processList.begin()+currIndex) -> get_name();
  this -> main_mem_manager -> deallocate_memory(std::stoi(tempID));
  this -> main_mem_manager -> processList.erase(this -> main_mem_manager -> processList.begin()+currIndex);
  this -> update(0);
}

void MainWidget:: update(int opCode){

  if(opCode == 1){
    this -> process_status_text -> clear();
  }
  this -> combo_kill_process -> clear();
  this -> combo_process_status -> clear();

  this -> add_processes();

  this -> textEdit_ -> clear();
  this -> set_textEdit();
}

void MainWidget::set_process_status_text(){
  int currIndex = this -> combo_process_status -> currentIndex();
  Process curP = this -> main_mem_manager -> processList[currIndex];
  std::string pinfo = "Process Status: \n Process ID: " + curP.get_name() + "\nProcess Size: " + std::to_string(curP.get_size())
                      + "\nProcess Location: " + std::to_string(curP.get_plocation());
  QString tempString = QString::fromStdString(pinfo);
  this -> process_status_text -> setPlainText(tempString);
  this -> update(0);
}

void MainWidget::set_textEdit(){
  std::string temp = "Free List: \n";
  std::vector<MemSpaces>::iterator it;
  for(it = this -> main_mem_manager -> freeList.begin(); it <this -> main_mem_manager -> freeList.end(); it++){
    //if(it -> get_pid() == 0)
      temp += it -> get_all_info() + '\n';
  }
  QString tempString = QString::fromStdString(temp);
  this -> textEdit_ -> setPlainText(tempString);
}

void MainWidget::add_single_process(){
  QString process_size = this -> new_process_size -> text();
  int int_psize = process_size.toInt();
  this -> main_mem_manager -> gen_single_process(int_psize);
  update(0);
}
