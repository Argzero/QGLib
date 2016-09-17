#ifndef QGLTEXT_H
#define QGLTEXT_H
#include <string>
#include "../qglobject.h"
#include "../../utils/qglmath.h"

using namespace std;

// EDIT THIS CLASS TO REFLECT YOUR DEFAULT FONT WHERE "SEGOE UI" IS SPECIFIED
// NOTE: Segoe UI is a nice font :)
class QGLText : public QGLObject
{
public:
    // Constructors
    QGLText(string _font = "Segoe UI");
    QGLText(QGLObject *_parent = NULL, Vector3 _pos = Vector3::Zero, string _text = "", int _size = 18, string _font = "Segoe UI", QColor _color = Qt::red, QGLObject::ALIGN _align = QGLObject::CENTER_MID, Vector3 _rot = Vector3(1,1,1), Vector3 _scale = Vector3(1,1,1));
    ~QGLText();

    // Functions
    virtual void Update();
    virtual void Draw(QPainter *p);

    // Variables
    string text;
    string font;
    float width;
    float height;
    int size; // Font-size
    QColor color;
};
#endif // QGLTEXT_H
