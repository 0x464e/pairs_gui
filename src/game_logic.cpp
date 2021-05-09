#include "game_logic.hh"


game_logic::game_logic(QObject *parent)
    : QObject(parent)
{
}

game_logic::~game_logic()
= default;

void game_logic::handle_click(int icon)
{
    const auto button = qobject_cast<CardButton*>(sender());
    button->turn();
    //button->hide();
}
