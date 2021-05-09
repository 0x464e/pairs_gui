#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include "cardbutton.hh"
#include "utils.hh"
#include "game_logic.hh"
#include <QMainWindow>
#include <QGridLayout>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    //max 30
    const int CARD_COUNT = 30;
    QWidget* central_widget_;
    QWidget* grid_layout_widget_;
    QGridLayout* grid_layout_;
    std::vector<CardButton*> buttons_;
    game_logic game_logic_;
};
#endif // MAINWINDOW_HH
