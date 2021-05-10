/* Class CardButton
 * ----------
 * COMP.CS.110 SPRING 2021
 * ----------
 * Class for modeling a GUI button component for the playing field cards.
 * Derived from QPushButton
 * */

#ifndef CARDBUTTON_HH
#define CARDBUTTON_HH

#include "utils.hh"
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
    /**
     * Constructor. Creates a CardButton object for the playing field cards.
     *
     * \param icon int icon to give this card
     * \param parent QWidget* parent for this object, default to nullptr
     * \return CardButton object
     */
    explicit CardButton(int icon, QWidget* parent = Q_NULLPTR);
    //turns this card
    void turn();
    //sets this card as disabled, optionally don't change the style state
    void set_disabled(bool change_style_state = true);
    //enable this card
    void set_enabled();
    //set to a state where this card was turned around without a matching pair
    void set_turned_no_pair_state();
    //returns whether or not this card is turned, true if turned
    bool get_turned_state() const;

signals:
    //custom signal with an int parameter
    void cardbutton_clicked(int);

private slots:
    //handles the default click signal from a QPushButton
    void handle_click();

private:
    //this card's icon
    int icon_;
    //turned state, true for turned
    bool turned_{};

    /**
     * Sets the specified style state to this button.
     *
     * \param state QVariant state
     */
    void set_style_state(const QVariant& state);
};

#endif // CARDBUTTON_HH
