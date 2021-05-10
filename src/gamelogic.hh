#ifndef GAME_LOGIC_HH
#define GAME_LOGIC_HH

#include "cardbutton.hh"
#include "player.hh"
#include <QObject>
#include <QTextBrowser>
#include <random>

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
    void handle_click(int icon);

private:
    std::vector<Player*> players_;
    Player* player_in_turn_;
    MainWindow* mainwindow_ = nullptr;
    int turn_number_;
    int player_count_;

    /**
     * Sets the next player's turn.
     */
    void set_next_player();
};

#endif // GAME_LOGIC_HH
