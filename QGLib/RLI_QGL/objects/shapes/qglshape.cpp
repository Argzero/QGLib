#include "qglshape.h"
#include "../qglobject.h"
#include "../../qglconstants.hpp"

using namespace QGLConstants;

QGLShape::QGLShape()
    : QGLObject(QGLObject::SHAPE)
{
    vertices = new QVector<Vector3>();
    wireframeThickness = 5.0;
    lit = false;
    if(SHOW_DEBUG)
        qDebug("QGLShape Created.");
}

QGLShape::QGLShape(QGLObject *_parent, Vector3 _pos, QGLObject::ALIGN _align,
                   bool _wireframe, QColor _frameColor)
    : QGLObject(QGLObject::SHAPE, _parent, _pos, _align)
{
    parent = _parent;
    position = _pos;
    wireframe = _wireframe;
    fill = true;
    frameColor = _frameColor;
    wireframeThickness = 5.0;
    lit = false;
    if(SHOW_DEBUG)
        qDebug("QGLShape Created.");
}

QGLShape::~QGLShape()
{
    delete vertices;
    delete colors;

    if(SHOW_DEBUG)
        qDebug("~Shape");
}

void QGLShape::update()
{
    QGLObject::update();
}

void QGLShape::draw(QPainter* p)
{
    QGLObject::draw(p);
}
