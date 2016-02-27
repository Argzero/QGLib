#include <GL/glu.h>
#include <QDebug>
#include <QtGui/QMouseEvent>

#include "qglwindow.h"
#include "qglconstants.hpp"

using namespace QGLConstants;

QGLWindow::QGLWindow(QWidget *parent) : QGLWidget(parent)
{
    updateTimer = new QTimer;
    bgON = false;
    bgCenterOffset = Vector2::Zero;
    connect(updateTimer,SIGNAL(timeout()),SLOT(updateGL()));
    qDebug("QGLWindow Created");
}

QGLWindow::~QGLWindow()
{
    if(objects == NULL)
        if(SHOW_DEBUG)
            qDebug("Deleting QGLWindow Object Collection...");
    QVector<QGLObject*> _obj_cpy = *objects;
    if(SHOW_DEBUG)
        qDebug() << "Copy Complete." << (_obj_cpy.length()) << " " << (objects->length());
    objects = NULL;
    delete objects;
    if(SHOW_DEBUG)
        qDebug("Deleting Objects...");
    while(_obj_cpy.length()>0)
    {
        if(SHOW_DEBUG)
            qDebug() << "Remaining Objects: " << (_obj_cpy.length());

        if(SHOW_DEBUG)
            qDebug("Deleting Object...");
        QGLObject::TYPE t = _obj_cpy.first()->type;
        switch(t){
        case QGLObject::EMPTY:
            {
                if(SHOW_DEBUG)
                    qDebug("EMPTY object deleted.");
                delete _obj_cpy.takeFirst();
            }
            break;
        case QGLObject::TEXT:
            {
                if(SHOW_DEBUG)
                    qDebug("Text deleted.");
                delete static_cast<QGLText*>(_obj_cpy.takeFirst());
            }
            break;
        case QGLObject::SHAPE:
            {
                if(SHOW_DEBUG)
                    qDebug("Shape delete.");
                QGLShape* _s = static_cast<QGLShape*>(_obj_cpy.first());
                switch(_s->shape)
                {
                case QGLShape::TRIANGLE:
                    delete static_cast<QGLTriangle*>(_s);
                    if(SHOW_DEBUG)
                        qDebug("Triangle deleted.");
                    break;
                case QGLShape::CIRCLE:
                    //delete _s; // TODO: CREATE CIRCLE AND MODIFY THIS!
                    if(SHOW_DEBUG)
                        qDebug("WARNING: MEMORY LEAK, CIRCLE delete not defined!");
                    break;
                case QGLShape::QUAD:
                    delete static_cast<QGLQuad*>(_obj_cpy.takeFirst());
                    if(SHOW_DEBUG)
                        qDebug("Rect deleted.");
                    break;
                case QGLShape::POLYGON:
                    //delete _s;
                    if(SHOW_DEBUG)
                        qDebug("WARNING: MEMORY LEAK, NGON delete not defined!");
                    break;
                default:
                    // delete _s;
                    if(SHOW_DEBUG)
                        qDebug("WARNING: MEMORY LEAK, UNKNOWN_TYPE delete functionality unable to be determined!");
                    break;
                }
            }
            break;
        case QGLObject::MODEL:
            {
                if(SHOW_DEBUG)
                    qDebug("WARNING: MEMORY LEAK, MODEL delete not defined!");
                delete _obj_cpy.takeFirst();
            }
            break;
        default:
            {
                if(SHOW_DEBUG)
                    qDebug("Other QGLObject type deleted! WARNING: UNABLE TO DETERMINE OBJECT TYPE.");
                delete _obj_cpy.takeFirst();
            }
            break;
        }
    }
    if(SHOW_DEBUG)
        qDebug() << "Object deletion complete. Remaining objects: " << (_obj_cpy.length());

    delete updateTimer;
    if(SHOW_DEBUG)
        qDebug("~QGLWindow");
}

