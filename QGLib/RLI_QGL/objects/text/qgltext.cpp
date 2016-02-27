#include "qgltext.h"
#include "../../qglconstants.hpp"

using namespace QGLConstants;

QGLText::QGLText()
    :QGLObject(TEXT, NULL, Vector3::Zero, CENTER_MID)
{
    text = "";
    size = 18;
    color = Qt::red;
    if(SHOW_DEBUG)
        qDebug("QGLText Created.");
}

QGLText::QGLText(QGLObject *_parent, Vector3 _pos, string _text, int _size, QColor _color, ALIGN _align)
    :QGLObject(TEXT, _parent, _pos, _align)
{
    text = _text;
    size = _size;
    color = _color;
}

QGLText::~QGLText()
{
    if(SHOW_DEBUG)
        qDebug("~Text");
}

void QGLText::update()
{
    QGLObject::update();
}

void QGLText::contains(Vector2 point)
{
// NEVER COLLIDES UNLESS YOU WANT IT TO [Why would you ever want this?]
}

/*TODO: Make work with multiple fonts*/
void QGLText::draw(QPainter* p)
{
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);

    Vector3 pos = GetPosition();
    pos.Z = 0; // Z NOT YET SUPPORTED!!!

    // Identify x and y locations to render text within widget
    int height = window->height();

    GLdouble model[4][4], proj[4][4];
    GLint view[4];
    glGetDoublev(GL_MODELVIEW_MATRIX, &model[0][0]);
    glGetDoublev(GL_PROJECTION_MATRIX, &proj[0][0]);
    glGetIntegerv(GL_VIEWPORT, &view[0]);

    GLdouble textPosX = 0, textPosY = 0, textPosZ = 0;
    QGLMath::project(pos.X, pos.Y, pos.Z,
            &model[0][0], &proj[0][0], &view[0],
            &textPosX, &textPosY, &textPosZ);
    textPosY = height - textPosY; // y is inverted

    QFontMetrics fm(QFont("Segoe UI", this->size));
    int pixelWidth = fm.width(QString::fromStdString(this->text));
    int pixelHeight = fm.height();
    int xOff=0;
    int yOff=0;

    switch(this->alignment)
    {
    case CENTER_MID:
        xOff-=pixelWidth/2;
        yOff+=pixelHeight/2;
        break;
    case CENTER_TOP:
        xOff-=pixelWidth/2;
        yOff+=pixelHeight/2;
        break;
    case CENTER_BOTTOM:
        xOff-=pixelWidth/2;
        break;
    case LEFT_MID:
        yOff+=pixelHeight/2;
        break;
    case LEFT_TOP:
        yOff+=pixelHeight;
        break;
    case LEFT_BOTTOM:
        break;
    case RIGHT_MID:
        xOff-=pixelWidth;
        yOff+=pixelHeight/2;
        break;
    case RIGHT_TOP:
        xOff-=pixelWidth;
        yOff+=pixelHeight;
        break;
    case RIGHT_BOTTOM:
        xOff-=pixelWidth;
        break;
    }

    // Render text
    p->beginNativePainting();
    p->setPen(this->color);
    p->setFont(QFont("Segoe UI", this->size));
    p->drawText(textPosX + xOff,
                textPosY + yOff, QString::fromStdString(this->text));
    p->endNativePainting();
    QGLObject::draw(p);
}
