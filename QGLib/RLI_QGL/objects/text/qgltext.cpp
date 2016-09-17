#include <QDebug>

#include "qglwindow.h"
#include "qgltext.h"
#include "../../utils/qglconstants.hpp"

using namespace QGLConstants;

QGLText::QGLText(string _font)
    :QGLObject(TEXT, NULL, Vector3::Zero, Vector3(1,1,1), Vector3(1,1,1), CENTER_MID)
{
    text = "";
    size = 18;
    color = Qt::red;
    font = _font;
    QFontMetrics fm(QFont(QString::fromStdString(this->font), this->size));
    int pixelWidth = fm.width(QString::fromStdString(this->text));
    int pixelHeight = fm.height();
    width = pixelWidth;
    height = pixelHeight;
    if(SHOW_CONSTRUCTION)
        qDebug("QGLText Created");
}

QGLText::QGLText(QGLObject *_parent, Vector3 _pos, string _text, int _size, string _font, QColor _color, ALIGN _align, Vector3 _scale, Vector3 _rot)
    :QGLObject(TEXT, _parent, _pos, _rot, _scale, _align)
{
    text = _text;
    size = _size;
    color = _color;
    font = _font;
    QFontMetrics fm(QFont(QString::fromStdString(this->font), this->size));
    int pixelWidth = fm.width(QString::fromStdString(this->text));
    int pixelHeight = fm.height();
    width = pixelWidth;
    height = pixelHeight;
    if(SHOW_CONSTRUCTION)
        qDebug("QGLText Created");
}

QGLText::~QGLText()
{
    if(SHOW_DESTRUCTION)
        qDebug("~Text");
}

void QGLText::Update()
{
    QGLObject::Update();
}

/*TODO: Make work with multiple fonts*/
void QGLText::Draw(QPainter* p)
{
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    if(QGLConstants::SHOW_OBJ_SCREEN_POS)
        qDebug() << "QGLText @ " << GetPosition().ToString();
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

    QFontMetrics fm(QFont(QString::fromStdString(this->font), this->size));
    int pixelWidth = fm.width(QString::fromStdString(this->text));
    int pixelHeight = fm.height();
    width = pixelWidth;
    height = pixelHeight;

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
    p->setFont(QFont(QString::fromStdString(font), this->size));
    p->drawText(textPosX + xOff,
                textPosY + yOff, QString::fromStdString(this->text));
    p->endNativePainting();
    QGLObject::Draw(p);
}
