#pragma once

#include "QCPTracerEx.h"
#include "QCustomPlot.h"
#include "CChartBaseData.h"

class QCustomPlotEx :public QCustomPlot
{
    Q_OBJECT

public:
    QCustomPlotEx(QWidget* parent = NULL);
    void Initchart();

signals:
    void SyncCross(QPoint& point);
    void SynEraserCross();
    void SelectChart(QCustomPlotEx*);
    void SynZoom(QWheelEvent* event);
    void SynTrans(QMouseEvent* event);
    void SynPress(QMouseEvent* event);
    void SynRelease(QMouseEvent* event);

public slots:
    void onMouseWheel(QWheelEvent* event);
    void playLineSlot();

protected:
    virtual void mouseMoveEvent(QMouseEvent* event);
    virtual void mousePressEvent(QMouseEvent* event);
    virtual void mouseReleaseEvent(QMouseEvent* event);
    virtual void paintEvent(QPaintEvent* event);
    virtual void leaveEvent(QEvent* event);
    virtual void wheelEvent(QWheelEvent* event);
    virtual void keyPressEvent(QKeyEvent* event);
    virtual void keyReleaseEvent(QKeyEvent* event);

public:
    void showTracer(bool show);
    void eraserTracker();
    bool isShowTracer();
    void showTrackerItem(const QPoint& pt);
    void setMousePos(QPoint& pt);
    QPoint getMousePos();
    bool getMouseFocus();
    void chartZoom(QWheelEvent* event);
    void chartTrans(QMouseEvent* event);
    void chartPress(QMouseEvent* event);
    void chartRelease(QMouseEvent* event);
    bool backToDefault();

    bool play(double dRate);
    bool stop();
    bool seek(double dRate);

    bool rotate(const CCRoateData& data);
    //horizon trans
    bool trans(const CCTransData& data);
    bool setPlaySetp(double dStep);

    bool getCurHorAxisRange(QCPRange& range);

private:
    
    bool m_isShowTracer;//�Ƿ���ʾ׷�����������ͼ���ƶ�����ʾ��Ӧ��ֵ��

    QCPTracerEx* m_xTracer;//x��
    QCPTracerEx* m_yTracer;//y��
    QList<QCPTracerEx*> m_dataTracers;//
    QCPTraceLineEx* m_lineTracer;//ֱ��
    
    int m_nPlayStepCount;
    int m_nIndex;
    float m_fIndex;
    QPoint m_MousePos;
    bool m_MouseFocus;
    bool m_keyOnlyAndAllZoom;
    bool m_mouseOnlyAndAllDrag;

    //�α겥�Ŷ�ʱ��
    QTimer m_DataPlayTimer;
    double m_dPlayStep;

};
