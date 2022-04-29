#pragma once

#include <QWidget>
#include <QMenu>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include "CChartOperatePage.h"
#include "CChartView.h"

// 播放状态
enum X_PLAY_STATUS
{
        X_PLAY_STATUS_None = 0,
        X_PLAY_STATUS_Stop,
        X_PLAY_STATUS_Pause,
        X_PLAY_STATUS_Seek,
        X_PLAY_STATUS_Play,
        X_PLAY_STATUS_Play_J,
        X_PLAY_STATUS_Play_K,
        X_PLAY_STATUS_Play_L,
};

class CXChartViewWnd : public QWidget
{
	Q_OBJECT

public:
    CXChartViewWnd(QWidget* pParent = NULL);
    virtual ~CXChartViewWnd();

public:
	void rootMenuClicked();
	void updateWndMenu();

	void updateCurveItem();

	//file
	void			initViewPlugin();
	void			getViewPluginData();
	void			setFileList(FlightItemDataVector& fileList);
	void			initOptionPageData();

	//interface
	CChartView*		getChartView();

	//get project time data
	bool			getProjectTime();
	bool			getProjectTime(int& iStartSec, int& iEndSec);

	//set chart project time data
	bool			setChartProjectTime();

public slots:
    //control
	void			controlHandle(const std::string& strControll);
	void			updateChartHandle();
	void			openCrossBtnHandle();
	void			fullBtnHandle();
	void			rotateBtnHandle();
	void			transBtnHandle();
	void			moveBtnHandle();
	void			setBtnHandle();
	void			moveUpMenuHandle();
	void			moveDownMenuHandle();
	void			paramSetHandle();
	void			backToDefaultHandle();

public:
    bool			play(int64_t lSeekPos = 0, int64_t lRate = 0);
    bool			seek(int64_t lSeekPos, int64_t lRate);
    bool			stop();
	//scale
	bool            Scale();

private:
	QWidget*	m_pWndPreview;
	QString		m_sWndName;
	QString		m_sWndId;
	CChartView*	m_pChartWidget;
	QVBoxLayout* m_pVBLayout;

	//curve view data
	FlightItemDataVector	m_flightList;
    int64_t		m_lCurPos;
    int64_t		m_lInPoint;
    int64_t		m_lOutPoint;
	double		m_sampleRate;

private:
	//curve top controls
	QHBoxLayout* m_pTopLayout;

	//cross
    QPushButton* m_pCrossBtn;

	//full screen
    QPushButton* m_pFullBtn;

	//rotate
    QPushButton* m_pRotateBtn;

	//trans
    QPushButton* m_pTranslationBtn;

	//move
    QPushButton* m_pMoveBtn;

	//set
    QPushButton* m_pSetBtn;

	//default
    QPushButton* m_pSetDefault;

	//curve set center
	CXChartOptionPageEX* m_pChartOptionPage;

private:
	CChartRoatePage* m_pChartRoatePage;
	CChartTransPage* m_pChartTransPage;

protected:
	void	initTopCtrl();
	void	initCtrl();
	void	initCurveCtrl();
	void	initBottomCtrl();
	void    registerMenu();
	void    createToolBar();
	void    initIface();
	void    releaseIface();
	void	initOption();
	void    updateCurTimeCodePos();

	//preview rect
	QRect	previewRect(const QRect& src);
private:

	X_PLAY_STATUS	m_ePlayStatus;
    int64_t			m_iCurPos;
	int				m_iBackwordStatus;
	int				m_iForwordStatus;
	int				m_nPlayTimer;//play time

	int	m_wndIndex;

	CFlightProjectTimeData m_ProjectTimeData;

protected:
    void resizeEvent(QResizeEvent* e);
};

#if 0

//Chart1
class CXChartViewWnd1 : public CXChartViewWnd
{
	Q_OBJECT
public:
	DECLARE_WND_CALL(CXChartViewWnd1)

public:
	explicit CXChartViewWnd1(QWidget* pParent = NULL);
	~CXChartViewWnd1();
};

//Chart2
class CXChartViewWnd2 : public CXChartViewWnd
{
	Q_OBJECT
public:
	DECLARE_WND_CALL(CXChartViewWnd2)

public:
	explicit CXChartViewWnd2(QWidget* pParent = NULL);
	~CXChartViewWnd2();
};

//Chart3
class CXChartViewWnd3 : public CXChartViewWnd
{
	Q_OBJECT
public:
	DECLARE_WND_CALL(CXChartViewWnd3)

public:
	explicit CXChartViewWnd3(QWidget* pParent = NULL);
	~CXChartViewWnd3();
};

//Chart4
class CXChartViewWnd4 : public CXChartViewWnd
{
	Q_OBJECT
public:
	DECLARE_WND_CALL(CXChartViewWnd4)

public:
	explicit CXChartViewWnd4(QWidget* pParent = NULL);
	~CXChartViewWnd4();
};

#endif
