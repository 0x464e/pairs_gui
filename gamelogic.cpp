#include "gamelogic.hh"
#include "mainwindow.hh"

GameLogic::GameLogic(std::vector<Player*> players, QWidget* parent) :
    QObject(parent), players_(std::move(players)),
    player_count_(players_.size()), turned_card_icon_(utils::none)
{
    //no need to pass in the same thing multiple times, this cast is
    //guaranteed to be safe when this object is MainWindow's child
    mainwindow_ = qobject_cast<MainWindow*>(parent);
}

GameLogic::~GameLogic()
{
    //deallocate each player object
    for (const auto& player : players_)
    {
        delete player;
    }
}

void GameLogic::start_game()
{
    //get a random player playing order by random shuffling the elements with 
    //a mersenne twister engine seeded with a true random number from 
    //std::random_device (if supported)
    std::shuffle(players_.begin(), players_.end(), 
        std::mt19937(std::random_device()()));
    set_next_player();
    mainwindow_->append_to_text_browser("Welcome to Animals Memory Game!\n"
                                        + player_in_turn_->get_name() 
                                        + " starts the game.\n"
                                        "---");
}

void GameLogic::handle_cardbutton_click(const int icon)
{
    //safe cast, this signal is only received from a CardButton
    const auto button = qobject_cast<CardButton*>(sender());
    turn_card(button, icon);
}

void GameLogic::turn_card(CardButton* button, const int icon)
{
    //if there is currently a card turned
    if (turned_card_)
    {
        print_log(icon);
        //if the turned card's icon is the same as 
        //the card that's about to be turned
        if (turned_card_icon_ == icon)
        {
            player_in_turn_->add_pair();
            button->turn();

            //invoke a lambda after PAIR_VIEW_TIME ms has passed
            //gives the players PAIR_VIEW_TIME amount of time to 
            //see the turned card pair
            QTimer::singleShot(PAIR_VIEW_TIME, [this, button]
            {
                delayed_card_handling(button);
            });
        }
        //if the turned card pair wasn't a matching pair
        else
        {
            button->turn();
            turned_card_->set_turned_no_pair_state();
            button->set_turned_no_pair_state();

            QTimer::singleShot(PAIR_VIEW_TIME, [this]
            {
                delayed_card_handling();
            });
        }
        //disables all cards for PAIR_VIEW_TIME ms
        //note that this runs before restore_all_cards() does in the lambda
        mainwindow_->disable_all_cards();
        turned_card_icon_ = utils::none;
    }
    else
    {
        //if this is the first card being turned, nothing special needs doing
        button->turn();
        turned_card_icon_ = icon;
        turned_card_ = button;
    }
}

void GameLogic::delayed_card_handling(CardButton* button)
{
    //if the button parameter was specified, this method is handling
    //a matching pair being turned
    if (button)
    {
        //hide the matching pair
        turned_card_->hide();
        button->hide();
    }
    else
    {
        //change turns if there was no matching pair
        set_next_player();
    }
    
    mainwindow_->restore_all_cards();
    turned_card_ = nullptr;
    check_game_over();

    //turn continuation message should only be appended if the game didn't end
    //and this method is handling a matching pair being turned
    if (!game_over_ && button)
    {
        mainwindow_->append_to_text_browser(
            player_in_turn_->get_name() + " continues their turn...");
    }
}

void GameLogic::set_next_player()
{
    if (game_over_) 
    {
        return;
    }
    //once each player has had their turn, get back to the first player
    //with modulo player count
    player_in_turn_ = players_.at(turn_number_++ % player_count_);

    //update player label
    const auto name = player_in_turn_->get_name();
    mainwindow_->set_player_in_turn(name);

    //on the very first turn, just the welcome message suffices
    if (turn_number_ != 1)
    {
        mainwindow_->append_to_text_browser(name + " takes the turn...");
    }
}

void GameLogic::print_log(const int icon) const
{
    const auto name = player_in_turn_->get_name();

    //add one because the change in pair count 
    //hasn't effect yet when this runs
    const auto pairs = player_in_turn_->get_pairs() + 1;

    //ternarys are beautiful, you're wrong if you think otherwise :p
    mainwindow_->append_to_text_browser(name + " turns their second card...\n" 
        //check if it's a pair
        + (turned_card_icon_ == icon ?
                utils::icon_name_to_plural(icon) + "!\n" + name + " now has " 
                + QString::number(pairs) + " pair" + (pairs > 1 ? "s" : "") + "."
            : 
                "No pair!\n---"));
}

void GameLogic::check_game_over()
{
    const auto game_over = mainwindow_->all_buttons_hidden();
    if (game_over)
    {
        end_game();
    }
}

void GameLogic::end_game()
{
    game_over_ = true;
    const auto winner_or_tied_players = get_winner_or_tied_players();
    const auto tie = winner_or_tied_players.size() > 1;

    //amount of pairs the winner (or tied players) have
    //safe access because there will always be at least one winner
    const auto pairs = winner_or_tied_players.at(0)->get_pairs();

    mainwindow_->append_to_text_browser("---\nGame Over!");


    if (tie)
    {
        //print the tied players
        const auto names = utils::player_vector_to_names(winner_or_tied_players);
        mainwindow_->append_to_text_browser(
            "It's a tie between " + names + " with " + QString::number(pairs) +
            " pair" + (pairs > 1 ? "s" : "") + "!");
    }
    else
    {
        //print the winner
        mainwindow_->append_to_text_browser(
            winner_or_tied_players.at(0)->get_name() + " wins with " 
            + QString::number(pairs) + " pair" + (pairs > 1 ? "s" : "") + "!");
    }

    mainwindow_->end_game();
}

std::vector<Player*> GameLogic::get_winner_or_tied_players()
{
    //sort by descending using a custom comparator lambda
    std::sort(players_.begin(), players_.end(),
              [](const auto& player1, const auto& player2)
              {
                  return player1->get_pairs() > player2->get_pairs();
              });

    std::vector<Player*> winner_or_tied_players = {};
    auto previous_score = 0u;

    for (const auto& player : players_)
    {
        const auto score = player->get_pairs();

        //scores are sorted by descending, so once the current score
        //is smaller than the previous score, we're done
        if (score >= previous_score)
        {
            previous_score = score;
            winner_or_tied_players.push_back(player);
        }
        else
        {
            break;
        }
    }

    return winner_or_tied_players;
}
