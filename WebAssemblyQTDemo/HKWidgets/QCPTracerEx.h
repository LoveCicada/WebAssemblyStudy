#pragma once

#include <QObject>
#include "QCustomPlot.h"


///
/// \brief The XxwTracer class:��ͼ������ʾ�������λ�õ�x,yֵ��׷����ʾ��
///


//QCPTracerEx
class QCPTracerEx : public QObject
{
    Q_OBJECT

public:
#if 1

    enum TracerType
    {
        XAxisTracer,//������x������ʾxֵ
        YAxisTracer,//������y������ʾyֵ
        DataTracer//��ͼ����ʾx,yֵ
    };

#endif // 0

    explicit QCPTracerEx(QCustomPlot* _plot, TracerType _type, QObject* parent = Q_NULLPTR);
    ~QCPTracerEx();
    void setPen(const QPen& pen);
    void setBrush(const QBrush& brush);
    void setText(const QString& text);
    void setLabelPen(const QPen& pen);
    void updatePosition(double xValue, double yValue);
    void setVisible(bool m_visible);

protected:
    bool m_visible;//�Ƿ�ɼ�
    TracerType m_type;//����
    // int m_type;
    QCustomPlot* m_plot;//ͼ��
    QCPItemTracer* m_tracer;//���ٵĵ�
    QCPItemText* m_label;//��ʾ����ֵ
    QCPItemLine* m_arrow;//��ͷ
};


///
/// \brief The XxwCrossLine class:������ʾ����ƶ������е����λ�õ�ֱ��
///
/// QCPTraceLineEx
class QCPTraceLineEx : public QObject
{
public:
    enum LineType
    {
        VerticalLine,//��ֱ��
        HorizonLine, //ˮƽ��
        Both//ͬʱ��ʾˮƽ�ʹ�ֱ��
    };
    explicit QCPTraceLineEx(QCustomPlot* _plot, LineType _type = VerticalLine, QObject* parent = Q_NULLPTR);
    ~QCPTraceLineEx();
    void initLine();
    void updatePosition(double xValue, double yValue);
    void setVisible(bool vis);

protected:
    bool m_visible;//�Ƿ�ɼ�
    LineType m_type;//����
    QCustomPlot* m_plot;//ͼ��
    QCPItemStraightLine* m_lineV; //��ֱ��
    QCPItemStraightLine* m_lineH; //ˮƽ��
};

