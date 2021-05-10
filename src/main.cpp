/* Animals Memory Game
*
* Desc:
* Animals memory game. This program creates a memory game, where a desired
* amount of players compete against each other in a classic card flipping 
* memory game. The cards have images of animals, find a pair to score a point.
* 
* The game starts off by randomizing the used cards and player order. The used
* rng is seeded by a true random number from std::random_device (if supported).
* There can be any even number of cards between two and 40. The upper limit of 
* 40 only comes from the amount of animal icons (20) the program has. 
* The playing field is randomized so that the row and column count are as near
* to each other as possible.
*
* Each round the player in turn turns two cards (by clicking on them). 
* Everyone can see the cards, and should look at them trying to keep in mind
* where each card is.
* If the player got a matching card pair, the card pair is removed from the 
* playing field, the player scores a point, and they get to continue their turn. 
* Otherwise, the cards get turned backside up again and the turn goes over to 
* the next player.
* The large textbox acts as a log which tells everything relevant that's 
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
* Notes about the program and it's implementation:
* The main idea when creating the program was possible future expandability.
* I tried to make everything with the thought in mind that it'd be easy to
* expand upon in the future. E.g the game will work with any amount of players
* even though as I'm writing this I still don't know if I'm going to bother to
* implement the ability to select the player count. (It'll be listed in the 
* extras below if I did bother to implement it)
* 
* Using a custom signal for passing the icon in my CardButton class may seem 
* redundant when I could just as well implement a "get_icon()" method to the
* class. But I wanted to try out emitting custom signals with arguments in Qt
* and it works out pretty well. Was a nice learning exercise.
* 
* Some design choices require C++14 features, but in the course materials C++14
* was stated as being okay, so it should be fine, I hope. I would've wanted to
* use even more modern C++ features for some design choices, but wasn't sure if
* I was allowed.***REMOVED***
*/

#include "mainwindow.hh"
#include <QApplication>
#include <QWidget>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //check if initialization failed
    if (w.init_failed())
    {
        QMessageBox msg_box;
        msg_box.setText("Card amount must be an even number between 2 and 40."
        "\nThe application will quit now.");
        msg_box.exec();
        QApplication::quit();
        return EXIT_FAILURE;
    }

    w.show();
    return QApplication::exec();
}
