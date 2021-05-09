#ifndef CARDBUTTON_HH
#define CARDBUTTON_HH

#include "utils.hh"
#include <QObject>
#include <QPushButton>

const int ICON_WIDTH = 100;
const int ICON_HEIGHT = 100;

const QString STYLE_SHEET_DEFAULT = ""
    "QPushButton {"
    "    background-color: transparent;"
    "    border: 1px solid lightblue;"
    "    border-radius: 10px;"
    "}"
    "QPushButton:hover {"
    "    background-color: rgba(0, 247, 255, 30)"
    "}"
    "QPushButton:pressed {"
    "    background: rgba(0, 247, 255, 80)"
    "}";

class CardButton : public QPushButton
{
    Q_OBJECT

public:
    explicit CardButton(int value, QWidget* parent = Q_NULLPTR);

signals:
    void cardbutton_clicked(int);

private slots:
    void handle_click();

private:
    int icon_;
    
};

#endif // CARDBUTTON_HH
