#include "Window.h"
#include "qapplication.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Window *window = new Window();
    delete window;
    return app.exec();
}
