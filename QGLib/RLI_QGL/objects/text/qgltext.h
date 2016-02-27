#ifndef QGLTEXT_H
#define QGLTEXT_H
#include <string>

#include "../qglobject.h"
#include "../../utils/qglmath.h"

using namespace std;

/*TODO: Make work with multiple fonts*/
class QGLText : public QGLObject
{
public:
    // Constructors
    QGLText();
    QGLText(QGLObject *_parent = NULL, Vector3 _pos = Vector3::Zero, string _text = "", int _size = 18, QColor _color = Qt::red, ALIGN _align = CENTER_MID);
    ~QGLText();

    // Functions
    virtual void update();
    virtual void draw(QPainter *p);
    void contains(Vector2 point);

    // Variables
    string text;
    int size; // Font-size
    QColor color;
};
#endif // QGLTEXT_H
