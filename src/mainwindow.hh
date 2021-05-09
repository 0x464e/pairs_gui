#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include "cardbutton.hh"
#include "utils.hh"
#include <QMainWindow>
#include <QGridLayout>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void receive_click(int tbd);

private:
    //max 30
    const int CARD_COUNT = 30;
    QWidget* central_widget_;
    QWidget* grid_layout_widget_;
    QGridLayout* grid_layout_;
    std::vector<CardButton*> buttons_;
};
#endif // MAINWINDOW_HH
