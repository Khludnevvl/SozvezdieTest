#include "main_window.h"
#include "knight.h"

#include <QGraphicsView>
#include <QLabel>
#include <QLayout>
#include <QPushButton>
#include <QString>
#include <QTest>
#include <QWidget>

const size_t TOP_OFFSET = 9;
const size_t LEFT_OFFSET = 24; // letter frame width
const size_t BOX_SIZE = 83;    // Square(83px x 83px)
const size_t DELAY = 500;      // 500 ms

MainWindow::MainWindow() {
  QVBoxLayout *main_window = new QVBoxLayout();

  createBoard(main_window);
  createLineEdits(main_window);
  createButton(main_window);
  createErrorLabel(main_window);

  resize(800, 850);
  setLayout(main_window);
}

void MainWindow::createBoard(QLayout *layout) {
  QGraphicsScene *scene = new QGraphicsScene(QRectF(0, 0, 700, 700));
  QGraphicsView *view = new QGraphicsView(scene);

  QPixmap board(":images/board.png");
  scene->addPixmap(board);

  QPixmap knight_pixmap(":images/knight.png");

  knight_ = scene->addPixmap(knight_pixmap);
  knight_->hide();

  layout->addWidget(view);
}

void MainWindow::createLineEdits(QLayout *layout) {
  QGridLayout *line_edits = new QGridLayout();

  start_pos_line_edit_ = new QLineEdit();
  end_pos_line_edit_ = new QLineEdit();

  QLabel *start_pos_label = new QLabel();
  QLabel *end_pos_label = new QLabel();

  start_pos_label->setText("Start position");
  end_pos_label->setText("End position");

  line_edits->addWidget(start_pos_label, 0, 0);
  line_edits->addWidget(end_pos_label, 1, 0);

  line_edits->addWidget(start_pos_line_edit_, 0, 1);
  line_edits->addWidget(end_pos_line_edit_, 1, 1);

  dynamic_cast<QVBoxLayout *>(layout)->addLayout(line_edits);
}

void MainWindow::createButton(QLayout *layout) {
  QPushButton *start_button = new QPushButton("Start!");
  layout->addWidget(start_button);
  connect(start_button, &QPushButton::clicked, this, &MainWindow::startMoving);
}

void MainWindow::createErrorLabel(QLayout *layout) {
  QLabel *error_label = new QLabel();
  connect(this, &MainWindow::error, error_label, &QLabel::setText);
  layout->addWidget(error_label);
}

void MainWindow::setHorsePosition(int x, int y) {
  // Pos {0,0} - lower left corner, Pos{7,7} - top right corner
  knight_->setPos(BOX_SIZE * (x) + LEFT_OFFSET,
                  BOX_SIZE * (7 - y) + TOP_OFFSET);
}

void MainWindow::startMoving() {
  QPushButton *button = (QPushButton *)sender();
  button->setEnabled(false);

  const QString start_pos = start_pos_line_edit_->text();
  const QString end_pos = end_pos_line_edit_->text();

  std::vector<Position> path;

  try {
    path = knight(start_pos.toStdString(), end_pos.toStdString());
    knight_->show();
    emit error(""); // clear error label;
  } catch (WrongPosition &e) {
    emit error(e.what());
  }

  for (const auto &pos : path) {
    setHorsePosition(pos.x, pos.y);
    QTest::qWait(DELAY);
  }

  button->setEnabled(true);
}
