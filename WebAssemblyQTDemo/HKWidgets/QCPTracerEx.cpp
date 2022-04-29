#include "QCPTracerEx.h"

QCPTracerEx::QCPTracerEx(QCustomPlot* _plot, TracerType _type, QObject* parent)
    : QObject(parent),
    m_plot(_plot),
    m_type(_type)
{
    m_visible = true;
    m_tracer = Q_NULLPTR;// ���ٵĵ�
    m_label = Q_NULLPTR;// ��ʾ����ֵ
    m_arrow = Q_NULLPTR;// ��ͷ
    if (m_plot)
    {
        QColor clrDefault(0, 139, 69);
        QBrush brushDefault(Qt::NoBrush);
        QPen penDefault(clrDefault);
        //        penDefault.setBrush(brushDefault);
        penDefault.setWidthF(1);

        m_tracer = new QCPItemTracer(m_plot);
        m_tracer->setStyle(QCPItemTracer::tsCircle);
        m_tracer->setPen(penDefault);
        m_tracer->setBrush(brushDefault);

        m_label = new QCPItemText(m_plot);
        m_label->setLayer("overlay");
        m_label->setClipToAxisRect(false);
        m_label->setPadding(QMargins(5, 5, 5, 5));
        m_label->setBrush(brushDefault);
        m_label->setPen(penDefault);
        m_label->position->setParentAnchor(m_tracer->position);
        //        m_label->setFont(QFont("����", 8));
        m_label->setFont(QFont("Arial", 8));
        m_label->setColor(clrDefault);
        m_label->setText("");

        m_arrow = new QCPItemLine(m_plot);
        QPen  arrowPen(clrDefault, 1);
        m_arrow->setPen(penDefault);
        m_arrow->setLayer("overlay");
        m_arrow->setClipToAxisRect(false);
        m_arrow->setHead(QCPLineEnding::esSpikeArrow);//����ͷ��Ϊ��ͷ��״

        switch (m_type)
        {
        case XAxisTracer:
        {
            m_tracer->position->setTypeX(QCPItemPosition::ptPlotCoords);
            m_tracer->position->setTypeY(QCPItemPosition::ptAxisRectRatio);
            m_tracer->setSize(7);
            m_label->setPositionAlignment(Qt::AlignTop | Qt::AlignHCenter);

            m_arrow->end->setParentAnchor(m_tracer->position);
            m_arrow->start->setParentAnchor(m_arrow->end);
            m_arrow->start->setCoords(0, 20);//ƫ����
            break;
        }
        case YAxisTracer:
        {
            m_tracer->position->setTypeX(QCPItemPosition::ptAxisRectRatio);
            m_tracer->position->setTypeY(QCPItemPosition::ptPlotCoords);
            m_tracer->setSize(7);
            m_label->setPositionAlignment(Qt::AlignRight | Qt::AlignHCenter);

            m_arrow->end->setParentAnchor(m_tracer->position);
            m_arrow->start->setParentAnchor(m_label->position);
            m_arrow->start->setCoords(-20, 0);//ƫ����
            break;
        }
        case DataTracer:
        {
            m_tracer->position->setTypeX(QCPItemPosition::ptPlotCoords);
            m_tracer->position->setTypeY(QCPItemPosition::ptPlotCoords);
            m_tracer->setSize(5);

            m_label->setPositionAlignment(Qt::AlignLeft | Qt::AlignVCenter);

            m_arrow->end->setParentAnchor(m_tracer->position);
            m_arrow->start->setParentAnchor(m_arrow->end);
            m_arrow->start->setCoords(20, 0);
            break;
        }
        default:
            break;
        }
        setVisible(false);
    }
}

QCPTracerEx::~QCPTracerEx()
{
    if (m_plot)
    {
        if (m_tracer)
            m_plot->removeItem(m_tracer);
        if (m_label)
            m_plot->removeItem(m_label);
        if (m_arrow)
            m_plot->removeItem(m_arrow);
    }
}

void QCPTracerEx::setPen(const QPen& pen)
{
    if (m_tracer)
        m_tracer->setPen(pen);
    if (m_arrow)
        m_arrow->setPen(pen);
}

void QCPTracerEx::setBrush(const QBrush& brush)
{
    if (m_tracer)
        m_tracer->setBrush(brush);
}

