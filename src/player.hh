#ifndef PLAYER_HH
#define PLAYER_HH

#include <string>
#include <QString>

class Player
{
public:
    explicit Player(QString name);
    QString get_name() const;

private:
    QString name_;
    int pairs_;
};

#endif // PLAYER_HH
