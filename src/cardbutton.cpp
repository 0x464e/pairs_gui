#include "cardbutton.hh"

CardButton::CardButton(const int icon, QWidget* parent)
    : QPushButton(parent), icon_(icon)
{
    connect(this, &QPushButton::clicked, this, &CardButton::handle_click);
    this->setStyleSheet(STYLE_SHEET_DEFAULT);
    this->setIcon(get_icon(utils::back));
    this->setIconSize(QSize(ICON_WIDTH, ICON_HEIGHT));
    this->setCursor(Qt::PointingHandCursor);
    auto size_policy = this->sizePolicy();
    size_policy.setRetainSizeWhenHidden(true);
    this->setSizePolicy(size_policy);

    auto asdasd = turned_;
    auto asd = " ";
}

void CardButton::turn()
{
    if(turned_)
    {
        this->setCursor(Qt::PointingHandCursor);
        this->setIcon(get_icon(utils::back));
        this->setStyleSheet(STYLE_SHEET_DEFAULT);
        this->blockSignals(false);
    }
    else
    {
        this->setIcon(utils::get_icon(icon_));
        this->setCursor(Qt::ForbiddenCursor);
        this->setStyleSheet(STYLE_SHEET_TURNED);
        this->blockSignals(true);
    }
    turned_ = !turned_;
}

void CardButton::handle_click()
{
    emit cardbutton_clicked(icon_);
}
