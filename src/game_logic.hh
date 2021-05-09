#pragma once

#include "cardbutton.hh"
#include <QObject>

class game_logic : public QObject
{
	Q_OBJECT

public:
    game_logic(QObject *parent);
    ~game_logic();

public slots:
    void handle_click(int icon);
};
