#include <QApplication>
#include <QPushButton>
#include <QTime>

int main(int argc, char *argv[]) {
    QApplication application(argc, argv);

    QPushButton button("Hello world!");
    button.show();

    return application.exec();
}
