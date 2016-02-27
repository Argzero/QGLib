#include "scenenode.h"
#include "../objects/qglobject.h"
#include "../objects/text/qgltext.h"
#include "../objects//shapes/qglshape.h"
#include "../qglconstants.hpp"

using namespace QGLConstants;

SceneNode::SceneNode(QWidget *_parent) : QGLWindow(_parent)
{
    objects = new QVector<QGLObject*>();
    addComponents();

    if(SHOW_DEBUG)
        qDebug("SceneNode Created.");
}

SceneNode::~SceneNode(){
    if(SHOW_DEBUG){
        qDebug("SceneNode Destructed.");
    }
}

void SceneNode::addBg(QColor c)
{
    QVector<QColor> cVec;
    cVec.append(c);
    cVec.append(c);
    cVec.append(c);
    cVec.append(c);
    cVec.append(c);
    QGLWindow::addBg(cVec);
}

void SceneNode::addBg(QVector<QColor> cVec)
{
    QGLWindow::addBg(cVec);
}

void SceneNode::addComponents()
{
    QVector<QColor>* sqC = new QVector<QColor>();
    sqC->append(QColor(1.0f, 1.0f, 0.2f));
    sqC->append(QColor(1.0f, 1.0f, 0.2f));
    sqC->append(QColor(1.0f, 1.0f, 0.2f));
    sqC->append(QColor(1.0f, 1.0f, 0.2f));
    sqC->append(QColor(0.5f,0.5f,0.5f));

    addBg(*sqC);


    QVector<Vector3>* v = new QVector<Vector3>();
    v->append(Vector3(0,0,0));
    v->append(Vector3(50,50,0));
    v->append(Vector3(50,0,0));

    //QGLTriangle* t = (this->QGLWindow::AddTriangle(NULL, Vector3(width()/2, height()/2, 0), v, Qt::blue, true, Qt::red));
    //t->wireframeThickness = 10.0;
    //(QGLWindow::AddTriangle(NULL, Vector3(50, 50, 0), 50, 0.0, Qt::green, true, Qt::white));


    QVector<Vector3>* sqV1 = new QVector<Vector3>();
    sqV1->append(Vector3(-50,-50,0));
    sqV1->append(Vector3(-50,50,0));
    sqV1->append(Vector3(50,50,0));
    sqV1->append(Vector3(50,-50,0));
    QVector<Vector3>* sqV2 = new QVector<Vector3>();
    sqV2->append(Vector3(-200,-20,0));
    sqV2->append(Vector3(-200,20,0));
    sqV2->append(Vector3(200,20,0));
    sqV2->append(Vector3(200,-20,0));
    QVector<Vector3>* sqV3 = new QVector<Vector3>();
    sqV3->append(Vector3(0,0,0));
    sqV3->append(Vector3(0,270,0));
    sqV3->append(Vector3(270,270,0));
    sqV3->append(Vector3(270,0,0));
    QVector<Vector3>* sqV4c3 = new QVector<Vector3>();
    sqV4c3->append(Vector3(-20, -5*qSqrt(3), 0));
    sqV4c3->append(Vector3(10, -5*qSqrt(3), 0));
    sqV4c3->append(Vector3(20, 5*qSqrt(3), 0));
    sqV4c3->append(Vector3(-10, 5*qSqrt(3), 0));

    // HARDCORE CHILDING O_O...
    QGLQuad* q1 = (QGLWindow::AddQuad(NULL, Vector3(200, 150, 0), sqV1, sqC, true, QColor(125,188, 188), QGLQuad::FOUR_TRIANGLES, QGLQuad::FULL_FRAME));
    QGLQuad* q2 = (QGLWindow::AddQuad(q1, Vector3(0, 120, 0), sqV2, Qt::green, false, QColor(0,188, 188), QGLQuad::TWO_TRIANGLES, QGLQuad::OUTER_ONLY));
    QGLQuad* q3 = (QGLWindow::AddQuad(q2, Vector3(200, 200, 0), sqV3, sqC, true, QColor(0,225, 150), QGLQuad::FOUR_TRIANGLES, QGLQuad::INNER_ONLY));
    (QGLWindow::AddQuad(q3, Vector3(0, 0, 0), sqV4c3, QColor(150,100,0)));

    (QGLWindow::AddText(NULL, Vector3(width()/2, height()/2, 0), "Hello, World!", 24, Qt::blue, QGLObject::CENTER_MID))->color = Qt::red;

    //connect(clickSource, SIGNAL(clicked()), &m_explosion, SLOT(play()));
    QGLWindow::start();
}

// Add text example:
//      QGLWindow::AddText(NULL, Vector3(width()/2, height()/2, 0), "Hello, World!", 24, Qt::blue, QGLText::CENTER_MID);
//
// Add triangle example:
