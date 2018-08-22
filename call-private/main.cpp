#include <QCoreApplication>
#include <iostream>

class Test {
private:
    virtual void func() {
        std::cout << __func__ << std::endl;
    }
    virtual void func2() {
        std::cout << __func__ << std::endl;
    }
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Test t;
    unsigned int v_table_addr = *((unsigned int *) &t);
    typedef void (*pFunc)(void *);
    pFunc func = (pFunc)(*((unsigned int *)v_table_addr));
    func(&t);
    pFunc func2 = (pFunc)(*((unsigned int *)(v_table_addr + 4)));
    func2(&t);

    return a.exec();
}
