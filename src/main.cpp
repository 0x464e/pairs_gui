#include "mainwindow.hh"
#include <QApplication>
#include <QWidget>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //check if initialization failed
    if (w.init_failed())
    {
        QMessageBox msg_box;
        msg_box.setText("Card amount must be an even number between 2 and 40."
        "\nThe application will quit now.");
        msg_box.exec();
        QApplication::quit();
        return EXIT_FAILURE;
    }

    w.show();
    return QApplication::exec();
}
