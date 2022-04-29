#pragma once

#include "XFlightData.h"
#include "CChartBaseData.h"
#include <QColor>
#include "QCustomPlotEx.h"
#include <QVBoxLayout>
#include <QTimer>
#include <QComboBox>

class CChartViewProperty
{
public:
	CChartViewProperty()
	{

	}

	CChartViewProperty(const CChartViewProperty& ChartViewProperty)
	{
        strTitle    = ChartViewProperty.strTitle;
        dWidth      = ChartViewProperty.dWidth;
        color       = ChartViewProperty.color;
	}

	CChartViewProperty(QString _strTitle, double _dWidth, QColor _color)
	{
        strTitle    = _strTitle;
        dWidth      = _dWidth;
        color       = _color;
	}

	QString strTitle;	//title
	double  dWidth;		//line width
	QColor  color;		//color
};
typedef std::vector<CChartViewProperty> ChartPropertyVec;
typedef std::vector<CChartViewProperty>::iterator ChartPropertyItor;
typedef std::vector<QCustomPlotEx* > QcpVec;
typedef std::vector<QCustomPlotEx* >::iterator QcpItor;

//chart plugin
class CChartView : public QWidget
{
	Q_OBJECT

public:
    CChartView(QWidget* parent = NULL);
	~CChartView();

signals:
	void UpdateCurveDataSignal(const QCPRange& range);

public slots:
	void SelectChart(QCustomPlotEx* pCustomPlotEx);
	void SyncCrossLine(QPoint point);
	void SyncEraserCrossLine();
	void SynZoomSlot(QWheelEvent* event);
	void SynTransSlot(QMouseEvent* event);
	void SynPressSlot(QMouseEvent* event);
	void SynRelaeseSlot(QMouseEvent* event);
	void UpdateCurveDataSlot(const QCPRange& range);

public:
	void initData();
	void Init();
	void InitCurve(QCustomPlotEx* pCustomPlot, const CChartViewProperty& chartViewProperty);
	bool AddSeries(const CChartViewProperty& chartViewProperty);
	void Layout();
	void LayoutDefault();
	void LayoutFull();

	void openCross();
	void fullScreen();
	void rotate(const CCRoateData& data);
	void trans(const CCTransData& data);
	void MoveUp();
	void MoveDown();
	void backToDefault();

	void UpdateChartView();
	void loadSampleData(const FlightItemDataVector& flightDataList);


public:
	//interface
	QcpVec& GetQcpVec();
	void SetChart(const ChartPropertyVec& chartProVec, const FlightItemDataVector& flightDataList);
	void SetChartProperty(const ChartPropertyVec& chartProVec);
	ChartPropertyVec& GetChartProperty();

	//set curve chart data
	bool SetChartData(const FlightItemDataVector& flightDataList);
	bool SetDefaultChartData(const FlightItemDataVector& flightDataList);

	//control
	bool play(double dRate);
	bool stop();
	bool seek(double dRate);

	bool setChartProjectTime(int iStartSec, int iEndSec);
	bool setChartPlayStep();

protected:
	void resizeEvent(QResizeEvent* e);
	void mouseMoveEvent(QMouseEvent* event);

private:
	//data
	QcpVec m_pQcpVec;
	int m_QcpIndex;
	ChartPropertyVec m_ChartProVec;
	QCustomPlotEx* m_pChartSelect;
	bool m_bFullScreen;

	QTimer m_Timer;
	int m_IndexData;

	//curve data
	FlightItemDataVector m_flightList;
	FlightItemDataVector m_DefaultFlightList;

	//project time
	int m_iStartSec;
	int m_iEndSec;
	double m_dChartPlayStep;

};
