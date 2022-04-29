
#include "QCustomPlotEx.h"
#include "CChartView.h"
#include <QDebug>

#define UPDATESTEP  10
#define ONESEC      1000		//1s=1000ms
#define FRAME_RATE  25

QCustomPlotEx::QCustomPlotEx(QWidget* parent)
    :QCustomPlot(parent)
    , m_isShowTracer(false)
    , m_xTracer(Q_NULLPTR)
    , m_yTracer(Q_NULLPTR)
    , m_dataTracers(QList<QCPTracerEx*>())
    , m_lineTracer(Q_NULLPTR)
    , m_nIndex(0)
    , m_fIndex(0)
    , m_keyOnlyAndAllZoom(true)
    , m_mouseOnlyAndAllDrag(true)
{
    
    m_isShowTracer = true;
    m_MouseFocus = false;
    //    m_timer->start(50);
    Initchart();

    
    connect(this, &QCustomPlotEx::SyncCross, dynamic_cast<CChartView*>(parent), &CChartView::SyncCrossLine);
    connect(this, &QCustomPlotEx::SynEraserCross, dynamic_cast<CChartView*>(parent), &CChartView::SyncEraserCrossLine);
    connect(this, &QCustomPlotEx::SelectChart, dynamic_cast<CChartView*>(parent), &CChartView::SelectChart);
    connect(this, &QCustomPlotEx::SynZoom, dynamic_cast<CChartView*>(parent), &CChartView::SynZoomSlot);
    connect(this, &QCustomPlotEx::SynPress, dynamic_cast<CChartView*>(parent), &CChartView::SynPressSlot);
    connect(this, &QCustomPlotEx::SynTrans, dynamic_cast<CChartView*>(parent), &CChartView::SynTransSlot);
    connect(this, &QCustomPlotEx::SynRelease, dynamic_cast<CChartView*>(parent), &CChartView::SynRelaeseSlot);
}

void QCustomPlotEx::Initchart()
{
    m_xTracer = new QCPTracerEx(this, QCPTracerEx::XAxisTracer);//x��
    m_yTracer = new QCPTracerEx(this, QCPTracerEx::YAxisTracer);//y��
    m_lineTracer = new QCPTraceLineEx(this, QCPTraceLineEx::Both);//ֱ��

    connect(&m_DataPlayTimer, &QTimer::timeout, this, &QCustomPlotEx::playLineSlot);
    connect(this, &QCustomPlotEx::mouseWheel, this, &QCustomPlotEx::onMouseWheel);

    int interval = ONESEC / FRAME_RATE;	//25fps => 40ms 
    m_DataPlayTimer.setInterval(interval);

    replot();//��ʾ
}

void QCustomPlotEx::playLineSlot()
{
    //��ȡȫ����Χ����ǰˮƽ�᷶Χ
    auto dataRange = graph()->data().data()->dataRange();
    auto axisRange = xAxis->range();
    auto start = dataRange.begin();
    auto end = dataRange.end();
    auto lower = axisRange.lower;
    auto upper = axisRange.upper;

    if (m_DataPlayTimer.isActive())
    {
        m_fIndex += m_dPlayStep;
    }

    if ((m_fIndex >= upper) && (upper < end) && (m_DataPlayTimer.isActive()))
    {
        QCPAxis* ax = axisRect()->rangeDragAxis(Qt::Horizontal);
        double diff = m_dPlayStep;
        ax->setRange(ax->range().lower + diff, ax->range().upper + diff);
        replot();
    }

    QCustomPlot::update();
}

