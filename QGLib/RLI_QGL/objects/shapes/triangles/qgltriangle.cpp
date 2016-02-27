#include "qgltriangle.h"
#include "../../../utils/qglmath.h"
#include "../../../qglconstants.hpp"

using namespace QGLConstants;

#include <string>     // std::string, std::to_string

QGLTriangle::QGLTriangle() :
    QGLShape(NULL,Vector3::Zero,CENTER_MID, false, Qt::black)
{
    shape = TRIANGLE;
}

// EQUILATERAL TRIANGLE
QGLTriangle::QGLTriangle(QGLObject *_parent, Vector3 _pos,
                         float _radius, QColor _color, float _rotation /*degrees*/,
                         bool _wireframe, QColor _frameColor):
    QGLShape(_parent, _pos, CENTER_MID, _wireframe, _frameColor)
{
    shape = TRIANGLE;
    if(_radius <= 0.0){
        std::string s;
        s.append("Invalid radius value, please provide positive, non-zero value - Provided: +_radius+");
        throw(s);
    }
    vertices = new QVector<Vector3>();
    vertices -> append(Vector3(_pos.X + (_radius * qCos(qDegreesToRadians(_rotation))),       _pos.Y + (_radius * qSin(qDegreesToRadians(_rotation))),       _pos.Z));
    vertices -> append(Vector3(_pos.X + (_radius * qCos(qDegreesToRadians(120 + _rotation))), _pos.Y + (_radius * qSin(qDegreesToRadians(120 + _rotation))), _pos.Z));
    vertices -> append(Vector3(_pos.X + (_radius * qCos(qDegreesToRadians(240 + _rotation))), _pos.Y + (_radius * qSin(qDegreesToRadians(240 + _rotation))), _pos.Z));

    colors = new QVector<QColor>();
    for(int i = 0; i<3; i++){
        colors->append(_color);
    }
}

QGLTriangle::QGLTriangle(QGLObject *_parent, Vector3 _pos,
                         float _radius, QVector<QColor> *_colors, float _rotation /*degrees*/,
                         bool _wireframe, QColor _frameColor):
    QGLShape(_parent, _pos, CENTER_MID, _wireframe, _frameColor)
{
    shape = TRIANGLE;
    if(_radius <= 0.0)
        throw("Invalid radius value, please provide positive, non-zero value - Provided: +_radius+");

    vertices = new QVector<Vector3>();
    vertices -> append(Vector3(_pos.X + (_radius * qCos(qDegreesToRadians(_rotation))),       _pos.Y + (_radius * qSin(qDegreesToRadians(_rotation))),       _pos.Z));
    vertices -> append(Vector3(_pos.X + (_radius * qCos(qDegreesToRadians(120 + _rotation))), _pos.Y + (_radius * qSin(qDegreesToRadians(120 + _rotation))), _pos.Z));
    vertices -> append(Vector3(_pos.X + (_radius * qCos(qDegreesToRadians(240 + _rotation))), _pos.Y + (_radius * qSin(qDegreesToRadians(240 + _rotation))), _pos.Z));

    if(_colors == NULL || _colors->length()!=3)
        throw("ERROR: MUST SUPPLY COLOR FOR EACH VERTEX PROVIDED!");
    colors = new QVector<QColor>();
    for(int i = 0; i<3; i++){
        colors->append(_colors->at(i));
    }
}

// ANY KIND OF TRIANGLE
QGLTriangle::QGLTriangle(QGLObject *_parent, Vector3 _pos,
                         QVector<Vector3> *_corners, QColor _color,
                         bool _wireframe, QColor _frameColor):
    QGLShape(_parent, _pos, CENTER_MID, _wireframe, _frameColor)
{
    shape = TRIANGLE;
    if(_corners->length()!=3)
        throw("Incorrect number of corners for Triangle. Requires 3.");

    vertices = new QVector<Vector3>();
    vertices -> append(_corners->takeFirst());
    vertices -> append(_corners->takeFirst());
    vertices -> append(_corners->takeFirst());

    colors = new QVector<QColor>();
    for(int i = 0; i<3; i++){
        colors->append(_color);
    }
}

QGLTriangle::QGLTriangle(QGLObject *_parent, Vector3 _pos,
                         QVector<Vector3> *_corners, QVector<QColor> *_colors,
                         bool _wireframe, QColor _frameColor):
    QGLShape(_parent, _pos, CENTER_MID, _wireframe, _frameColor)
{
    shape = TRIANGLE;
    if(_corners->length()!=3)
        throw("Incorrect number of corners for Triangle. Requires 3.");

    vertices = new QVector<Vector3>();
    vertices -> append(_corners->takeFirst());
    vertices -> append(_corners->takeFirst());
    vertices -> append(_corners->takeFirst());

    if(_colors == NULL || _colors->length()!=3)
        throw("ERROR: MUST SUPPLY COLOR FOR EACH VERTEX PROVIDED!");
    colors = new QVector<QColor>();
    for(int i = 0; i<3; i++)
    {
        colors->append(_colors->at(i));
    }
}

QGLTriangle::~QGLTriangle()
{

}

// TODO: DO ANIMATIONS
void QGLTriangle::update()
{
    QGLShape::update();
}

void QGLTriangle::draw(QPainter *p)
{
    // Modest triangles
    p->beginNativePainting();
    // LIGHTING - TODO!: NOT IMPLEMENTED!
    // Begin with glEnable(GL_LIGHTING); END with glDisable(GL_LIGHTING);
    //
    // Properties of the objects' materials
    // glMaterialfv(GL_FRONT, GL_SHININESS, shininess); // Shininess
    //
    // Enable ambient light usage
    //  glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    //  OR glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
    //
    // Position of the light source
    //  glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    // END LIGHTING
    if(lit){
        return;
    }

    if(fill){
        // Draw Triangle
        glBegin(GL_TRIANGLES); // TODO: Transparency
            glColor3f(colors->at(0).red(),colors->at(0).green(), colors->at(0).blue());
            glVertex3f(vertices->at(0).X, vertices->at(0).Y, vertices->at(0).Z);

            glColor3f(colors->at(1).red(),colors->at(1).green(), colors->at(1).blue());
            glVertex3f(vertices->at(1).X, vertices->at(1).Y, vertices->at(1).Z);

            glColor3f(colors->at(2).red(),colors->at(2).green(), colors->at(2).blue());
            glVertex3f(vertices->at(2).X, vertices->at(2).Y, vertices->at(2).Z);
        glEnd();
    }
    if(wireframe){
        glBegin(GL_LINE_STRIP); // TODO: Transparency
            glLineWidth(wireframeThickness);
            glColor3f(frameColor.red(), frameColor.green(), frameColor.blue());
            glVertex3f(vertices->at(0).X, vertices->at(0).Y, vertices->at(0).Z);
            glVertex3f(vertices->at(1).X, vertices->at(1).Y, vertices->at(1).Z);
            glVertex3f(vertices->at(2).X, vertices->at(2).Y, vertices->at(2).Z);
            glVertex3f(vertices->at(0).X, vertices->at(0).Y, vertices->at(0).Z);
        glEnd();
    }
    p->endNativePainting();
    QGLShape::draw(p);
}

Vector3 QGLTriangle::GetCenter()
{
    return QGLMath::AvgVector3(*vertices);
}


void QGLTriangle::contains(Vector2 point)
{
}
