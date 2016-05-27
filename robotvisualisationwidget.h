#ifndef ROBOTVISUALISATIONWIDGET_H
#define ROBOTVISUALISATIONWIDGET_H

#include <QWidget>
#include <QtOpenGL>
#include <QMouseEvent>
#include <QOpenGLFunctions>
#include <QVector>
#include "point.h"

class RobotVisualisationWidget : public QGLWidget, protected QOpenGLFunctions
{
	Q_OBJECT
public:
	explicit RobotVisualisationWidget(QWidget *parent = 0);
	void setRobotJointsPoints(QVector<Point> points);
	void setPastTCPsBufferSize(int newSize);
	void setViewAngles(float rotX, float rotY, float rotZ);
protected:
	void initializeGL();
	void resizeGL(int width, int height);
	void paintGL();
	void mousePressEvent(QMouseEvent* event);
	void mouseMoveEvent(QMouseEvent* event);
private:
	void draw();
	void drawPastTCPs();
	void drawXYZ();
	GLfloat rotationX;
	GLfloat rotationY;
	GLfloat rotationZ;
	QPoint lastPos;
	QVector<Point> jointsPoints;
	int pastTCPBufferSize;
	QList<Point> pastTCPs;
signals:

public slots:
};

#endif // ROBOTVISUALISATIONWIDGET_H
