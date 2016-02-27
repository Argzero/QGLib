#include <QApplication>
#include <QFile>
#include <QMessageBox>

#include "mainwindow.h"
#include "RLI_QGL/scenes/scenenode.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SceneNode c;
    c.show();

    QStringList list;
    list << "segoeui.ttf"; // << "DejaVuSerif-Bold.ttf" << "DejaVuSerif-Italic.ttf" << "DejaVuSerif-BoldItalic.ttf";
    int fontID(-1);
    bool fontWarningShown(false);
    for (QStringList::const_iterator constIterator = list.constBegin(); constIterator != list.constEnd(); ++constIterator) {
        QFile res(":/RLI_QGL/fonts/" + *constIterator);
        if (res.open(QIODevice::ReadOnly) == false) {
            if (fontWarningShown == false) {
                QMessageBox::warning(0, "Application", (QString)"Can't LOAD" + QChar(0x00AB) + " Specified Font " + QChar(0x00BB) + ".");
                fontWarningShown = true;
            }
        } else {
            fontID = QFontDatabase::addApplicationFontFromData(res.readAll());
            if (fontID == -1 && fontWarningShown == false) {
                QMessageBox::warning(0, "Application", (QString)"Cant " + QChar(0x00AB) + " Specified Font" + QChar(0x00BB) + ".");
                fontWarningShown = true;
            }
        }
    }
    return a.exec();
}
