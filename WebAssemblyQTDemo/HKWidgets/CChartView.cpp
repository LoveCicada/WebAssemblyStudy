
#include"CChartView.h"


CChartView::CChartView(QWidget* parent)
    :QWidget(parent)
{
	initData();
}


CChartView::~CChartView()
{

}

QcpVec& CChartView::GetQcpVec()
{
	return m_pQcpVec;
}

void CChartView::SetChart(const ChartPropertyVec& chartProVec, const FlightItemDataVector& flightDataList)
{
	SetChartProperty(chartProVec);
	SetChartData(flightDataList);
	SetDefaultChartData(flightDataList);
	UpdateChartView();
}

void CChartView::SetChartProperty(const ChartPropertyVec& chartProVec)
{
	m_ChartProVec = chartProVec;
}

ChartPropertyVec& CChartView::GetChartProperty()
{
	return m_ChartProVec;
}

bool CChartView::SetChartData(const FlightItemDataVector& flightDataList)
{
	bool bRet = true;
	m_flightList = flightDataList;

	return bRet;
}

bool CChartView::SetDefaultChartData(const FlightItemDataVector& flightDataList)
{
	bool bRet = true;
	m_DefaultFlightList = flightDataList;

	auto itorSrc = flightDataList.begin();
	if (itorSrc == flightDataList.end())
		return false;

	//clear old data
	m_DefaultFlightList.clear();
	//depth copy
	for (; itorSrc != flightDataList.end(); ++itorSrc)
	{

#if 0

		CFlightItemData* pData;
		auto data = (*itorSrc);
		pData = data.Clone();
		m_DefaultFlightList.push_back(*pData);

#else

		CFlightItemData data;
		data.strCategory = itorSrc->strCategory;
		data.strLabel = itorSrc->strLabel;

		auto paramDataVec = itorSrc->vecParameterData;
		auto itorParam = paramDataVec.begin();
		for (; itorParam != paramDataVec.end(); ++itorParam)
		{
			CParameterData paramData;
			paramData.time = itorParam->time;
			paramData.dValue = itorParam->dValue;
			data.vecParameterData.push_back(paramData);
		}

		m_DefaultFlightList.push_back(data);

#endif // 0

	}

	return bRet;
}

void CChartView::initData()
{
	m_bFullScreen = false;
	m_IndexData = 0;
	m_pChartSelect = NULL;

	//connect(this, &CChartView::UpdateCurveDataSignal, this, &CChartView::UpdateCurveDataSlot, Qt::QueuedConnection);
    connect(this, SIGNAL(UpdateCurveDataSignal(const QCPRange&)), this, SLOT(UpdateCurveDataSlot(const QCPRange&))/*, Qt::QueuedConnection*/);
                    
}

void CChartView::Init()
{
	for (auto itor = m_pQcpVec.begin(); itor != m_pQcpVec.end(); ++itor)
	{
		if (*itor)
		{
			delete (*itor);
		}
	}
	m_pQcpVec.clear();

	m_QcpIndex = 0;
	ChartPropertyItor proItor = m_ChartProVec.begin();
	for (; proItor != m_ChartProVec.end(); ++proItor)
	{
		AddSeries(*proItor);
	}

	initData();
}

