#include "qglquad.h"
#include "../../../qglwindow.h"
#include "../../../utils/qglmath.h"
#include "../../../utils/qglconstants.hpp"

using namespace QGLConstants;

QGLQuad::QGLQuad() :
    QGLShape(NULL, Vector3::Zero, false, CENTER_MID, false, Qt::black)
{
    shape = QUAD;

    if(SHOW_CONSTRUCTION)
        qDebug("QGLQuad Created");
}

QGLQuad::QGLQuad(QGLObject *_parent, Vector3 _pos,
                 QVector<Vector3> *_vertices, QColor _color, bool _mouseEnable,
                 bool _wireframe, QColor _frameColor,
                 RENDER_TYPE _renderType,
                 FRAME_TYPE _frameType):
    QGLShape(_parent, _pos, false, CENTER_MID, _wireframe, _frameColor)
{
    shape = QUAD;

    vertices = new QVector<Vector3>();
    colors = new QVector<QColor>();
    for(int i = 0; i<4; i++){
        vertices -> append(_vertices->at(i));
        colors   -> append(_color);
    }

    if(_renderType == FOUR_TRIANGLES && (_vertices->length()==5))
        centerPoint = _vertices->at(4);
    else{
        centerPoint = QGLMath::AvgVector3(*_vertices);
    }
    colors -> append(_color);
    frameType = _frameType;
    renderType = _renderType;

    if(SHOW_CONSTRUCTION)
        qDebug("QGLQuad Created");
}

QGLQuad::QGLQuad(QGLObject *_parent, Vector3 _pos,
                 QVector<Vector3> *_vertices, QVector<QColor> *_colors, bool _mouseEnable,
                 bool _wireframe, QColor _frameColor,
                 RENDER_TYPE _renderType,
                 FRAME_TYPE _frameType):
    QGLShape(_parent, _pos, false, CENTER_MID, _wireframe, _frameColor)
{
    shape = QUAD;

    vertices = new QVector<Vector3>();
    colors = new QVector<QColor>();
    if(_colors->length()!=4 && (_renderType != FOUR_TRIANGLES) && SHOW_DEBUG)
    {
        throw("TWO_TRIANGLES construction requires exactly four colors.\nFOUR_TRIANGLES construction requires exactly five colors.\nThe last color is the centerpoint color");
    }

    for(int i = 0; i<4; i++)
    {
        vertices -> append(_vertices->at(i));
        colors -> append(_colors->at(i));
    }

    if(_renderType == FOUR_TRIANGLES && (_vertices->length()==5))
        centerPoint = _vertices->at(4);
    else{
        centerPoint = QGLMath::AvgVector3(*_vertices);
    }
    colors -> append(_colors->at(4));
    frameType = _frameType;
    renderType = _renderType;

    if(SHOW_CONSTRUCTION)
        qDebug("QGLQuad Created");
}

QGLQuad::~QGLQuad()
{
    if(SHOW_DESTRUCTION)
        qDebug("~QGLQuad");
}

void QGLQuad::Update()
{
    QGLShape::Update();
}

