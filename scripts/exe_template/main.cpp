#include <fstream>
#include <QApplication>
#include "main_window.h"
#include "print_macro.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  setlocale(LC_NUMERIC, "C");
  MainWindow w;
  std::string cpp_file_name = GetFileNameFromFullPath(__FILE__);
  // Delete .cpp from file name
  cpp_file_name = cpp_file_name.substr(0, cpp_file_name.length() - 4);
  w.setWindowTitle(QString(cpp_file_name.c_str()));
  w.show();
  w.hide();

  w.show();
  return a.exec();
}

