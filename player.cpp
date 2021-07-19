#include "player.hh"

Player::Player(QString name) :
    name_(std::move(name))
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
