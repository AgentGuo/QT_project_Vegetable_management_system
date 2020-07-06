#include "widgetpainter.h"
#include <QPainter>
//#include <QRect>
//#include <QPointF>
//#include <QLineF>

WidgetPainter::WidgetPainter(QWidget* parent) : QWidget(parent)
{
	setFixedSize(360, 360); //固定大小
	setWindowTitle("Hello DevDiv!");
}

WidgetPainter::~WidgetPainter()
{

}

void WidgetPainter::paintEvent(QPaintEvent *)
{
	// 画一条直线
	QPainter painter(this);             // 创建QPainter一个对象
	QPen pen;

	//pen.setStyle(Qt::DashLine);        
	pen.setColor(Qt::red);           // 设置画笔为黄色
	painter.setPen(pen);                // 设置画笔
	painter.drawLine(rect().topLeft(), rect().bottomRight());

	// 画一个空心矩形
	pen.setColor(Qt::darkRed);
	painter.setPen(pen);
	painter.drawRect(1, 1, 100, 100);     //painter.drawRect(QRect(1, 1, 100, 100));


}