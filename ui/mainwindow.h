#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <src/server.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Server* game_instance;

private slots:
    void startButton_clicked_handler();
    void game_window_closed_handler();
};

#endif // MAINWINDOW_H
