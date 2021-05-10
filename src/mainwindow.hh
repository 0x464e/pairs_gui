#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include "cardbutton.hh"
#include "player.hh"
#include "utils.hh"
#include "gamelogic.hh"
#include <QMainWindow>
#include <QGridLayout>
#include <QTextBrowser>
#include <QLabel>
#include <QLCDNumber>
#include <QTimer>
#include <vector>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool init_failed() const;
    void set_player_in_turn(const QString& player) const;
    void append_to_text_browser(const QString& text) const;
    void disable_all_cards() const;
    void restore_all_cards() const;
    bool all_buttons_hidden() const;
    void stop_timer();

private slots:
    void timer_callback();

private:
    //max 30
    const int CARD_COUNT = 30;
    const int GRID_SPACING = 6;
    const int TEXT_BROWSER_HEIGHT = 210;
    const QString PLAYER_IN_TURN = "Player in turn:\n";
    const QString PLAYER1_NAME = "Make";
    const QString PLAYER2_NAME = "Jorma";

    std::vector<CardButton*> cardbuttons_{};

    QWidget* central_widget_{};
    QWidget* grid_layout_widget_{};
    QTextBrowser* text_browser_{};
    QLabel* player_indicator_label_{};
    QGridLayout* grid_layout_{};
    QLCDNumber* lcd_number_{};
    QTimer timer_;
    GameLogic* game_logic_;
    bool successful_init_{};
    int timer_secs_;

    void init_widgets();
    void init_cardbuttons(unsigned card_rows, unsigned card_columns);
    void init_widget_sizes(unsigned card_rows, unsigned card_columns);
};

#endif // MAINWINDOW_HH
