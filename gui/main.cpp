#include <unistd.h>

#include "mainwindow.h"
#include "ppm.hh"
#include <CLI/CLI.hpp>
#include <QApplication>
#include <QImage>
#include <QPixmap>
#include <QResizeEvent>
#include <QSize>
#include <QWidget>
#include <Qt>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <print>
static QImage load_image(std::istream &in) {
  Ppm ppm(in);
  return ppm.image();
}

int main(int argc, char *argv[]) {
  CLI::App cli{"PPM image viewer"};
  std::filesystem::path path;
  cli.add_option("--file", path,
                 "PPM file to open (omit or '-' to read stdin)");
  CLI11_PARSE(cli, argc, argv);

  const bool from_stdin = path.empty() || path == "-";
  if (from_stdin && isatty(STDIN_FILENO)) {
    std::println(stderr, "{}", cli.help());
    return 1;
  }

  QApplication app(argc, argv);

  QImage image;
  if (from_stdin) {
    image = load_image(std::cin);
  } else {
    std::ifstream file(path);
    if (!file.is_open()) {
      std::println(stderr, "cannot open the file");
      return 1;
    }
    image = load_image(file);
  }
  if (image.isNull()) {
    std::println(stderr, "failed to read a PPM image");
    return 1;
  }
  MainWindow w(image);
  w.resize(image.width(), image.height());
  w.show();
  return app.exec();
}