#ifndef CARDBUTTON_HH
#define CARDBUTTON_HH

#include "utils.hh"
#include <QObject>
#include <QPushButton>
#include <QVariant>
#include <QStyle>

//constants for sizes
const int ICON_WIDTH = 100;
const int ICON_HEIGHT = 100;

const int CARDBUTTON_WIDTH = 110;
const int CARDBUTTON_HEIGHT = 110;

//css styles for card buttons in different states
const QString STYLE_SHEET = ""
    "/* Base style for all QPushButtons */"
    "QPushButton {"
    "	border-radius: 10px;"
    "}"
    ""
    "/* Styles for different states */"
    "QPushButton[state='default'] {"
    "    background-color: transparent;"
    "    border: 1px solid lightblue;"
    "}"
    "QPushButton[state='turned'] {"
    "    background-color: rgba(0, 255, 0, 150);"
    "    border: 1px solid green"
    "}"
    "QPushButton[state='turned_no_pair'] {"
    "    background-color: rgba(255, 0, 0, 150);"
    "    border: 1px solid red;"
    "}"
    "QPushButton[state='disabled'] {"
    "    background-color: transparent;"
    "    border: 1px solid lightblue;"
    "}"
    ""
    "/* Hover styles for different states */"
    "QPushButton[state='default']:hover {"
    "    background-color: rgba(0, 247, 255, 60);"
    "}"
    "QPushButton[state='disabled']:hover {"
    "    background-color: rgba(255, 0, 0, 60);"
    "    border: 1px solid red;"
    "}"
    ""
    "/* Pressed styles for different states */"
    "QPushButton[state='default']:pressed {"
    "    background: rgba(0, 247, 255, 100);"
    "}";

//QVariants for the above css property values
const QVariant DEFAULT_STATE = QVariant("default");
const QVariant TURNED_STATE = QVariant("turned");
const QVariant TURNED_NO_PAIR_STATE = QVariant("turned_no_pair");
const QVariant DISABLED_STATE = QVariant("disabled");

class CardButton : public QPushButton
{
    Q_OBJECT

public:
    explicit CardButton(int icon, QWidget* parent = Q_NULLPTR);
    void turn();
    void set_disabled(bool change_style_state = true);
    void set_enabled();
    void set_turned_no_pair();
    bool get_turned_state() const;

signals:
    void cardbutton_clicked(int);

private slots:
    void handle_click();

private:
    int icon_;
    bool turned_{};

    /**
     * Sets the specified style state to this button.
     *
     * \param state QVariant state
     */
    void set_style_state(const QVariant& state);
};

#endif // CARDBUTTON_HH
