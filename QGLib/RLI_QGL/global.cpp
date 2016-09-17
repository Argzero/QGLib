#include <QFile>
#include <QMessageBox>
#include <QString>
#include <QFontDatabase>

namespace QGLGlobal{
    void setUpFonts(QStringList list){
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
                    QMessageBox::warning(0, "Application", (QString)"Can't ADD" + QChar(0x00AB) + " Specified Font" + QChar(0x00BB) + ".");
                    fontWarningShown = true;
                }
            }
        }
    }
}
