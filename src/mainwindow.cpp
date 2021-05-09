#include "mainwindow.hh"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), game_logic_(this)
{
    auto card_rows = 1u;
    auto card_columns = 1u;

    utils::calculate_factors(CARD_COUNT, card_rows, card_columns);

    //first tests for adding buttons
    this->setFixedSize(card_columns * 110 + 300, card_rows * 110 + 300);

    central_widget_ = new QWidget(this);
    grid_layout_widget_ = new QWidget(central_widget_);
    grid_layout_ = new QGridLayout(grid_layout_widget_);
    grid_layout_->setSizeConstraint(QLayout::SetFixedSize);

    const auto icons = utils::get_random_card_icons(CARD_COUNT);
    auto i = 0;

    for (auto row = 0u; row < card_rows; row++)
    {
        for (auto col = 0u; col < card_columns; col++)
        {
            auto button = new CardButton(icons.at(i++), 
                qobject_cast<QWidget*>(grid_layout_));
            buttons_.push_back(button);
            connect(button, &CardButton::cardbutton_clicked, &game_logic_, 
                &game_logic::handle_click);
            grid_layout_->addWidget(button, row, col);
        }
    }
    
    this->setCentralWidget(central_widget_);
}

MainWindow::~MainWindow()
= default;
