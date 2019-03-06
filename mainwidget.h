#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QTextEdit>
#include "MemoryManager.h"

class QPushButton;
class QLineEdit;
class QTextEdit;
class QComboBox;

class MainWidget: public QWidget{

  Q_OBJECT

public:
  explicit MainWidget(QWidget *parent=0);
  ~MainWidget();

  void add_processes();

  void update(int);
  void set_textEdit();

private slots:
  void remove_process();
  void set_process_status_text();
  void add_single_process();

private:
  MemoryManager* main_mem_manager;
  QPushButton* button_new_process;
  QLineEdit * new_process_size;
  QPushButton* button_kill_process;
  QComboBox* combo_kill_process;
  QPushButton* button_process_status;
  QComboBox* combo_process_status;
  QTextEdit* textEdit_;
  QTextEdit* process_status_text;
};

#endif
