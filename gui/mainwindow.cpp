#include "mainwindow.h"

#include <QImage>
#include <QLabel>
#include <QMainWindow>
#include <QPixmap>
#include <QWidget>

MainWindow::MainWindow(const QImage &image, QWidget *parent)
    : QMainWindow(parent), m_label(new QLabel(this)) {
  m_label->setPixmap(QPixmap::fromImage(image));
  setCentralWidget(m_label);
  setWindowTitle("ppm_viewer");
}