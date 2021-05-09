#include "cardbutton.hh"

CardButton::CardButton(const int value, QWidget* parent)
    : QPushButton(parent), icon_(value)
{
    connect(this, &QPushButton::clicked, this, &CardButton::handle_click);
    this->setStyleSheet(STYLE_SHEET_DEFAULT);
    this->setIcon(get_icon(utils::icons::back));
    this->setIconSize(QSize(ICON_WIDTH, ICON_HEIGHT));
    this->setCursor(Qt::PointingHandCursor);
    auto size_policy = this->sizePolicy();
    size_policy.setRetainSizeWhenHidden(true);
    this->setSizePolicy(size_policy);
}

void CardButton::handle_click()
{
    emit cardbutton_clicked(icon_);
}