void CChartView::InitCurve(QCustomPlotEx* pCustomPlot, const CChartViewProperty& chartViewProperty)
{
	if (!pCustomPlot)
		return;

	QCPGraph* pQCPGraph = pCustomPlot->graph();
	if (pQCPGraph)
	{
		QPen pen;
		pen.setColor(chartViewProperty.color);
		pen.setWidth(chartViewProperty.dWidth);
		pQCPGraph->setPen(pen);
		pQCPGraph->rescaleAxes(true);
		pQCPGraph->setName(chartViewProperty.strTitle);
		//pQCPGraph->dataPixelPosition(0);
	}

	QColor colorBk(63, 63, 63);
	pCustomPlot->setBackground(QBrush(colorBk));//����ͼ������
	//pCustomPlot->selectionRect()->setPen(QPen(Qt::black, 1, Qt::DashLine));//����ѡ�����ʽ����
	//pCustomPlot->selectionRect()->setBrush(QBrush(QColor(0, 0, 100, 50)));//ѡ��ı���
	//pCustomPlot->setSelectionRectMode(QCP::SelectionRectMode::srmZoom);//����ѡ��
	pCustomPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);//��ק������
	pCustomPlot->graph()->setSmooth(true);

	pCustomPlot->axisRect()->setRangeDragAxes(pCustomPlot->xAxis, nullptr);//��קֻ��x��仯��y�᲻��
	pCustomPlot->axisRect()->setRangeZoomAxes(pCustomPlot->xAxis, nullptr);//����ֻ��x��仯��y�᲻��
	
	pCustomPlot->legend->setBrush(QColor(255,255,255,100));//����ͼ�б���͸����ͼ�пɼ�
	pCustomPlot->legend->setVisible(true);//��ʾͼ��
	QColor color(138, 138, 138);
	pCustomPlot->xAxis->grid()->setPen(QPen(color, 1, Qt::PenStyle::DashLine));//x���ߵ���ɫ
	pCustomPlot->yAxis->grid()->setPen(QPen(color, 1, Qt::PenStyle::DashLine));//y���ߵ���ɫ
	pCustomPlot->xAxis->setBasePen(color);//x����ɫ
	pCustomPlot->yAxis->setBasePen(color);//y����ɫ
	pCustomPlot->xAxis->setTickPen(color);//x�����̶���ɫ
	pCustomPlot->yAxis->setTickPen(color);//y�����̶���ɫ
	pCustomPlot->xAxis->setSubTickPen(color);//x��ο̶���ɫ
	pCustomPlot->yAxis->setSubTickPen(color);//y��ο̶���ɫ
	pCustomPlot->xAxis->setTickLabelColor(color);//x����ֵ��ɫ
	pCustomPlot->yAxis->setTickLabelColor(color);//y����ֵ��ɫ

	pCustomPlot->axisRect()->setupFullAxesBox(true);//�ı߶���ʾxy��
	pCustomPlot->xAxis->ticker()->setTickCount(6);//�������̶�����

	//���� x2,y2
	pCustomPlot->xAxis2->setVisible(false);
	pCustomPlot->yAxis2->setVisible(false);

	QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);//������X��
	dateTicker->setDateTimeFormat("hh:mm:ss");//���ڸ�ʽ(�ɲο�QDateTime::fromString()����)
	pCustomPlot->xAxis->setTicker(dateTicker);//����X��Ϊʱ����
	pCustomPlot->setOpenGl(true);

}

bool CChartView::AddSeries(const CChartViewProperty& chartViewProperty)
{
	bool bRet = true;

	QCustomPlotEx* pCustomPlot = new QCustomPlotEx(this);
	pCustomPlot->addGraph();
	InitCurve(pCustomPlot, chartViewProperty);

	m_pQcpVec.push_back(pCustomPlot);

	return bRet;
}

void CChartView::Layout()
{

	if (m_bFullScreen)
	{
		LayoutFull();
	}
	else
	{
		LayoutDefault();
	}

}

void CChartView::LayoutDefault()
{
	QRect rtClient = rect();

	int offsetH = 0;
	int offsetW = 0;
	int chartNum = m_pQcpVec.size();
	if (chartNum <= 0)
	{
		return;
	}
	int chartWidth = rtClient.width();
	int chartHeight = rtClient.height() / chartNum;

	QRect rt;
	for (int i = 0; i < m_pQcpVec.size(); ++i)
	{
		rt.setTop(rtClient.top() + offsetH + chartHeight * i);
		rt.setLeft(rtClient.left() + offsetW);
		rt.setWidth(chartWidth);
		rt.setHeight(chartHeight);
		m_pQcpVec[i]->setGeometry(rt);
		m_pQcpVec[i]->show();

	}
}

void CChartView::LayoutFull()
{
	QRect rtClient = rect();

	int offsetH = 0;
	int offsetW = 0;
	int chartWidth = rtClient.width();
	int chartHeight = rtClient.height();

	QRect rt;
	rt.setTop(rtClient.top() + offsetH);
	rt.setLeft(rtClient.left() + offsetW);
	rt.setWidth(chartWidth);
	rt.setHeight(chartHeight);
	if (m_pChartSelect)
	{

		QcpItor qcpItor = m_pQcpVec.begin();
		for (; qcpItor != m_pQcpVec.end(); ++qcpItor)
		{
			if (*qcpItor)
			{
				(*qcpItor)->hide();
			}
		}

		m_pChartSelect->setGeometry(rt);
		QRect rt = m_pChartSelect->geometry();

		m_pChartSelect->show();
	}
	else
	{
		Layout();
	}
}

