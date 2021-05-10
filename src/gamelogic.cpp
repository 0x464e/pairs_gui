#include "gamelogic.hh"
#include "mainwindow.hh"

GameLogic::GameLogic(std::vector<Player*> players, QWidget* parent)
    : QObject(parent), players_(std::move(players)), player_in_turn_(nullptr),
      turn_number_(0), player_count_(players_.size()),
      turned_card_icon_(utils::none), turned_card_(nullptr)
{
    //no need to pass in the same thing multiple times, this cast is
    //guaranteed to be safe when this object is MainWindow's child
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
    std::shuffle(players_.begin(), players_.end(), 
        std::mt19937(std::random_device()()));
    set_next_player();
    const auto name = player_in_turn_->get_name();
    mainwindow_->set_player_in_turn(name);
    mainwindow_->append_to_text_browser(name + " starts the game!");
}

void GameLogic::handle_cardbutton_click(const int icon)
{
    //safe cast, this signal is only received from a CardButton
    const auto button = qobject_cast<CardButton*>(sender());

    //if there is currently a card turned
    if(turned_card_)
    {
        if(turned_card_icon_ == icon)
        {
            player_in_turn_->add_pair();
            button->turn();

            QTimer::singleShot(PAIR_VIEW_TIME, [this, button]
            {
                turned_card_->hide();
                button->hide();
                turned_card_ = nullptr;
                mainwindow_->restore_all_cards();
            });
        }
        else
        {
            button->turn();
            turned_card_->set_turned_no_pair();
            button->set_turned_no_pair();
            QTimer::singleShot(PAIR_VIEW_TIME, [this]
            {
                mainwindow_->restore_all_cards();
                turned_card_ = nullptr;
            });
        }
        mainwindow_->disable_all_cards();
        turned_card_icon_ = utils::none;
    }
    else
    {
        button->turn();
        turned_card_icon_ = icon;
        turned_card_ = button;
    }
}

void GameLogic::set_next_player()
{
    //once each player has had their turn, get back to the first player
    //with modulo player count
    player_in_turn_ = players_.at(turn_number_++ % player_count_);
}