void QCustomPlotEx::showTrackerItem(const QPoint& pt)
{
    if (!m_isShowTracer)
        return;

    //��ǰ���λ�ã��������꣩
    int x_pos = pt.x();
    int y_pos = pt.y();

    //��������ת��ʵ�ʵ�x,y�������
    float x_val = this->xAxis->pixelToCoord(x_pos);
    float y_val = this->yAxis->pixelToCoord(y_pos);

    m_xTracer->setVisible(true);
    m_xTracer->updatePosition(x_val, y_val);

    m_yTracer->setVisible(true);
    m_yTracer->updatePosition(x_val, y_val);

    int nTracerCount = m_dataTracers.count();
    int nGraphCount = graphCount();
    if (nTracerCount < nGraphCount)
    {
        for (int i = nTracerCount; i < nGraphCount; ++i)
        {
            QCPTracerEx* tracer = new QCPTracerEx(this, QCPTracerEx::DataTracer);
            m_dataTracers.append(tracer);
        }
    }
    else if (nTracerCount > nGraphCount)
    {
        for (int i = nGraphCount; i < nTracerCount; ++i)
        {
            QCPTracerEx* tracer = m_dataTracers[i];
            if (tracer)
            {
                tracer->setVisible(false);
            }
        }
    }
    for (int i = 0; i < nGraphCount; ++i)
    {
        QCPTracerEx* tracer = m_dataTracers[i];
        if (!tracer)
            tracer = new QCPTracerEx(this, QCPTracerEx::DataTracer);
        tracer->setVisible(true);
        QPen pen;
        QColor color(255, 48, 48);
        pen.setColor(color);//ʮ�ֶԱ�����ֵ�����ɫ
        tracer->setPen(pen);
        tracer->setBrush(Qt::NoBrush);
        tracer->setLabelPen(pen);
        auto iter = this->graph(i)->data()->findBegin(x_val);
        double value = iter->mainValue();
        tracer->updatePosition(x_val, value);
    }
    
    m_lineTracer->setVisible(true);
    m_lineTracer->updatePosition(x_val, y_val);

    this->replot();//�����ػ�

}


void QCustomPlotEx::mouseMoveEvent(QMouseEvent* event)
{
    m_MouseFocus = true;
    m_MousePos = event->pos();
    emit SyncCross(m_MousePos);

    //TRUE -- ALL
    //FALSE -- SINGLE
    if (m_mouseOnlyAndAllDrag == true) {
        emit SynTrans(event);
    }
    else{
        QCustomPlot::mouseMoveEvent(event);
    }
}

void QCustomPlotEx::mousePressEvent(QMouseEvent* event)
{
    QCustomPlot::mousePressEvent(event);

    if (event->button() == Qt::LeftButton) {

        QCustomPlotEx::update();
        if (m_mouseOnlyAndAllDrag == true) {
            emit SynPress(event);
        }
        else {
            QCustomPlot::mousePressEvent(event);
        }
    }
}

void QCustomPlotEx::mouseReleaseEvent(QMouseEvent* event)
{
    //m_mouseOnlyAndAllDrag = true;
    emit SynRelease(event);
}

//��ɫ�α�
void QCustomPlotEx::paintEvent(QPaintEvent* event)
{
    QCustomPlot::paintEvent(event);

     QPainter painter(this);
     QPen pen(Qt::red);
     pen.setWidth(2);
     painter.setPen(pen);

     QRect rt = this->plotLayout()->element(0, 0)->rect();

     auto data = graph()->data().data();
     auto dataRange = data->dataRange();
     
     auto startIndex = data->dataRange().begin();
     auto endIndex = data->dataRange().end();

     m_fIndex = std::max((float)startIndex, m_fIndex);
     m_fIndex = std::min((float)endIndex, m_fIndex);

     int index = (int)(m_fIndex);
     auto keyValue = data->at(index)->key; 
     auto fPosx = xAxis->coordToPixel(keyValue);

     //�����α겻����ͼ�����
     if (fPosx >= rt.left() && fPosx < rt.right())
     {
         painter.drawLine(fPosx, rt.top(), fPosx, rt.bottom());
     }
     //�����α겻����ͼ���ұ�
     if (fPosx >= rt.right())
     {
         fPosx = rt.right();
         painter.drawLine(fPosx, rt.top(), fPosx, rt.bottom());
     }

     //ѡ��ͼ�����������ñ���ɫ��������ѡ��
     bool bSelect = hasFocus();
     if (bSelect)
     {
         qDebug() << "select" << graph()->name();
         QColor color(0,75,130);
         setBackground(QBrush(color));
         emit SelectChart(this);
     }
     else
     {
         QColor color(63, 63, 63);
         setBackground(QBrush(color));
     }

}

void QCustomPlotEx::leaveEvent(QEvent* event)
{
    Q_UNUSED(event);

    m_MouseFocus = false;
    emit SynEraserCross();

}

void QCustomPlotEx::wheelEvent(QWheelEvent* event)
{
    if (m_keyOnlyAndAllZoom == true) {
        emit SynZoom(event);//�����¼����淢���ź�
    }
    else {
        QCustomPlot::wheelEvent(event);
    }
}

void QCustomPlotEx::keyPressEvent(QKeyEvent* event)
{
    m_mouseOnlyAndAllDrag = true;
    if (event->key() == Qt::Key_Shift) {
        m_keyOnlyAndAllZoom = false;
    }
    if (event->key() == Qt::Key_Shift) {
        m_mouseOnlyAndAllDrag = false;
    }

    QCustomPlot::keyPressEvent(event);
}

