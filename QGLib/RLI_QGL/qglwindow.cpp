// OS-SPECIFIC FUNCTIONALITY
#ifdef __APPLE__
#include <OpenGL/glu.h>
#else
#include <GL/glu.h>
#endif

#include <QDebug>
#include <QProcess>
#include <QtGui/QMouseEvent>

#include "qglwindow.h"
#include "objects/scenes/scenenode.h"
#include "utils/qglconstants.hpp"

using namespace QGLConstants;

void inline unproject(GLdouble x,GLdouble y,GLdouble z,
    GLdouble *mv,GLdouble *pr,GLint *vp,
    Vector3 &v)
    {
    GLdouble rx,ry,rz;
    gluUnProject(x,y,z, mv,pr,vp, &rx,&ry,&rz);
    v = Vector3(rx,ry,rz);
}

QGLWindow::QGLWindow(QWidget *parent) : QOpenGLWidget(parent)
{
    updateTimer = new QTimer;
    bgON = false;
    bgCenterOffset = Vector2::Zero;
    connect(updateTimer,SIGNAL(timeout()),SLOT(update()));
}

QGLWindow::~QGLWindow()
{
    if(SHOW_DESTRUCTION)
        qDebug("Deleting Main Scenes...");

    scenes.clear();
    if(SHOW_DESTRUCTION){
        qDebug() << "Main Scene List deletion complete. Remaining Main Scenes: " << (scenes.length());
    }
    delete updateTimer;
    if(SHOW_DESTRUCTION)
        qDebug("~QGLWindow");
}

void QGLWindow::updateCursor()
{
    QPoint mPos = this->mapFromGlobal(QCursor::pos());
    this->mouse.X = mPos.x();
    this->mouse.Y = mPos.y();
}

void QGLWindow::start()
{
    if(SHOW_DEBUG)
        qDebug("QGLWindow TIMER START!");
    if(!QGLConstants::SHOW_MOUSE)
        this->setCursor(Qt::BlankCursor);
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

    GLdouble mv[16];
    GLdouble pr[16];
    GLint vp[4];
    glGetDoublev(GL_MODELVIEW_MATRIX,mv);
    glGetDoublev(GL_PROJECTION_MATRIX,pr);
    glGetIntegerv(GL_VIEWPORT,vp);

    Vector3 results[8];
    unproject(vp[0] ,vp[1],0.0, mv,pr,vp, results[0]);
    unproject(vp[0] ,vp[1],1.0, mv,pr,vp, results[1]);
    unproject(vp[0]+vp[2],vp[1],0.0, mv,pr,vp, results[2]);
    unproject(vp[0]+vp[2],vp[1],1.0, mv,pr,vp, results[3]);
    unproject(vp[0]+vp[2],vp[1]+vp[3],0.0, mv,pr,vp, results[4]);
    unproject(vp[0]+vp[2],vp[1]+vp[3],1.0, mv,pr,vp, results[5]);
    unproject(vp[0] ,vp[1]+vp[3],0.0, mv,pr,vp, results[6]);
    unproject(vp[0] ,vp[1]+vp[3],1.0, mv,pr,vp, results[7]);

    if(SHOW_WINDOW_DATA)
        qDebug()<< "\n\n\nFrustum: \n"
                   + results[0].ToString() + ", "
                   + results[1].ToString() + ", "
                   + results[2].ToString() + ", "
                   + results[3].ToString() + "\nAND\n"
                   + results[4].ToString() + ", "
                   + results[5].ToString() + ", "
                   + results[6].ToString() + ", "
                   + results[7].ToString();
}

void QGLWindow::updateGL()
{
    qDebug() << "UPDATE. EMPTY...";
}

void QGLWindow::paintGL()
{
    //qDebug() << "PAINT.";
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
    float lightPosition[] = { 0.0, 500.0, 500.0, 1.0 };

    // Initialize Painter
    QPainter p(this);

    // Drawing Rectangle to cover entire Window (erase last frame to draw new frame)
    clear(&p);

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

    // TELL SCENES TO DRAW AND UPDATE!!!
    if(QGLConstants::SHOW_DEBUG)
        qDebug() << scenes.length() << " scenes";
    for(int i=0; i < scenes.length(); i++){
        qDebug("SCENE UPDATE AND DRAW");
        ((SceneNode*)(scenes.at(i)))->Draw(&p);
        ((SceneNode*)(scenes.at(i)))->Update();
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
    if(QGLConstants::SHOW_QGLWINDOW_DEBUG_TRIANGLES){
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
    }
    if(SHOW_QGL_CURSOR){
        Vector3 point = Vector3(mouse.X,mouse.Y,0);
        glBegin(GL_TRIANGLES); // TODO: Transparency
            glColor3f(255.0f/255.0f, 215.0f/255.0f, 0.0f);
            glVertex3f(point.X+QGL_CURSOR_SIZE, point.Y+QGL_CURSOR_SIZE/2, point.Z);
            glVertex3f(point.X+QGL_CURSOR_SIZE/2, point.Y+QGL_CURSOR_SIZE/2, point.Z);
            glVertex3f(point.X, point.Y, point.Z);
        glEnd();
        glBegin(GL_TRIANGLES); // TODO: Transparency
            glColor3f(255.0f/255.0f, 215.0f/255.0f, 0.0f);
            glVertex3f(point.X+QGL_CURSOR_SIZE/2, point.Y+QGL_CURSOR_SIZE/2, point.Z);
            glVertex3f(point.X+QGL_CURSOR_SIZE/2, point.Y+QGL_CURSOR_SIZE, point.Z);
            glVertex3f(point.X, point.Y, point.Z);
        glEnd();
    }
    p.endNativePainting();
}

void QGLWindow::setBg(QVector<QColor> cVec)
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

void QGLWindow::qglClearColor(QColor clearColor)
{
    glClearColor(clearColor.redF(), clearColor.greenF(), clearColor.blueF(), clearColor.alphaF());
}

Vector2 QGLWindow::GetMouse(){
    return mouse;
}

void QGLWindow::AddScene(SceneNode* s){
    scenes.append(s);
}
