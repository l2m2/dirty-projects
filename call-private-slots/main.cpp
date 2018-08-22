#include <QCoreApplication>
#include <iostream>

class Test: public QObject {
    Q_OBJECT
public:
    Test(QObject *parent = nullptr) : QObject(parent) {}
private slots:
    void func() {
        std::cout << __func__ << std::endl;
    }
};

#include "main.moc"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Test t;
    QMetaObject::invokeMethod(&t, "func");

    return a.exec();
}

