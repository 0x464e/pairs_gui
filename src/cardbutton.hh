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

const QString STYLE_SHEET_TURNED = ""
    "QPushButton {"
    "    background-color: rgba(0, 255, 0, 30);"
    "    border: 1px solid green;"
    "    border-radius: 10px;"
    "}";

class CardButton : public QPushButton
{
    Q_OBJECT

public:
    explicit CardButton(int icon, QWidget* parent = Q_NULLPTR);
    void turn();

signals:
    void cardbutton_clicked(int);

private slots:
    void handle_click();

private:
    int icon_;
    bool turned_{};
};

#endif // CARDBUTTON_HH