void QCPTracerEx::setLabelPen(const QPen& pen)
{
    if (m_label)
    {
        m_label->setPen(pen);
        m_label->setBrush(Qt::NoBrush);
        m_label->setColor(pen.color());
    }
}

void QCPTracerEx::setText(const QString& text)
{
    if (m_label)
        m_label->setText(text);
}

void QCPTracerEx::setVisible(bool vis)
{
    m_visible = vis;
    if (m_tracer)
        m_tracer->setVisible(m_visible);
    if (m_label)
        m_label->setVisible(m_visible);
    if (m_arrow)
        m_arrow->setVisible(m_visible);
}

void QCPTracerEx::updatePosition(double xValue, double yValue)
{
    if (!m_visible)
    {
        setVisible(true);
        m_visible = true;
    }

    if (yValue > m_plot->yAxis->range().upper)
        yValue = m_plot->yAxis->range().upper;

    //translate stamp to date time
    int nDateTime = (int)xValue;
    QDateTime qDateTime = QDateTime::fromSecsSinceEpoch(nDateTime);
    QString strDateTime = qDateTime.toString("hh:mm:ss");

    switch (m_type)
    {
    case XAxisTracer:
    {
        m_tracer->position->setCoords(xValue, 1);
        m_label->position->setCoords(0, 20);//����X��lable��λ��
        m_arrow->start->setCoords(0, 15);
        m_arrow->end->setCoords(0, 0);
        setText(strDateTime);
        break;
    }
    case YAxisTracer:
    {
        m_tracer->position->setCoords(0, yValue);
        m_label->position->setCoords(-50, -10);
        m_arrow->start->setCoords(30, 10);
        m_arrow->end->setCoords(0, 0);
        setText(QString::number(yValue));
        break;
    }
    case DataTracer:
    {
        m_tracer->position->setCoords(xValue, yValue);
        m_label->position->setCoords(20, 0);
        setText(QString("X:%1--Y:%2").arg(strDateTime).arg(yValue));
        break;
    }
    default:
        break;
    }
}


/// ////////////////////

QCPTraceLineEx::QCPTraceLineEx(QCustomPlot* _plot, LineType _type, QObject* parent)
    : QObject(parent),
    m_type(_type),
    m_plot(_plot)
{
    m_lineV = Q_NULLPTR;
    m_lineH = Q_NULLPTR;
    initLine();
}

QCPTraceLineEx::~QCPTraceLineEx()
{
    if (m_plot)
    {
        if (m_lineV)
            m_plot->removeItem(m_lineV);
        if (m_lineH)
            m_plot->removeItem(m_lineH);
    }
}

void QCPTraceLineEx::initLine()
{
    if (m_plot)
    {
        QColor color(0, 229, 255);
        QPen linesPen(color, 2, Qt::DashLine);

        if (VerticalLine == m_type || Both == m_type)
        {
            m_lineV = new QCPItemStraightLine(m_plot);//��ֱ��
            m_lineV->setLayer("overlay");
            m_lineV->setPen(linesPen);
            m_lineV->setClipToAxisRect(true);
            m_lineV->point1->setCoords(0, 0);
            m_lineV->point2->setCoords(0, 0);
        }

        if (HorizonLine == m_type || Both == m_type)
        {
            m_lineH = new QCPItemStraightLine(m_plot);//ˮƽ��
            m_lineH->setLayer("overlay");
            m_lineH->setPen(linesPen);
            m_lineH->setClipToAxisRect(true);
            m_lineH->point1->setCoords(0, 0);
            m_lineH->point2->setCoords(0, 0);
        }
    }
}

void QCPTraceLineEx::updatePosition(double xValue, double yValue)
{
    if (VerticalLine == m_type || Both == m_type)
    {
        if (m_lineV)
        {
            m_lineV->point1->setCoords(xValue, m_plot->yAxis->range().lower);
            m_lineV->point2->setCoords(xValue, m_plot->yAxis->range().upper);
        }
    }

    if (HorizonLine == m_type || Both == m_type)
    {
        if (m_lineH)
        {
            m_lineH->point1->setCoords(m_plot->xAxis->range().lower, yValue);
            m_lineH->point2->setCoords(m_plot->xAxis->range().upper, yValue);
        }
    }
}

void QCPTraceLineEx::setVisible(bool vis)
{
    if (m_lineV)
        m_lineV->setVisible(vis);
    if (m_lineH)
        m_lineH->setVisible(vis);
}
