/* Class MainWindow
 * ----------
 * COMP.CS.110 SPRING 2021
 * ----------
 * Class for the main window. Creates the GUI for this program.
 * */

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
    /**
     * Constructor, initializes the creation of the main GUI window.
     *
     * \param parent QWidget* parent for this object
     * \return MainWindow object
     */
    explicit MainWindow(QWidget *parent = nullptr);

    /**
     * Method to retrieve the initialization success state.
     * 
     * \return bool true for a failed initialization
     */
    bool init_failed() const;

    /**
     * Sets the player in turn for the QLabel ui component.
     * 
     * \param player QString player's name
     */
    void set_player_in_turn(const QString& player) const;
    
    /**
     * Appends text to the QTextBrowser ui component.
     * 
     * \param text QString text to append
     */
    void append_to_text_browser(const QString& text) const;
    
    //disables all cards in the playing field
    void disable_all_cards() const;
    //restores all cards in the playing field from the disabled state
    void restore_all_cards() const;
    //returns whether all card buttons are hidden, true if they are
    bool all_buttons_hidden() const;
    //runs code related to ending the game
    void end_game();

private slots:
    //receiver the play time timer's signals
    void timer_callback();

private:
    //amount of cards in the playing field
    //must be an even number between 2 and 40
    const int CARD_COUNT = 40;
    //spacing amount between ui components
    const int GRID_SPACING = 6;

    const int TEXT_BROWSER_HEIGHT = 210;
    const QString PLAYER_IN_TURN = "Player in turn:\n";
    const QString PLAYER1_NAME = "Make";
    const QString PLAYER2_NAME = "Jorma";
    const QString PLAYER3_NAME = "Viliami";

    //vector to contain pointers for each cardbutton
    std::vector<CardButton*> cardbuttons_{};
    
    //ui components
    QWidget* central_widget_{};
    QWidget* grid_layout_widget_{};
    QTextBrowser* text_browser_{};
    QLabel* player_indicator_label_{};
    QGridLayout* grid_layout_{};
    QLCDNumber* lcd_number_{};
    
    //timer to handle counting game time
    QTimer timer_;
    //pointer to the game logic object, gets created in this class's constructor
    GameLogic* game_logic_{};

    //whether or not this class was initialized successfully
    bool successful_init_{};
    //amount of seconds passed in this game
    int timer_secs_;

    //initializes most of the widgets
    void init_widgets();

    /**
     * Initializes card buttons.
     *
     * \param card_rows UInt amount of rows in the playing field
     * \param card_columns UInt amount of columns in the playing field
     */
    void init_cardbuttons(unsigned card_rows, unsigned card_columns);


    /**
     * Initializes widget sizes and positions based off the playing field size.
     *
     * \param card_rows UInt amount of rows in the playing field
     * \param card_columns UInt amount of columns in the playing field
     */
    void init_widget_sizes(unsigned card_rows, unsigned card_columns);
};

#endif // MAINWINDOW_HH
