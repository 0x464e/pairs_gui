#include "player.hh"

Player::Player(QString name) :
    name_(std::move(name)), pairs_(0)
{

}


QString Player::get_name() const
{
    return name_;
}
