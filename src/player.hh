/* Class Player
 * ----------
 * COMP.CS.110 SPRING 2021
 * ----------
 * Models a player for the game.
 * */

#ifndef PLAYER_HH
#define PLAYER_HH

#include <string>
#include <QString>

class Player
{
public:
    explicit Player(QString name);

    /**
     * Gets this player's name.
     * 
     * \return QStrings player name
     */
    QString get_name() const;

    /**
     * Increments this player's pair count by one.
     */
    void add_pair();

    /**
     * Returns the amount of pairs this player has.
     *
     * \return int number of pairs
     */
    unsigned get_pairs() const;

private:
    QString name_;
    int pairs_{};
};

#endif // PLAYER_HH
