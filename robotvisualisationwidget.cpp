#include "robotvisualisationwidget.h"
#include <iostream>

#define LINES_TO_DRAW 9
#define PAST_TCP_BUFFER_DEFAULT_SIZE 40

RobotVisualisationWidget::RobotVisualisationWidget(QWidget *parent) : QGLWidget(parent)
{
	setFormat(QGLFormat(QGL::DoubleBuffer | QGL::DepthBuffer));
	rotationX = -90;
	rotationY = 0;
	rotationZ = -135;
	this->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
	pastTCPBufferSize = PAST_TCP_BUFFER_DEFAULT_SIZE;
}

void RobotVisualisationWidget::setRobotJointsPoints(QVector<Point> points)
{
	jointsPoints = points;
	pastTCPs.append(points.last());
	if(pastTCPs.size() > pastTCPBufferSize) {
		pastTCPs.removeFirst();
	}
	this->repaint();
}

void RobotVisualisationWidget::setPastTCPsBufferSize(int newSize)
{
	pastTCPBufferSize = newSize;
}

void RobotVisualisationWidget::setViewAngles(float rotX, float rotY, float rotZ)
{
	rotationX = rotX;
	rotationY = rotY;
	rotationZ = rotZ;
	//TODO redraw now?
}

void RobotVisualisationWidget::initializeGL()
{
	initializeOpenGLFunctions();
	qglClearColor(Qt::black);
	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
}

void RobotVisualisationWidget::resizeGL(int width, int height)
{
	glViewport(0,0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	GLfloat x = GLfloat(width) / height;
	//GLfloat x = 10;
	glFrustum(-x, x, -x, x, 8, 20);
	glMatrixMode(GL_MODELVIEW);
}

void RobotVisualisationWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	draw();
}

void RobotVisualisationWidget::mousePressEvent(QMouseEvent *event)
{
	lastPos = event->pos();
}

void RobotVisualisationWidget::mouseMoveEvent(QMouseEvent *event)
{
	GLfloat dx = GLfloat(event->x() - lastPos.x()) / width();
	GLfloat dy = GLfloat(event->y() - lastPos.y()) / height();
	if(event->buttons() & Qt::LeftButton) {
		rotationX += 180 * dy;
		rotationY += 180 * dx;
		updateGL();
	} else if(event->buttons() & Qt::RightButton) {
		rotationX += 180 * dy;
		rotationZ += 180 * dx;
		updateGL();
	}
	lastPos = event->pos();
}

void RobotVisualisationWidget::draw()
{
	//qDebug() << "RobotVisualisationWidget: drawing...";
	if(jointsPoints.size() != (LINES_TO_DRAW + 1)) {
		qDebug() << "RobotVisualisationWidget::draw(): jointsPoints size wrong: " << jointsPoints.size();
		return;
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -10.0);
	glRotatef(rotationX, 1.0, 0.0, 0.0);
	glRotatef(rotationY, 0.0, 1.0, 0.0);
	glRotatef(rotationZ, 0.0, 0.0, 1.0);
	drawXYZ();
	drawPastTCPs();
	for(int i = 0; i < LINES_TO_DRAW; i++) {
		Point p1 = jointsPoints.at(i);
		Point p2 = jointsPoints.at(i + 1);
		glLoadName(i);
		glPointSize(5);
		glBegin(GL_POINTS);
		qglColor(Qt::magenta);
		glVertex3f(p1.x / 1000, p1.y / 1000, p1.z / 1000);
		glEnd();
		glLineWidth(3.0);
		glBegin(GL_LINES);
		qglColor(Qt::yellow);
		//std::cout << "Draw line from point " << p1 << " to point " << p2 << std::endl;
		glVertex3f(p1.x / 1000, p1.y / 1000, p1.z / 1000);
		glVertex3f(p2.x / 1000, p2.y / 1000, p2.z / 1000);
		glEnd();

	}
	Point p = jointsPoints.last();
	glPointSize(7);
	glBegin(GL_POINTS);
	qglColor(Qt::red);
	glVertex3f(p.x / 1000, p.y / 1000, p.z / 1000);
	glEnd();
}

void RobotVisualisationWidget::drawPastTCPs()
{
	glPointSize(2);
	for(Point p : pastTCPs) {
		glBegin(GL_POINTS);
		qglColor(Qt::cyan);
		glVertex3f(p.x/1000, p.y/1000, p.z/1000);
		glEnd();
	}
}

void RobotVisualisationWidget::drawXYZ()
{
	int axisLength = 1;
	glBegin(GL_LINES);
	qglColor(Qt::red);
	glVertex3f(0,0,0);
	glVertex3f(axisLength,0,0);
	glEnd();

	glBegin(GL_LINES);
	qglColor(Qt::green);
	glVertex3f(0,0,0);
	glVertex3f(0,axisLength,0);
	glEnd();

	glBegin(GL_LINES);
	qglColor(Qt::blue);
	glVertex3f(0,0,0);
	glVertex3f(0,0,axisLength);
	glEnd();
}
