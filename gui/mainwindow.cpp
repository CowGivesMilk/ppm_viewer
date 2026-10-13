
#include "mainwindow.h"

#include <QImage>
#include <QLabel>
#include <QMainWindow>
#include <QObject>
#include <QResizeEvent>
#include <QSize>
#include <Qt>

MainWindow::MainWindow(const QImage &image, QWidget *parent)
    : QMainWindow(parent), m_image(image), m_label(new QLabel(this)) {
  m_label->setAlignment(Qt::AlignCenter);
  m_label->setContentsMargins(0, 0, 0, 0);

  setCentralWidget(m_label);
  setWindowTitle("ppm_viewer");

  update_image();
}

void MainWindow::resizeEvent(QResizeEvent *event) {
  QMainWindow::resizeEvent(event);
  update_image();
}

void MainWindow::update_image() {
  if (m_image.isNull()) {
    return;
  }

  const QSize available_size = m_label->contentsRect().size();

  QPixmap pixmap = QPixmap::fromImage(m_image);

  if (m_image.width() > available_size.width() ||
      m_image.height() > available_size.height()) {
    pixmap = pixmap.scaled(available_size, Qt::KeepAspectRatio,
                           Qt::SmoothTransformation);
  }

  m_label->setPixmap(pixmap);
}
