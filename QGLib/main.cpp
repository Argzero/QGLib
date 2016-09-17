#include <QApplication>
#include "mainwindow.h"

#include "RLI_QGL/global.cpp"
#include "RLI_QGL/qglwindow.h"
#include "RLI_QGL/objects/scenes/scenenode.h"
#include "RLI_QGL/objects/text/qgltext.h"

// THIS SHOWS HOW YOU WOULD MAKE AN APPLICATION IN QGLib
int main(int argc, char *argv[])
{
    // QSurfaceFormat::setDefaultFormat(); MAY BE NEEDED HERE FOR SOME FUNCTIONALITIES
    QApplication a(argc, argv);
    QGLWindow window;
    window.show();

    // DEFINE ALL FONTS IN THE PROGRAM -- CURRENTLY STATIC LOADING, NOT DYNAMIC LOADING
    QStringList list;
    list << "segoeui.ttf";
    list << "segoeuib.ttf";
    QGLGlobal::setUpFonts(list);

    // Making a Scene
    SceneNode* MainScene = new SceneNode(&window);
    QGLText* normal = new QGLText(MainScene,
                                  Vector3(window.width()/2,window.height()/2,0),
                                  "HELLO, WORLD!",
                                  18,
                                  "Segoe UI",
                                  Qt::red,
                                  QGLObject::CENTER_BOTTOM,
                                  Vector3(1,1,1),
                                  Vector3(1,1,1));
    QGLText* bold   = new QGLText(normal,
                                  Vector3(2,normal->height/2,0),
                                  "FOOBAR!",
                                  36,
                                  "Segoe UI Bold",
                                  Qt::white,
                                  QGLObject::CENTER_TOP);
    MainScene->QGLObject::AddChild(normal);

    window.AddScene(MainScene);
    window.start();
    return a.exec();
}
