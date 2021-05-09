#include "gamelogic.hh"
#include <QMainWindow>

GameLogic::GameLogic(QObject* parent)
    : QObject(parent)
{
}

GameLogic::~GameLogic()
= default;

void GameLogic::handle_click(int icon)
{
    const auto button = qobject_cast<CardButton*>(sender());
    button->turn();
}