void CChartView::UpdateChartView()
{
	Init();
	Layout();
	loadSampleData(m_flightList);
}

void CChartView::resizeEvent(QResizeEvent* e)
{
	
	Layout();
}

void CChartView::loadSampleData(const FlightItemDataVector& flightDataList)
{

	if (flightDataList.size() <= 0)
	{
		return;
	}

	for (int k = 0; k < m_pQcpVec.size(); ++k)
	{
		auto vecData = flightDataList.at(k).vecParameterData;

		int numIndex = vecData.size();//1
		int dataIndex = 0;
		m_pQcpVec[k]->graph()->data()->clear();
		for (int kk = 0; kk < numIndex; ++kk)
		{
			if (dataIndex > vecData.size() || vecData.size() <= 0)
			{
				break;
			}
			double dValue = vecData[dataIndex].dValue;
			auto time = vecData[dataIndex].time;
			double dTime = time.toSecsSinceEpoch();

			dataIndex++;
			m_pQcpVec[k]->graph()->addData(dTime, dValue);
			
		}

		if (numIndex > 0)
		{
			auto startTime = vecData[0].time;
			double dStartTime = startTime.toSecsSinceEpoch();

			auto endTime = vecData[numIndex-1].time;
			double dEndTime = endTime.toSecsSinceEpoch();

			m_pQcpVec[k]->xAxis->setRange(dStartTime, dEndTime);
		}

		m_pQcpVec[k]->setPlaySetp(m_dChartPlayStep);
		m_pQcpVec[k]->graph()->rescaleAxes(true);
		m_pQcpVec[k]->replot(QCustomPlot::rpQueuedReplot);

	}
}

bool CChartView::play(double dRate)
{
	bool bRet = true;

	QcpItor qcpItor = m_pQcpVec.begin();
	for (; qcpItor != m_pQcpVec.end(); ++qcpItor)
	{
		if (*qcpItor)
		{
			(*qcpItor)->play(dRate);
		}
	}


	return bRet;
}

bool CChartView::stop()
{
	bool bRet = true;

	QcpItor qcpItor = m_pQcpVec.begin();
	for (; qcpItor != m_pQcpVec.end(); ++qcpItor)
	{
		if (*qcpItor)
		{
			(*qcpItor)->stop();
		}
	}

	return bRet;
}

bool CChartView::seek(double dRate)
{
	bool bRet = true;

	QcpItor qcpItor = m_pQcpVec.begin();
	for (; qcpItor != m_pQcpVec.end(); ++qcpItor)
	{
		if (*qcpItor)
		{
			(*qcpItor)->seek(dRate);
		}
	}

	return bRet;
}

void CChartView::SyncCrossLine(QPoint point)
{
	QPoint pt;
	QcpItor qcpItor = m_pQcpVec.begin();
	//get mouse pos
	for (; qcpItor != m_pQcpVec.end(); ++qcpItor)
	{
		if (*qcpItor)
		{
			bool bFocus = (*qcpItor)->getMouseFocus();
			if (bFocus)
			{
				pt = (*qcpItor)->getMousePos();

			}
		}
	}

	//draw cross
	qcpItor = m_pQcpVec.begin();
	for (; qcpItor != m_pQcpVec.end(); ++qcpItor)
	{
		if (*qcpItor)
		{
			QTime time;
			time.start();
			(*qcpItor)->showTrackerItem(pt);
		}
	}

}

void CChartView::SyncEraserCrossLine()
{
	//eraser cross
	QcpItor qcpItor = m_pQcpVec.begin();
	qcpItor = m_pQcpVec.begin();
	for (; qcpItor != m_pQcpVec.end(); ++qcpItor)
	{
		if (*qcpItor)
		{
			(*qcpItor)->eraserTracker();
		}
	}
}

