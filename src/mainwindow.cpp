#include "mainwindow.hh"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), timer_(this), timer_secs_(1)
{
    //card row and column count, will be set byref by utils::calculate_factors
    auto card_rows = 1u;
    auto card_columns = 1u;

    //attempt to calculate factors for the specified card count
    successful_init_ = utils::calculate_factors(CARD_COUNT, card_rows,
                                                card_columns);

    //two players hardcoded, but everything is designed so that any amount
    //of players would work. player selection can easily be added later
    const std::vector<Player*> players = { new Player(PLAYER1_NAME), 
                                           new Player(PLAYER2_NAME) };
    game_logic_ = new GameLogic(players, this);

    //if an invalid card count was specified, no need to continue further
    if (!successful_init_)
    {
        return;
    }

    this->setWindowIcon(QIcon(":/icons/app_icon.ico"));

    init_widgets();
    init_cardbuttons(card_rows, card_columns);
    init_widget_sizes(card_rows, card_columns);

    timer_.start(1000);
    connect(&timer_, &QTimer::timeout, this, &MainWindow::timer_callback);
    game_logic_->start_game();
}

void MainWindow::init_widgets()
{
    central_widget_ = new QWidget(this);
    this->setCentralWidget(central_widget_);
    grid_layout_widget_ = new QWidget(central_widget_);
    grid_layout_ = new QGridLayout(grid_layout_widget_);
    text_browser_ = new QTextBrowser(grid_layout_widget_);
    player_indicator_label_ = new QLabel(PLAYER_IN_TURN, grid_layout_widget_);
    player_indicator_label_->setFont(QFont("Arial", 25, QFont::Bold));
    player_indicator_label_->setAlignment(Qt::AlignCenter);
    lcd_number_ = new QLCDNumber(5, grid_layout_widget_);
    lcd_number_->display("00:00");
    grid_layout_->setSizeConstraint(QLayout::SetFixedSize);
    grid_layout_->setSpacing(GRID_SPACING);
}

void MainWindow::init_cardbuttons(const unsigned card_rows,
                                  const unsigned card_columns)
{
    //gets the correct amount of randomized card icons
    const auto icons = utils::get_random_card_icons(CARD_COUNT);

    //index to get icons from the above icon vector
    auto i = 0;

    //create and add a new button for each column in each row
    for (auto row = 0u; row < card_rows; row++)
    {
        for (auto col = 0u; col < card_columns; col++)
        {
            const auto button = new CardButton(icons.at(i++), grid_layout_widget_);
            cardbuttons_.push_back(button);
            connect(button, &CardButton::cardbutton_clicked, game_logic_,
                    &GameLogic::handle_click);
            grid_layout_->addWidget(button, row, col);
        }
    }

}

void MainWindow::init_widget_sizes(const unsigned card_rows,
                                   const unsigned card_columns)
{
    //height is same in both circumstances
    const auto height = card_rows * (CARDBUTTON_HEIGHT + GRID_SPACING) 
        + TEXT_BROWSER_HEIGHT;
    auto width = 0;

    //if there are over four columns, the label & timer can 
    //fit next to the text browser
    if (card_columns > 4)
    {
        grid_layout_->addWidget(text_browser_, card_rows, 0, 2,
                                card_columns - 2);
        grid_layout_->addWidget(player_indicator_label_, card_rows,
                                card_columns - 2, 1, 2);
        grid_layout_->addWidget(lcd_number_, card_rows + 1, 
                                card_columns - 2, 1, 2);

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

bool MainWindow::init_failed() const
{
    return !successful_init_;
}

void MainWindow::set_player_in_turn(const QString& player) const
{
    player_indicator_label_->setText(PLAYER_IN_TURN + player);
}

void MainWindow::append_to_text_browser(const QString& text) const
{
    text_browser_->append(text);
}

MainWindow::~MainWindow()
= default;

void MainWindow::timer_callback()
{
    lcd_number_->display(utils::seconds_to_time_string(timer_secs_++));
}
