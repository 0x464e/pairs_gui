#ifndef GAME_LOGIC_HH
#define GAME_LOGIC_HH

#include "cardbutton.hh"
#include "player.hh"
#include "utils.hh"
#include <QObject>
#include <QTextBrowser>
#include <random>
#include <QTimer>

//forward declare MainWindow to avoid circular dependency
class MainWindow;

class GameLogic : public QObject
{
Q_OBJECT

public:
    /**
     * Constructor. Receives the players vector with move semantics,
     * sets the parent for this object, and initializes the private mainwindow_
     * variable by casting from the parent pointer.
     *
     * \param players vector of player object pointers
     * \param parent QWidget pointer, pointer to the parent MainWindow object
     */
    explicit GameLogic(std::vector<Player*> players, QWidget* parent = Q_NULLPTR);
    ~GameLogic();
    void start_game();

public slots:
    void handle_cardbutton_click(int icon);

private:
    //how long card pair is visible for after being turned (in ms)
    const int PAIR_VIEW_TIME = 3000;

    //players in the game
    std::vector<Player*> players_;
    //which player is in turn right now
    Player* player_in_turn_;
    //pointer to the MainWindow object to access methods there
    MainWindow* mainwindow_;
    //how many turns the game has gone on for
    int turn_number_;
    size_t player_count_;
    //which icon the turned card has right now
    //if there is no turned card, it's none (0)
    int turned_card_icon_;
    //CardButton pointer for which card is turned right now
    CardButton* turned_card_;
    CardButton* other_button_;
    int value1_ = 1;

    //Sets the next player's turn.
    void set_next_player();
};

#endif // GAME_LOGIC_HH
