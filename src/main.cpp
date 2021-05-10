/* Animals Memory Game
* 
* Desc:
* Animals memory game. This program creates a memory game, where a desired
* amount of players compete against each other in a classic card flipping
* memory game. The cards have images of animals, find a pair to score a point.
*
* The game starts off by asking the desired amount of playing field cards and
* player names. After that, the used cards and player order are randomized.
* The used rng is seeded by a true random number from std::random_device.
* There can be any even number of cards between two and 40. The upper limit of
* 40 only comes from the amount of animal icons (20) the program has.
* The playing field is constructed so that the row and column count are as near
* to each other as possible.
*
* Each round the player in turn turns two cards (by clicking on them).
* Everyone can see the cards, and should look at them trying to keep in mind
* where each card is.
* If the player got a matching card pair, the card pair is removed from the
* playing field, the player scores a point, and they get to continue their turn.
* Otherwise, the cards get turned backside up again and the turn goes over to
* the next player.
* The large textbox acts as a log which tells everything relevant to what's
* happening in the game.
*
* Animal icons included in the game are as follows:
* bird, bunny, camel, cat, chicken, cow, dog, donkey, duck, elephant, flamingo,
* horse, lizard, llama, monke, panda, pig, rooster, sheep, and squirrel
*
* The games ends when the playing field is empty of cards. The program prints
* out the winner and their score (amount of card pairs collected), or in case
* of a tie, it prints out the names of the tied players and their score.
*
*
* Notes about the program and its implementation:
* The main idea when creating the program was possible future expandability.
* I tried to make everything with the thought in mind that it'd be easy to
* expand upon it in the future. E.g the game will work with any amount of players
* even though as I'm writing this, I still don't know if I'm going to bother to
* implement the ability to select the player count.
* Update: I added it last minute, everything went smoothly as expected.
*
* Using a custom signal for passing the icon in my CardButton class may seem
* redundant when I could just as well implement a "get_icon()" method to the
* class. But I wanted to try out emitting custom signals with arguments in Qt
* and it worked out quite well. Was a nice learning exercise.
*
* Some design choices require C++14 features, but in the course materials C++14
* was stated as being okay, so it should be fine, I hope. I would've wanted to
* use even more modern C++ features for some design choices, but wasn't sure if
* it was allowed.
*/

#include "mainwindow.hh"
#include "utils.hh"
#include <QApplication>
#include <QWidget>
#include <QMessageBox>
#include <QInputDialog>


const unsigned MAX_CARD_AMOUNT = 40;
const unsigned DEFAULT_CARD_AMOUNT = 30;

/**
 * Asks the user to input the desired amount of playing field cards with
 * a popup.
 * 
 * \param cards byref specified UInt for the card amount
 * \return bool true if valid card number & cancel wasn't pressed
 */
bool ask_card_amount(unsigned& cards)
{
    bool ok_button_pressed{};
    //dialog box to input desired amount of cards

    cards = QInputDialog::getInt(nullptr, "Enter Card Amount",
                                 "Enter an even amount of cards between 2 and 40:",
                                 DEFAULT_CARD_AMOUNT, 2, MAX_CARD_AMOUNT, 1,
                                 &ok_button_pressed);

    //ok pressed & divisible by two
    return ok_button_pressed && !(cards % 2);
}

/**
 * Asks for player names and creates Player objects based off it.
 * 
 * \return bool true for success
 */
bool ask_player_names(std::vector<Player*>& player_names)
{
    bool ok_button_pressed{};

    //dialog box to input desired player count
    const auto names = QInputDialog::getMultiLineText(
        nullptr, "Enter Player Names",
        "Enter player names separated with new lines.\nAmount of player "
        "names will be the amount of players the game has.\nDuplicate names"
        " work, but are not recommended", "Player1\nPlayer2\nPlayer3", 
        &ok_button_pressed);

    //if cancel was pressed
    if (!ok_button_pressed)
    {
        return false;
    }

    const auto names_vector = utils::split(names, '\n');
    //if less than two names were specified
    if (names_vector.size() < 2)
    {
        QMessageBox msg_box{};
        msg_box.setText("You must specify at least two players..\n"
            "The program will quit now.");
        msg_box.exec();
        return false;
    }

    //create players
    for (const auto& name : names_vector)
    {
        player_names.push_back(new Player(name));
    }

    return true;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    unsigned card_count{};
    std::vector<Player*> players{};
    bool player_names_ok{};

    //ask amount of cards and return whether or not it was a success
    const auto cards_ok = ask_card_amount(card_count);
    
    //if asking for cards failed, dont bother asking for player names
    if(!cards_ok)
    {
        QMessageBox msg_box{};
        msg_box.setText("Card amount must be an even number between 2 and 40."
            "\nThe application will quit now.");
        msg_box.exec();
    }
    else
    {
        player_names_ok = ask_player_names(players);
    }

    //quit if either failed
    if (!cards_ok || !player_names_ok)
    {
        QApplication::quit();
        return EXIT_FAILURE;
    }

    MainWindow w(card_count, players);

    w.show();
    return QApplication::exec();
}