void QCustomPlotEx::keyReleaseEvent(QKeyEvent* event)
{
    m_mouseOnlyAndAllDrag = true;

    if (event->key() == Qt::Key_Shift) {
        m_keyOnlyAndAllZoom = true;
    }
    if (event->key() == Qt::Key_Shift) {
        m_mouseOnlyAndAllDrag = true;
    }

    QCustomPlot::keyReleaseEvent(event);
}

void QCustomPlotEx::eraserTracker()
{
    m_xTracer->setVisible(false);
    m_yTracer->setVisible(false);
    m_lineTracer->setVisible(false);

    this->replot();//�����ػ�

}

void QCustomPlotEx::onMouseWheel(QWheelEvent* event)
{
    int delta = event->delta();
    qDebug() << "del=" << delta;
    static int num = 1;
    if (delta > 0)
    {
        num += 2;
        num = std::min(8, num);
    }
    else if (delta < 0)
    {
        num -= 2;
        num = std::max(4, num);
    }
    qDebug() << "num=" << num;
    xAxis->ticker()->setTickCount(num);
}

void QCustomPlotEx::showTracer(bool show)
{
    m_isShowTracer = show;
    if (m_xTracer)
        m_xTracer->setVisible(m_isShowTracer);

    foreach(QCPTracerEx * tracer, m_dataTracers)
    {
        if (tracer)
            tracer->setVisible(m_isShowTracer);
    }
    if (m_lineTracer)
        m_lineTracer->setVisible(m_isShowTracer);
}

bool QCustomPlotEx::isShowTracer()
{
    return m_isShowTracer;
}

void QCustomPlotEx::setMousePos(QPoint& pt)
{
    m_MousePos = pt;
}

QPoint QCustomPlotEx::getMousePos()
{
    return m_MousePos;
}

bool QCustomPlotEx::getMouseFocus()
{
    return m_MouseFocus;
}

void QCustomPlotEx::chartZoom(QWheelEvent* event)
{
    QCustomPlot::wheelEvent(event);//ʵ�����ŵĺ���
}

void QCustomPlotEx::chartTrans(QMouseEvent* event)
{
    QCustomPlot::mouseMoveEvent(event);
}

void QCustomPlotEx::chartPress(QMouseEvent* event)
{
    QCustomPlot::mousePressEvent(event);
}

void QCustomPlotEx::chartRelease(QMouseEvent* event)
{
    QCustomPlot::mouseReleaseEvent(event);
}

bool QCustomPlotEx::play(double dRate)
{
    bool bRet = true;
    int dataCount = graph()->dataCount();
    int dataIndex = graph()->dataCount() * dRate;
    m_nIndex = dataIndex;
    m_nPlayStepCount = 0;

    m_DataPlayTimer.start();
    return bRet;
}

bool QCustomPlotEx::stop()
{
    bool bRet = true;
    m_DataPlayTimer.stop();
    return bRet;
}

bool QCustomPlotEx::seek(double dRate)
{
    bool bRet = true;
    int dataCount = graph()->dataCount();
    int dataIndex = graph()->dataCount() * dRate;
    m_nIndex = dataIndex;

    m_fIndex = dataIndex;

    QCustomPlotEx::update();
    return bRet;
}

bool QCustomPlotEx::rotate(const CCRoateData& data)
{
    bool bRet = true;


    return true;
}

bool QCustomPlotEx::trans(const CCTransData& data)
{
    bool bRet = true;

    QCPAxis* ax = axisRect()->rangeDragAxis(Qt::Horizontal);
    double diff = (double)(data.pt.x());
    //change the current xAxis range
    ax->setRange(ax->range().lower + diff, ax->range().upper + diff);

    replot();

    return bRet;
}

bool QCustomPlotEx::setPlaySetp(double dStep)
{
    bool bRet = true;

    int dataCount = graph()->dataCount();
    m_dPlayStep = dStep * (double)dataCount;

    return bRet;
}

bool QCustomPlotEx::backToDefault()
{
    bool bRet = true;
    bool foundRange;
    QCP::SignDomain inSignDomain = QCP::sdBoth;
    auto rangeData = graph()->getKeyRange(foundRange, inSignDomain);

    QCPAxis* pAx = axisRect()->rangeDragAxis(Qt::Horizontal);
    pAx->setRange(rangeData.lower, rangeData.upper);
    replot();

    return bRet;

}

bool QCustomPlotEx::getCurHorAxisRange(QCPRange& range)
{
    bool bRet = true;
    
    auto ax = axisRect()->rangeDragAxis(Qt::Horizontal);
    range = ax->range();

    return bRet;
}