void QGLQuad::Draw(QPainter *p)
{
    // Modest quads
    p->beginNativePainting();
    if(lit)
    {
        return;
    }
    if(fill)
    {
        // Draw Triangles
        switch(renderType){
        case TWO_TRIANGLES:
            glBegin(GL_TRIANGLES); // TODO: Transparency
                glColor3f(colors->at(0).red(),colors->at(0).green(), colors->at(0).blue());
                glVertex3f(this->vertices->at(0).X + this->GetPosition().X, this->vertices->at(0).Y + this->GetPosition().Y, this->vertices->at(0).Z + this->GetPosition().Z);

                glColor3f(colors->at(1).red(),colors->at(1).green(), colors->at(1).blue());
                glVertex3f(this->vertices->at(1).X + this->GetPosition().X, this->vertices->at(1).Y + this->GetPosition().Y, this->vertices->at(1).Z + this->GetPosition().Z);

                glColor3f(colors->at(2).red(),colors->at(2).green(), colors->at(2).blue());
                glVertex3f(this->vertices->at(2).X + this->GetPosition().X, this->vertices->at(2).Y + this->GetPosition().Y, this->vertices->at(2).Z + this->GetPosition().Z);
            glEnd();
            glBegin(GL_TRIANGLES); // TODO: Transparency
                glColor3f(colors->at(2).red(),colors->at(2).green(), colors->at(2).blue());
                glVertex3f(this->vertices->at(2).X + this->GetPosition().X, this->vertices->at(2).Y + this->GetPosition().Y, this->vertices->at(2).Z + this->GetPosition().Z);

                glColor3f(colors->at(3).red(),colors->at(3).green(), colors->at(3).blue());
                glVertex3f(this->vertices->at(3).X + this->GetPosition().X, this->vertices->at(3).Y + this->GetPosition().Y, this->vertices->at(3).Z + this->GetPosition().Z);

                glColor3f(colors->at(0).red(),colors->at(0).green(), colors->at(0).blue());
                glVertex3f(this->vertices->at(0).X + this->GetPosition().X, this->vertices->at(0).Y + this->GetPosition().Y, this->vertices->at(0).Z + this->GetPosition().Z);
            glEnd();
            break;
        case FOUR_TRIANGLES:
            if(colors->length()!=5)
            {
                if(SHOW_DEBUG)
                        qDebug() << "NO COLOR ASSIGNED TO CENTER.\nSet to Black.";
                colors->append(Qt::black);
            }
            for(int i = 0; i < this->vertices->length(); i++)
            {
                int i2 = (i+1<=this->vertices->length()-1)? i+1: 0;
                glBegin(GL_TRIANGLES); // TODO: Transparency
                    glColor3f(colors->at(i).red(),colors->at(i).green(), colors->at(i).blue());
                    glVertex3f(this->vertices->at(i).X + this->GetPosition().X, this->vertices->at(i).Y + this->GetPosition().Y, this->vertices->at(i).Z + this->GetPosition().Z);

                    glColor3f(colors->at(i2).red(),colors->at(i2).green(), colors->at(i2).blue());
                    glVertex3f(this->vertices->at(i2).X + this->GetPosition().X, this->vertices->at(i2).Y + this->GetPosition().Y, this->vertices->at(i2).Z + this->GetPosition().Z);

                    glColor3f(colors->at(4).red(),colors->at(4).green(), colors->at(4).blue());
                    glVertex3f(centerPoint.X + this->GetPosition().X, centerPoint.Y + this->GetPosition().Y, centerPoint.Z + this->GetPosition().Z);
                glEnd();
            }
            break;
        default:
            break;
        }
    }
    if(wireframe)
    {
        switch(renderType){
        case TWO_TRIANGLES:
            glBegin(GL_LINE_STRIP); // TODO: Transparency
                glLineWidth(wireframeThickness);
                glColor3f(frameColor.red(), frameColor.green(), frameColor.blue());
                glVertex3f(this->vertices->at(0).X + this->GetPosition().X, this->vertices->at(0).Y + this->GetPosition().Y, this->vertices->at(0).Z + this->GetPosition().Z);
                glVertex3f(this->vertices->at(1).X + this->GetPosition().X, this->vertices->at(1).Y + this->GetPosition().Y, this->vertices->at(1).Z + this->GetPosition().Z);
                glVertex3f(this->vertices->at(2).X + this->GetPosition().X, this->vertices->at(2).Y + this->GetPosition().Y, this->vertices->at(2).Z + this->GetPosition().Z);
                glVertex3f(this->vertices->at(3).X + this->GetPosition().X, this->vertices->at(3).Y + this->GetPosition().Y, this->vertices->at(3).Z + this->GetPosition().Z);
                glVertex3f(this->vertices->at(0).X + this->GetPosition().X, this->vertices->at(0).Y + this->GetPosition().Y, this->vertices->at(0).Z + this->GetPosition().Z);
                glVertex3f(this->vertices->at(2).X + this->GetPosition().X, this->vertices->at(2).Y + this->GetPosition().Y, this->vertices->at(2).Z + this->GetPosition().Z);
            glEnd();
            break;
        case FOUR_TRIANGLES:
            for(int i = 0; i < this->vertices->length(); i++)
            {
                int i2 = (i+1<=this->vertices->length()-1)? i+1: 0;
                glBegin(GL_LINE_STRIP); // TODO: Transparency
                    glLineWidth(wireframeThickness);
                    if(frameType == OUTER_ONLY || frameType == FULL_FRAME){
                        glColor3f(frameColor.red(), frameColor.green(), frameColor.blue());
                        glVertex3f(this->vertices->at(i).X + this->GetPosition().X, this->vertices->at(i).Y + this->GetPosition().Y, this->vertices->at(i).Z + this->GetPosition().Z);
                        glVertex3f(this->vertices->at(i2).X + this->GetPosition().X, this->vertices->at(i2).Y + this->GetPosition().Y, this->vertices->at(i2).Z + this->GetPosition().Z);
                    }
                    if(frameType==INNER_ONLY||frameType==FULL_FRAME){
                        if(INNER_ONLY)
                            glVertex3f(this->vertices->at(i).X + this->GetPosition().X, this->vertices->at(i).Y + this->GetPosition().Y, this->vertices->at(i).Z + this->GetPosition().Z);
                        glVertex3f(centerPoint.X + this->GetPosition().X, centerPoint.Y + this->GetPosition().Y, centerPoint.Z + this->GetPosition().Z);
                        glVertex3f(this->vertices->at(i).X + this->GetPosition().X, this->vertices->at(i).Y + this->GetPosition().Y, this->vertices->at(i).Z + this->GetPosition().Z);
                    }
                    glEnd();
            }
            break;
        default:
            break;
        }
    }
    p->endNativePainting();
    QGLShape::Draw(p);
}

Vector3 QGLQuad::GetCenter()
{
    return QGLMath::AvgVector3((*vertices));
}

bool QGLQuad::CheckClicked()
{
    return false;
}

bool QGLQuad::CheckMouseOver(QPainter* p)
{
    return false;
}