void CChartView::SynZoomSlot(QWheelEvent* event)
{

#if 0		//log

	QObject* sender = QObject::sender();
	QString strClass = sender->metaObject()->className();
	QString objName = sender->objectName();
	QCustomPlotEx* obj = qobject_cast<QCustomPlotEx*>(sender);

	qDebug() << "2222222222222222";
	qDebug() << QDateTime::currentDateTime();
	qDebug() << "sender = " << strClass;
	qDebug() << "strClass = " << strClass;
	qDebug() << "objName = " << objName;
	qDebug() << "obj = " << obj;

#endif // 0

	std::vector<QCPRange> beforeRange,afterRange,lastRange;
	QcpItor qcpItor = m_pQcpVec.begin();
	qcpItor = m_pQcpVec.begin();
	for (; qcpItor != m_pQcpVec.end(); ++qcpItor)
	{
		if (*qcpItor)
		{	
			QCPRange range;
			(*qcpItor)->getCurHorAxisRange(range);
			beforeRange.push_back(range);
			
			(*qcpItor)->chartZoom(event);
			
			(*qcpItor)->getCurHorAxisRange(range);
			afterRange.push_back(range);
		}
	}

#if 0	//log

	static int nCount = 0;
	nCount++;
	if (nCount % 2 == 1)
	{
		qDebug() << QDateTime::currentDateTime();
		qDebug() << "SynZoomSlot first time " << endl;
	}
	else if (nCount % 2 == 0)
	{
		nCount = 0;
		qDebug() << QDateTime::currentDateTime();
		qDebug() << "SynZoomSlot second time " << endl;
	}

#endif // 0

#if 0

	UpdateCurveDataSlot(afterRange[0]);

#endif // 0

}

void CChartView::SynTransSlot(QMouseEvent* event)
{
	QcpItor qcpItor = m_pQcpVec.begin();
	qcpItor = m_pQcpVec.begin();
	for (; qcpItor != m_pQcpVec.end(); ++qcpItor)
	{
		if (*qcpItor)
		{
			(*qcpItor)->chartTrans(event);
		}
	}
}

void CChartView::SynPressSlot(QMouseEvent* event)
{
	QcpItor qcpItor = m_pQcpVec.begin();
	qcpItor = m_pQcpVec.begin();
	for (; qcpItor != m_pQcpVec.end(); ++qcpItor)
	{
		if (*qcpItor)
		{
			(*qcpItor)->chartPress(event);
		}
	}
}

void CChartView::SynRelaeseSlot(QMouseEvent* event)
{
	QcpItor qcpItor = m_pQcpVec.begin();
	qcpItor = m_pQcpVec.begin();
	for (; qcpItor != m_pQcpVec.end(); ++qcpItor)
	{
		if (*qcpItor)
		{
			(*qcpItor)->chartRelease(event);
		}
	}
}

void CChartView::SelectChart(QCustomPlotEx* pCustomPlotEx)
{
	m_pChartSelect = pCustomPlotEx;
}

void CChartView::mouseMoveEvent(QMouseEvent* event)
{
	QWidget::mouseMoveEvent(event);
}

void CChartView::openCross()
{
	static bool bOpen = true;
	bOpen = !bOpen;

	QcpItor qcpItor = m_pQcpVec.begin();
	qcpItor = m_pQcpVec.begin();
	for (; qcpItor != m_pQcpVec.end(); ++qcpItor)
	{
		if (*qcpItor)
		{
			(*qcpItor)->showTracer(bOpen);
		}
	}
}

void CChartView::fullScreen()
{
	if (m_bFullScreen)
	{
		//full-->default
		m_bFullScreen = false;
	}
	else
	{
		//default->full
		m_bFullScreen = true;
	}

	Layout();
}

void CChartView::rotate(const CCRoateData& data)
{
	if (m_pChartSelect)
	{
		m_pChartSelect->rotate(data);
	}
}

void CChartView::trans(const CCTransData& data)
{
	if (m_pChartSelect)
	{
		m_pChartSelect->trans(data);
	}
}

void CChartView::MoveUp()
{
	if (!m_pChartSelect)
		return;

	int nChartIndex = 0;
    int nChartNum = (int)m_pQcpVec.size();
	for (int i = 0; i < nChartNum; ++i)
	{
		if (m_pChartSelect == m_pQcpVec[i])
		{
			nChartIndex = i;
			break;
		}
	}

	//change vec index
	if (nChartIndex > 0)
	{
		std::swap(m_pQcpVec[nChartIndex], m_pQcpVec[nChartIndex - 1]);
	}

	Layout();
}

