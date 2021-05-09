#include "mainwindow.hh"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), game_logic_(this)
{
    auto card_rows = 1u;
    auto card_columns = 1u;

    utils::calculate_factors(CARD_COUNT, card_rows, card_columns);

    this->setWindowIcon(QIcon(":/icons/app_icon.ico"));

    central_widget_ = new QWidget(this);
    this->setCentralWidget(central_widget_);
    grid_layout_widget_ = new QWidget(central_widget_);
    grid_layout_ = new QGridLayout(grid_layout_widget_);
    text_browser_ = new QTextBrowser(grid_layout_widget_);
    player_indicator_label_ = new QLabel(PLAYER_IN_TURN, grid_layout_widget_);
    player_indicator_label_->setFont(QFont("Arial", 25, QFont::Bold));
    player_indicator_label_->setAlignment(Qt::AlignCenter);
    lcd_number_ = new QLCDNumber(5, grid_layout_widget_);
    grid_layout_->setSizeConstraint(QLayout::SetFixedSize);
    grid_layout_->setSpacing(GRID_SPACING);

    const auto icons = utils::get_random_card_icons(CARD_COUNT);
    auto i = 0;

    for (auto row = 0u; row < card_rows; row++)
    {
        for (auto col = 0u; col < card_columns; col++)
        {
            const auto button = new CardButton(icons.at(i++), 
                grid_layout_widget_);
            connect(button, &CardButton::cardbutton_clicked, &game_logic_, 
                &GameLogic::handle_click);
            grid_layout_->addWidget(button, row, col);
        }
    }

    const auto height = card_rows * (CARDBUTTON_HEIGHT + GRID_SPACING)
        + TEXT_BROWSER_HEIGHT;
    auto width = 0;

    if(card_columns > 4)
    {
        grid_layout_->addWidget(text_browser_, 
            card_rows, 0, 2, card_columns-2);
        grid_layout_->addWidget(player_indicator_label_, 
            card_rows, card_columns - 2, 1, 2);
        grid_layout_->addWidget(lcd_number_, 
            card_rows + 1, card_columns - 2, 1, 2);

        width = card_columns * (CARDBUTTON_WIDTH + GRID_SPACING) 
            + 2 * GRID_SPACING;
    }
    else
    {
        grid_layout_->addWidget(text_browser_, 
            card_rows, 0, 2, card_columns);
        grid_layout_->addWidget(player_indicator_label_,
            0, card_columns, 1, 2);
        lcd_number_->setFixedSize(2 * CARDBUTTON_WIDTH, CARDBUTTON_HEIGHT);
        grid_layout_->addWidget(lcd_number_, 
            1, card_columns, 1, 2);

        width = (card_columns + 2) * (CARDBUTTON_WIDTH + GRID_SPACING)
            + 2 * GRID_SPACING;
    }

    this->setFixedSize(width, height);
}

MainWindow::~MainWindow()
= default;