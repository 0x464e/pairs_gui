#include "cardbutton.hh"

CardButton::CardButton(const int icon, QWidget* parent)
    : QPushButton(parent), icon_(icon)
{
    connect(this, &QPushButton::clicked, this, &CardButton::handle_click);
    this->setProperty("state", DEFAULT_STATE);
    this->setStyleSheet(STYLE_SHEET);
    this->setIcon(get_icon(utils::back));
    this->setIconSize(QSize(ICON_WIDTH, ICON_HEIGHT));
    this->setCursor(Qt::PointingHandCursor);
    this->setFixedSize(CARDBUTTON_WIDTH, CARDBUTTON_HEIGHT);
    auto size_policy = this->sizePolicy();
    size_policy.setRetainSizeWhenHidden(true);
    this->setSizePolicy(size_policy);
    
}

void CardButton::turn()
{
    if (turned_)
    {
        //if card was already turned, it's being turned back
        this->setIcon(get_icon(utils::back));
        set_enabled();
    }
    else
    {
        this->setIcon(utils::get_icon(icon_));
        this->set_style_state(TURNED_STATE);
        set_disabled(false);
    }
    turned_ = !turned_;
}

void CardButton::set_disabled(const bool change_style_state)
{
    //optionally don't set the style state
    if (change_style_state)
    {
        this->set_style_state(DISABLED_STATE);
    }
    this->setCursor(Qt::ForbiddenCursor);
    //block signals so further presses of the button don't do anything
    this->blockSignals(true);
}

void CardButton::set_enabled()
{
    this->set_style_state(DEFAULT_STATE);
    this->setCursor(Qt::PointingHandCursor);
    this->blockSignals(false);
}

void CardButton::set_turned_no_pair_state()
{
    set_style_state(TURNED_NO_PAIR_STATE);
}

bool CardButton::get_turned_state() const
{
    return turned_;
}

void CardButton::handle_click()
{
    //emit custom signal with an argument
    emit cardbutton_clicked(icon_);
}

void CardButton::set_style_state(const QVariant& state)
{
    //style has to unpolished and polished for a property change to effect
    this->setProperty("state", state);
    this->style()->unpolish(this);
    this->style()->polish(this);
}
