#include "gamelogic.hh"
#include "mainwindow.hh"

GameLogic::GameLogic(std::vector<Player*> players, QWidget* parent)
    : QObject(parent), players_(std::move(players)), player_in_turn_(nullptr),
      turn_number_(0), player_count_(players_.size())

{
    //no need to pass in the same thing multiple times, this cast is
    //guaranteed to be safe
    mainwindow_ = qobject_cast<MainWindow*>(parent);
}

GameLogic::~GameLogic()
{
    //deallocate each player object
    for(const auto& player : players_)
    {
        delete player;
    }
}

void GameLogic::start_game()
{
    //get a random player playing order by random shuffling the elements with 
    //a mersenne twister engine seeded with a true random number number from 
    //std::random_device (if supported)
    std::shuffle(players_.begin(), players_.end(), std::mt19937(std::random_device()()));
    set_next_player();
    const auto name = player_in_turn_->get_name();
    mainwindow_->set_player_in_turn(name);
    mainwindow_->append_to_text_browser(name + " starts the game!");
}

void GameLogic::handle_click(int icon)
{
    const auto button = qobject_cast<CardButton*>(sender());
    button->turn();
}

void GameLogic::set_next_player()
{
    //once each player has had their turn, get back to the first player
    //with modulo player count
    player_in_turn_ = players_.at(turn_number_++ % player_count_);
}
