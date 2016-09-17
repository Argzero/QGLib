#include "qglshape.h"
#include "../qglobject.h"
#include "../../utils/qglconstants.hpp"

using namespace QGLConstants;

QGLShape::QGLShape()
    : QGLObject(QGLObject::SHAPE)
{
    vertices = new QVector<Vector3>();
    wireframeThickness = 5.0;
    mouseEnabled = false;
    lit = false;
    if(SHOW_CONSTRUCTION)
        qDebug("QGLShape Created");
}

QGLShape::QGLShape(QGLObject *_parent, Vector3 _pos, bool _mouseEnable, QGLObject::ALIGN _align,
                   bool _wireframe, QColor _frameColor)
    : QGLObject(QGLObject::SHAPE, _parent, _pos, _align)
{
    parent = _parent;
    position = _pos;
    mouseEnabled = _mouseEnable;
    wireframe = _wireframe;
    fill = true;
    frameColor = _frameColor;
    wireframeThickness = 5.0;
    lit = false;
    if(SHOW_CONSTRUCTION)
        qDebug("QGLShape Created");
}

QGLShape::~QGLShape()
{
    delete vertices;
    delete colors;

    if(SHOW_DESTRUCTION)
        qDebug("~Shape");
}

void QGLShape::Update()
{
    QGLObject::Update();
}

void QGLShape::Draw(QPainter* p)
{
    QGLObject::Draw(p);
}