void CChartView::MoveDown()
{
	if (!m_pChartSelect)
		return;

	int nChartIndex = 0;
	int nChartNum = m_pQcpVec.size();
	for (int i = 0; i < nChartNum; ++i)
	{
		if (m_pChartSelect == m_pQcpVec[i])
		{
			nChartIndex = i;
			break;
		}
	}

	//change vec index
	if ((nChartIndex >= 0)  && (nChartIndex < (nChartNum - 1)))
	{
		std::swap(m_pQcpVec[nChartIndex], m_pQcpVec[nChartIndex + 1]);
	}

	Layout();

}

void CChartView::backToDefault()
{

#if 0

	QcpItor qcpItor = m_pQcpVec.begin();
	qcpItor = m_pQcpVec.begin();
	for (; qcpItor != m_pQcpVec.end(); ++qcpItor)
	{
		if (*qcpItor)
		{
			(*qcpItor)->backToDefault();
		}
	}

#endif // 0

	//use default data to draw chart
	SetChartData(m_DefaultFlightList);
	loadSampleData(m_DefaultFlightList);
}

bool CChartView::setChartProjectTime(int iStartSec, int iEndSec)
{
	bool bRet = true;

	m_iStartSec = iStartSec;
	m_iEndSec = iEndSec;
	double dValue = 1000.0 / 25.0;	//25P->>40ms
	m_dChartPlayStep = 1.0 / ((double)(m_iEndSec - m_iStartSec) * dValue);

	return bRet;
}

bool CChartView::setChartPlayStep()
{
	bool bRet = true;

	QcpItor qcpItor = m_pQcpVec.begin();
	for (; qcpItor != m_pQcpVec.end(); ++qcpItor)
	{
		if (*qcpItor)
		{
			(*qcpItor)->setPlaySetp(m_dChartPlayStep);
		}
	}

	return bRet;
}

void CChartView::UpdateCurveDataSlot(const QCPRange& range)
{

#if 0	//log

	QObject* sender = QObject::sender();
	QString strClass = sender->metaObject()->className();
	QString objName = sender->objectName();
	CChartView* obj = qobject_cast<CChartView*>(sender);

	qDebug() << "strClass = " << strClass;
	qDebug() << "objName = " << objName;

	qDebug() << "333333333333333333";
	static int nCount = 0;
	nCount++;
	if (nCount % 2 == 1)
	{
		qDebug() << "query data first time " << endl;
	}
	else if (nCount % 2 == 0)
	{
		nCount = 0;
		qDebug() << "query data second time " << endl;
	}

#endif // 0

#if 0

	bool bRet = false;
	FlightItemDataVector flightDataList;
	if (m_pDataInterface)
	{
		qint64 startTime = (qint64)(range.lower);
		qint64 endTime	 = (qint64)(range.upper);
		QDateTime qStartTime = QDateTime::fromSecsSinceEpoch(startTime);
		QDateTime qEndTime	 = QDateTime::fromSecsSinceEpoch(endTime);

		CHProjectData projectData;
		projectData.startTime	= qStartTime.toString("yyyy-MM-dd hh:mm:ss");
		projectData.endTime		= qEndTime.toString("yyyy-MM-dd hh:mm:ss");

		/*
			current curve name is source param name, when change 
			the curve real name,the below query will fail! 
		*/
		QString strFields;
		QString strSpilt = ",";
		auto itor = m_ChartProVec.begin();
		for (; itor != m_ChartProVec.end(); ++itor)
		{
			projectData.fieldsVec.push_back(itor->strTitle);
			QString str = itor->strTitle + strSpilt;
			strFields += str;
		}
		if (!strFields.isEmpty())
		{
			// delete last ","
			strFields = strFields.left(strFields.length() - 1);
		}
		projectData.fields = strFields;

		bRet = m_pDataInterface->GetHttpFlightDataListEx(projectData, flightDataList);
		if (!bRet)
		{
			qDebug() << "get data error";
		}
	}

	if (bRet)
	{
		SetChartData(flightDataList);
		loadSampleData(flightDataList);
	}
	
#endif // 0

}
