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
    const unsigned PAIR_VIEW_TIME = 500;

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
    bool game_over_;

    void turn_card(CardButton* button, int icon);

    //Sets the next player's turn.
    void set_next_player();

    void print_log(int icon) const;

    void check_game_over();

    void end_game();

    /**
     * Handles cards being hidden, or turned back after the specified viewing
     * time of cards has passed.
     *
     * \param button CardButton pointer, default to nullptr.\n
     * If specified, this method is handling a matching pair being turned.
     */
    void delayed_card_handling(CardButton* button = nullptr);

    /**
     * Gets the winner of the game, or if it was a tie between one or more players,
     * all the tied players are returned.\n
     * The returned vector will only contain one player if there was no tie.
     *
     * \return vector of Player object pointers
     */
    std::vector<Player*> get_winner_or_tied_players();
};

#endif // GAME_LOGIC_HH