void QGLWindow::updateCursor()
{
    QPoint mPos = this->mapFromGlobal(QCursor::pos());
    this->mouse.X = mPos.x();
    this->mouse.Y = mPos.y();
}

void QGLWindow::addComponents()
{
}

void QGLWindow::start()
{
    if(SHOW_DEBUG)
        qDebug("QGLWindow TIMER START!");
    updateTimer->start(0);
}

void QGLWindow::initializeGL()
{
    makeCurrent();

    // Set up the rendering context, define display lists etc
    glClearColor(1.0f, 1.0f, 0.0f, 0.0f);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_DEPTH_TEST);
    glColorMaterial(GL_FRONT,GL_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_BLEND);
    glEnable(GL_POLYGON_SMOOTH);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0, 0, 0, 0);
}

void QGLWindow::resizeGL(int w, int h)
{
    // setup viewport, projection etc.:
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h); // set origin to bottom left corner
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void QGLWindow::paintGL()
{
    makeCurrent();
    updateCursor();
    /******************************************************
     * LIGHTING EXAMPLE VALUES
     *  float ambientLight[] = { 0.6, 0.2, 0.2, 1.0 };
     *  float specularLight[] = { 1.0, 1.0, 1.0, 1.0 };
     *  float specularity[] = { 1.0, 1.0, 1.0, 1.0 };
     *  float shininess[] = { 60.0 };
     *  float lightPosition[] = { 0.0, 50.0, 50.0, 1.0 };
     ******************************************************/
    // For lit triangle in corner
    float ambientLight[] = { 0.6, 0.2, 0.2, 1.0 };
    float lightPosition[] = { 0.0, 10.0, 15.0, 1.0 };

    // Initialize Painter
    QPainter p(this);
    clear(&p); // Drawing Rectangle to cover entire Window (erase last frame to draw new frame)

    if(bgON){
    p.beginNativePainting();

    // LIGHTING
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // Properties of the objects' materials
    //glMaterialfv(GL_FRONT, GL_SHININESS, shininess); // Shininess

    // Enable ambient light usage
    //glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    //glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);

    // Position of the light source
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    glBegin(GL_TRIANGLES);
        glColor3f(bgRectColors[0].red(),bgRectColors[0].green(),bgRectColors[0].blue());
        glVertex2f(0.0f, 0.0f);

        glColor3f(bgRectColors[1].red(),bgRectColors[1].green(),bgRectColors[1].blue());
        glVertex2f(width(), 0.0f);

        glColor3f(bgRectColors[4].red(),bgRectColors[4].green(),bgRectColors[4].blue());
        glVertex2f(width()/2, height()/2);

        glColor3f(bgRectColors[1].red(),bgRectColors[1].green(),bgRectColors[1].blue());
        glVertex2f(width(), 0.0f);

        glColor3f(bgRectColors[2].red(),bgRectColors[2].green(),bgRectColors[2].blue());
        glVertex2f(width(), height());

        glColor3f(bgRectColors[4].red(),bgRectColors[4].green(),bgRectColors[4].blue());
        glVertex2f(width()/2, height()/2);

        glColor3f(bgRectColors[2].red(),bgRectColors[2].green(),bgRectColors[2].blue());
        glVertex2f(width(), height());

        glColor3f(bgRectColors[3].red(),bgRectColors[3].green(),bgRectColors[3].blue());
        glVertex2f(0.0f, height());

        glColor3f(bgRectColors[4].red(),bgRectColors[4].green(),bgRectColors[4].blue());
        glVertex2f(width()/2, height()/2);

        glColor3f(bgRectColors[0].red(),bgRectColors[0].green(),bgRectColors[0].blue());
        glVertex2f(0.0f, 0.0f);

        glColor3f(bgRectColors[3].red(),bgRectColors[3].green(),bgRectColors[3].blue());
        glVertex2f(0.0f, height());

        glColor3f(bgRectColors[4].red(),bgRectColors[4].green(),bgRectColors[4].blue());
        glVertex2f(width()/2, height()/2);
    glEnd();
    p.endNativePainting();
    }

    for(int i=0; i < objects->length(); i++){
       // qDebug("QGLWINDOW OBJECT DRAW");
        objects->at(i)->update();
        objects->at(i)->draw(&p);
    }


    // Fancy triangles
    p.beginNativePainting();

    // LIGHTING
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // Properties of the objects' materials
    //glMaterialfv(GL_FRONT, GL_SHININESS, shininess); // Shininess

    // Enable ambient light usage
    //glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    //glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);

    // Position of the light source
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    glBegin(GL_TRIANGLES);
        glColor3f(0.5f, 0.0f, 0.5f);
        glVertex3f(0, 0, 0);

        glColor3f(0.0f, 0.0f, 0.3f);
        glVertex3f(200,0,0);

        glColor3f(0.3f, 0.0f, 0.0f);
        glVertex3f(0,200,0);
    glEnd();
    glDisable(GL_LIGHTING);
    glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 0.0f, 0.5f);
        glVertex2f(width(), height());

        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2f(width() - 200, height());

        glColor3f(0.5f, 0.0f, 0.0f);
        glVertex2f(width(), height() - 200);
    glEnd();
    p.endNativePainting();
}

