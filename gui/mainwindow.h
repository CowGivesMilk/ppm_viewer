#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QImage>
#include <QMainWindow>
#include <qwidget.h>

class QLabel;

class MainWindow : public QMainWindow {
public:
  explicit MainWindow(const QImage &image, QWidget *parent = nullptr);

private:
  QLabel *m_label;
};

#endif
