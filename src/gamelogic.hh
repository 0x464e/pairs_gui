#ifndef GAME_LOGIC_HH
#define GAME_LOGIC_HH

#include "cardbutton.hh"
#include <QObject>
#include <QTextBrowser>

class GameLogic : public QObject
{
	Q_OBJECT

public:
    explicit GameLogic(QObject* parent = Q_NULLPTR);
    ~GameLogic();

public slots:
    void handle_click(int icon);
};

#endif // GAME_LOGIC_HH