void QGLWindow::addBg(QVector<QColor> cVec)
{
    bgRectColors.append(cVec[0]);
    bgRectColors.append(cVec[1]);
    bgRectColors.append(cVec[2]);
    bgRectColors.append(cVec[3]);
    bgRectColors.append(cVec[4]);
    bgON = true;
}

void QGLWindow::bgOff()
{
    bgON = false;
}


void QGLWindow::bgOn()
{
    if(bgRectColors.length()<5)
        throw("NOT ENOUGH BG COLORS ADDED. PLEASE USE ADDBG TO ADD A BACKGROUND.");
    bgON = true;
}

void QGLWindow::clear(QPainter *p)
{
    p->save();
    p->setPen(Qt::NoPen);
    p->setBrush(Qt::black);
    p->drawRect(rect());
    p->restore();
}

void QGLWindow::qglColor(QColor color)
{
    glColor3f(color.redF(), color.greenF(), color.blueF());
}

void QGLWindow::qglClearColor(QColor clearColor)
{
    glClearColor(clearColor.redF(), clearColor.greenF(), clearColor.blueF(), clearColor.alphaF());
}

QGLText* QGLWindow::AddText(QGLObject *_parent, Vector3 _pos, string _text, int _size, QColor _color, QGLText::ALIGN _align)
{
    if(_parent == NULL)
    {
        objects->push_back(new QGLText(_parent, _pos, _text, _size, _color, _align));
        objects->last()->window = this;
        return static_cast<QGLText*>(objects->last());
    }
    else
    {
        _parent->children->append(new QGLText(_parent, _pos, _text, _size, _color, _align));
        _parent->children->last()->window = this;
        return static_cast<QGLText*>(_parent->children->last());
    }
}

// EQUILATERAL TRIANGLE
QGLTriangle* QGLWindow::AddTriangle(QGLObject *_parent, Vector3 _pos,
            float _radius, float _rotation /*degrees*/, QColor _color,
            bool _wireframe, QColor _frameColor)
{
    if(_parent == NULL)
    {
        objects->push_back(new QGLTriangle(_parent, _pos, _radius, _color, _rotation, _wireframe, _frameColor));
        objects->last()->window = this;
        return static_cast<QGLTriangle*>(objects->last());
    }
    else
    {
        _parent->children->append(new QGLTriangle(_parent, _pos, _radius, _color, _rotation, _wireframe, _frameColor));
        _parent->children->last()->window = this;
        return static_cast<QGLTriangle*>(_parent->children->last());
    }
}

