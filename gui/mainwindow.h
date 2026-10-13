#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QImage>
#include <QLabel>
#include <QMainWindow>
#include <QObject>
#include <QWidget>
class QResizeEvent;

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(const QImage &image, QWidget *parent = nullptr);

protected:
  void resizeEvent(QResizeEvent *event) override;

private:
  QImage m_image;
  QLabel *m_label;

  void update_image();
};

#endif
