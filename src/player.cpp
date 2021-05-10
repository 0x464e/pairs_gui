#include "player.hh"

Player::Player(QString name) :
    name_(std::move(name)), pairs_(0)
{

}

QString Player::get_name() const
{
    return name_;
}

void Player::add_pair()
{
    pairs_++;
}

unsigned Player::get_pairs() const
{
    return pairs_;
}