QGLTriangle* QGLWindow::AddTriangle(QGLObject *_parent, Vector3 _pos,
            float _radius, float _rotation /*degrees*/, QVector<QColor> *_colors,
            bool _wireframe, QColor _frameColor)
{
    if(_parent == NULL)
    {
        objects->push_back(new QGLTriangle(_parent, _pos, _radius, _colors, _rotation, _wireframe, _frameColor));
        objects->last()->window = this;
        return static_cast<QGLTriangle*>(objects->last());
    }
    else
    {
        _parent->children->append(new QGLTriangle(_parent, _pos, _radius, _colors, _rotation, _wireframe, _frameColor));
        _parent->children->last()->window = this;
        return static_cast<QGLTriangle*>(_parent->children->last());
    }
}

// ANY TYPE OF TRIANGLE
QGLTriangle* QGLWindow::AddTriangle(QGLObject *_parent, Vector3 _pos,
            QVector<Vector3> *_corners, QColor _color,
            bool _wireframe, QColor _frameColor)
{
    if(_parent == NULL)
    {
        objects->push_back(new QGLTriangle(_parent, _pos, _corners, _color, _wireframe, _frameColor));
        objects->last()->window = this;
        return static_cast<QGLTriangle*>(objects->last());
    }
    else
    {
        _parent->children->append(new QGLTriangle(_parent, _pos, _corners, _color, _wireframe, _frameColor));
        _parent->children->last()->window = this;
        return static_cast<QGLTriangle*>(_parent->children->last());
    }
}

QGLTriangle* QGLWindow::AddTriangle(QGLObject *_parent, Vector3 _pos,
            QVector<Vector3> *_corners, QVector<QColor> *_colors,
            bool _wireframe, QColor _frameColor)
{
    if(_parent == NULL)
    {
        objects->push_back(new QGLTriangle(_parent, _pos, _corners, _colors, _wireframe, _frameColor));
        objects->last()->window = this;
        return static_cast<QGLTriangle*>(objects->last());
    }
    else
    {
        _parent->children->append(new QGLTriangle(_parent, _pos, _corners, _colors, _wireframe, _frameColor));
        _parent->children->last()->window = this;
        return static_cast<QGLTriangle*>(_parent->children->last());
    }
}

// Quadritlaterals
QGLQuad* QGLWindow::AddQuad(QGLObject *_parent, Vector3 _pos,
                 QVector<Vector3> *_vertices, QColor _color,
                 bool _wireframe, QColor _frameColor,
                 QGLQuad::RENDER_TYPE _renderType,
                 QGLQuad::FRAME_TYPE _frameType)
{
    if(_parent == NULL)
    {
        objects->push_back(new QGLQuad(_parent, _pos, _vertices, _color, _wireframe,
                                       _frameColor, _renderType, _frameType));

        objects->last()->window = this;
        return static_cast<QGLQuad*>(objects->last());
    }
    else
    {
        _parent->children->append(new QGLQuad(_parent, _pos, _vertices, _color, _wireframe,
                                                 _frameColor, _renderType, _frameType));
        _parent->children->last()->window = this;
        return static_cast<QGLQuad*>(_parent->children->last());
    }
}

QGLQuad* QGLWindow::AddQuad(QGLObject *_parent, Vector3 _pos,
                 QVector<Vector3> *_vertices, QVector<QColor> *_colors,
                 bool _wireframe, QColor _frameColor,
                 QGLQuad::RENDER_TYPE _renderType,
                 QGLQuad::FRAME_TYPE _frameType)
{
    if(_parent == NULL)
    {
        objects->push_back(new QGLQuad(_parent, _pos, _vertices, _colors, _wireframe,
                                       _frameColor, _renderType, _frameType));

        objects->last()->window = this;
        return static_cast<QGLQuad*>(objects->last());
    }
    else
    {
        _parent->children->append(new QGLQuad(_parent, _pos, _vertices, _colors, _wireframe,
                                                 _frameColor, _renderType, _frameType));
        _parent->children->last()->window = this;
        return static_cast<QGLQuad*>(_parent->children->last());
    }
}
