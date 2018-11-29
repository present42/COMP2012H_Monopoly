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
    void initGameWindow();

private:
    Ui::MainWindow *ui;
    Server* game_instance;
    GameWindow* game_window;

private slots:
    void startButton_clicked_handler();
    void game_window_closed_handler();

    void handler(int id);

};

#endif // MAINWINDOW_H
