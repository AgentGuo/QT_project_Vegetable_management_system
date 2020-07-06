#include "widgetpainter.h"
#include <QPainter>
//#include <QRect>
//#include <QPointF>
//#include <QLineF>

WidgetPainter::WidgetPainter(QWidget* parent) : QWidget(parent)
{
	setFixedSize(360, 360); //�̶���С
	setWindowTitle("Hello DevDiv!");
}

WidgetPainter::~WidgetPainter()
{

}

void WidgetPainter::paintEvent(QPaintEvent *)
{
	// ��һ��ֱ��
	QPainter painter(this);             // ����QPainterһ������
	QPen pen;

	//pen.setStyle(Qt::DashLine);        
	pen.setColor(Qt::red);           // ���û���Ϊ��ɫ
	painter.setPen(pen);                // ���û���
	painter.drawLine(rect().topLeft(), rect().bottomRight());

	// ��һ�����ľ���
	pen.setColor(Qt::darkRed);
	painter.setPen(pen);
	painter.drawRect(1, 1, 100, 100);     //painter.drawRect(QRect(1, 1, 100, 100));


}