#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QGraphicsItem>
#include <QGraphicsView>
#include <QLineEdit>
#include <QWidget>

class MainWindow : public QWidget {
  Q_OBJECT
public:
  MainWindow();

private:
  void setHorsePosition(int x, int y);
  void createBoard(QLayout *layout);
  void createLineEdits(QLayout *layout);
  void createButton(QLayout *layout);
  void createErrorLabel(QLayout *layout);

  QGraphicsPixmapItem *horse_;
  QLineEdit *start_pos_line_edit_;
  QLineEdit *end_pos_line_edit_;

signals:
  void error(const QString &msg);

public slots:

  void startMoving();
};

#endif // MAIN_WINDOW_H
