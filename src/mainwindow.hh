#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include "cardbutton.hh"
#include "utils.hh"
#include "gamelogic.hh"
#include <QMainWindow>
#include <QGridLayout>
#include <QTextBrowser>
#include <QLabel>
#include <QLCDNumber>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    //max 30
    const int CARD_COUNT = 30;
    const int GRID_SPACING = 6;
    const int TEXT_BROWSER_HEIGHT = 210;
    const QString PLAYER_IN_TURN = "Player in turn:\nPlayer";
    QWidget* central_widget_;
    QWidget* grid_layout_widget_;
    QTextBrowser* text_browser_;
    QLabel* player_indicator_label_;
    QGridLayout* grid_layout_;
    QLCDNumber* lcd_number_;
    GameLogic game_logic_;
};
#endif // MAINWINDOW_HH
