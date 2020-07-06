#ifndef WIDGETPAINTER_H
#define WIDGETPAINTER_H


#include <QWidget>

class WidgetPainter : public QWidget
{
	//Q_OBJECT
public:
	WidgetPainter(QWidget* parent = 0);
	~WidgetPainter();
	void paintEvent(QPaintEvent *);
};

#endif