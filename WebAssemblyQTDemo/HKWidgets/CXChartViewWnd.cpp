#include "CXChartViewWnd.h"
#include <QMenu>
#include <QAction>

#define RATE		1000		//translate rate
#define ONESEC		1000		//1s=1000ms
#define FRAME_RATE	25
#define CTRL_WIDTH	30
#define CTRL_HEIGHT 30

//common
const short CTL_SPACE               = 2;    // 控件间间距
const short CTL_SPACE_1             = 1;    // 间距1
const short CTL_SPACE_2             = 2;    // 间距2
const short CTL_SPACE_4             = 4;    // 间距4
const short CTL_SPACE_6             = 6;    // 间距6
const short CTL_SPACE_8             = 8;    // 间距8
const short CTL_SPACE_10            = 10;   // 间距10
const short CTL_SPACE_12            = 12;   // 间距12
const short CTL_SPACE_16            = 16;   // 间距16
const short CTL_SPACE_20            = 20;   // 间距20


#ifndef SAFE_DELETE
#define SAFE_DELETE(p)          { if(p) { delete (p);     (p)=nullptr; } }
#endif

CXChartViewWnd::CXChartViewWnd(QWidget* pParent)
	: QWidget(pParent),
	m_wndIndex(0)
{
	m_iCurPos = 0;
	m_ePlayStatus = X_PLAY_STATUS_Stop;
	m_iBackwordStatus = 2;
	m_iForwordStatus = 2;
	m_nPlayTimer = 0;

	initIface();
	initCtrl();
	initTopCtrl();

	initOption();
	initOptionPageData();

	initBottomCtrl();
	setFocusPolicy(Qt::ClickFocus);
	setAcceptDrops(true);
}

CXChartViewWnd::~CXChartViewWnd()
{
	releaseIface();
	//SAFE_DELETE(m_pWndPreview);
	SAFE_DELETE(m_pChartWidget);
}

void CXChartViewWnd::initIface()
{
	
}

void CXChartViewWnd::releaseIface()
{

}

void CXChartViewWnd::registerMenu()
{
	
}

void CXChartViewWnd::initTopCtrl()
{
    m_pCrossBtn = new QPushButton(this);
//	m_pCrossBtn->setBackColor(X_GetSysColor("BaseFrame"));
    QString strIcon = ":/skins/flight/chart/cross.png";
    QIcon icon;
    icon.addFile(strIcon);
    m_pCrossBtn->setIcon(icon);
    QSize size(m_pCrossBtn->width(),m_pCrossBtn->height());
    m_pCrossBtn->setIconSize(size);
//	m_pCrossBtn->setBitmaps(strIcon, true);
	m_pCrossBtn->setToolTip(QStringLiteral("cross"));

    m_pFullBtn = new QPushButton(this);
//	m_pFullBtn->setBackColor(X_GetSysColor("BaseFrame"));
    strIcon = ":/skins/flight/chart/fullScreen";
    icon.addFile(strIcon);
    m_pFullBtn->setIcon(icon);
    m_pFullBtn->setIconSize(size);
//	m_pFullBtn->setBitmaps(strIcon, true);
	m_pFullBtn->setToolTip(QStringLiteral("fullScreen"));

    m_pRotateBtn = new QPushButton(this);
//	m_pRotateBtn->setBackColor(X_GetSysColor("BaseFrame"));
    strIcon = ":/skins/flight/chart/rotate";
    icon.addFile(strIcon);
    m_pRotateBtn->setIcon(icon);
    m_pRotateBtn->setIconSize(size);
//	m_pRotateBtn->setBitmaps(strIcon, true);
	m_pRotateBtn->setToolTip(QStringLiteral("rotate"));

    m_pTranslationBtn = new QPushButton(this);
//	m_pTranslationBtn->setBackColor(X_GetSysColor("BaseFrame"));
    strIcon = ":/skins/flight/chart/trans";
    icon.addFile(strIcon);
    m_pTranslationBtn->setIcon(icon);
    m_pTranslationBtn->setIconSize(size);
//	m_pTranslationBtn->setBitmaps(strIcon, true);
	m_pTranslationBtn->setToolTip(QStringLiteral("trans"));

    m_pMoveBtn = new QPushButton(this);
//	m_pMoveBtn->setBackColor(X_GetSysColor("BaseFrame"));
    strIcon = ":/skins/flight/chart/move";
    icon.addFile(strIcon);
    m_pMoveBtn->setIcon(icon);
    m_pMoveBtn->setIconSize(size);
//	m_pMoveBtn->setBitmaps(strIcon, true);
	m_pMoveBtn->setToolTip(QStringLiteral("move"));

    m_pSetBtn = new QPushButton(this);
//	m_pSetBtn->setBackColor(X_GetSysColor("BaseFrame"));
    strIcon = ":/skins/flight/chart/set";
    icon.addFile(strIcon);
    m_pSetBtn->setIcon(icon);
    m_pSetBtn->setIconSize(size);
//	m_pSetBtn->setBitmaps(strIcon, true);
	m_pSetBtn->setToolTip(QStringLiteral("set"));

    m_pSetDefault = new QPushButton(this);
//	m_pSetDefault->setBackColor(X_GetSysColor("BaseFrame"));
    strIcon = ":/skins/flight/chart/default";
    icon.addFile(strIcon);
    m_pSetDefault->setIcon(icon);
    m_pSetDefault->setIconSize(size);
//	m_pSetDefault->setBitmaps(strIcon, true);
	m_pSetDefault->setToolTip(QStringLiteral("default"));

    connect(m_pCrossBtn, &QPushButton::clicked, this, &CXChartViewWnd::openCrossBtnHandle);
    connect(m_pFullBtn, &QPushButton::clicked, this, &CXChartViewWnd::fullBtnHandle);

    connect(m_pRotateBtn, &QPushButton::clicked, this, &CXChartViewWnd::rotateBtnHandle);
    connect(m_pTranslationBtn, &QPushButton::clicked, this, &CXChartViewWnd::transBtnHandle);
    connect(m_pMoveBtn, &QPushButton::clicked, this, &CXChartViewWnd::moveBtnHandle);
    connect(m_pSetBtn, &QPushButton::clicked, this, &CXChartViewWnd::setBtnHandle);
    connect(m_pSetDefault, &QPushButton::clicked, this, &CXChartViewWnd::backToDefaultHandle);

	
	m_pChartRoatePage = new CChartRoatePage(this);
	m_pChartRoatePage->setChartWidget(m_pChartWidget);
	m_pChartTransPage = new CChartTransPage(this);
	m_pChartTransPage->setChartWidget(m_pChartWidget);
	m_pChartOptionPage = new CXChartOptionPageEX();
	m_pChartOptionPage->setWindowModality(Qt::ApplicationModal);
	m_pChartOptionPage->setChartWidget(m_pChartWidget);
	m_pChartOptionPage->setTotalFileList(m_flightList);
}

void CXChartViewWnd::initCtrl()
{
    m_pChartWidget = new CChartView(this);
	m_pChartWidget->show();
	setChartProjectTime();
	m_pVBLayout = new QVBoxLayout(m_pChartWidget);

}

void CXChartViewWnd::initCurveCtrl()
{
	CChartViewProperty chartProHeight("height", 2, QColor(Qt::darkYellow));
	CChartViewProperty chartProSpeed("speed", 2, QColor(Qt::darkMagenta));
	CChartViewProperty chartProLongitude("longitude", 2, QColor(Qt::darkCyan));
	ChartPropertyVec chartProVec;
	chartProVec.push_back(chartProHeight);
	chartProVec.push_back(chartProSpeed);
	chartProVec.push_back(chartProLongitude);
	//m_pChartWidget->SetChart(chartProVec, m_flightList);
}

void CXChartViewWnd::initBottomCtrl()
{
	
}

void CXChartViewWnd::initViewPlugin()
{

}

void CXChartViewWnd::getViewPluginData()
{

}


void CXChartViewWnd::setFileList(FlightItemDataVector& fileList)
{
	m_flightList = fileList;
    if (m_pChartOptionPage)
    {
        m_pChartOptionPage->setTotalFileList(fileList);
    }
}

void CXChartViewWnd::initOptionPageData()
{
	if (m_pChartOptionPage)
	{
		m_pChartOptionPage->setFileList(m_flightList);
		//m_pChartOptionPage->setChartWidget(m_pChartWidget);
	}
}

bool CXChartViewWnd::play(int64_t lSeekPos, int64_t lRate)
{
	m_lCurPos = lSeekPos;

	int iStartSec = 0;
	int iEndSec = 0;
	getProjectTime(iStartSec, iEndSec);
	m_lCurPos = lSeekPos + iStartSec * FRAME_RATE;
	m_iCurPos = m_lCurPos;

	if (m_pChartWidget)
	{
		double dRate = (double)lRate / (double)RATE;
		m_pChartWidget->play(dRate);
	}

	return true;
}

bool CXChartViewWnd::seek(int64_t lSeekPos, int64_t lRate)
{
	m_lCurPos = lSeekPos;

	if (m_pChartWidget)
	{
		double dRate = (double)lRate / (double)RATE;
		m_pChartWidget->seek(dRate);
	}

	int iStartSec = 0;
	int iEndSec = 0;
	getProjectTime(iStartSec, iEndSec);
	m_lCurPos = lSeekPos + iStartSec * FRAME_RATE;

	updateCurTimeCodePos();
	m_ePlayStatus = X_PLAY_STATUS_Stop;

	return true;
}

bool CXChartViewWnd::stop()
{
	if (m_pChartWidget)
	{
		m_pChartWidget->stop();
	}

	return true;
}

void CXChartViewWnd::controlHandle(const std::string& strControll)
{
	QString sCmd = strControll.c_str();
	if (sCmd.contains("play"))
	{
		int nPos = sCmd.indexOf("+");
		QString strLeft = sCmd.left(nPos);
		QString seekPos = strLeft.right(strLeft.length() - 4);

		QString strRight = sCmd.right(sCmd.length() - (nPos + 1));
		QString ratePos = strRight.right(strRight.length() - 4);

		play(seekPos.toInt(), ratePos.toInt());

	}
	else if (0 == strControll.compare("stop"))
	{
		stop();
	}
	else if (sCmd.contains("seek"))
	{
		int nPos = sCmd.indexOf("+");
		QString strLeft = sCmd.left(nPos);
		QString seekPos = strLeft.right(strLeft.length() - 4);

		QString strRight = sCmd.right(sCmd.length() - (nPos + 1));
		QString ratePos = strRight.right(strRight.length() - 4);

		seek(seekPos.toInt(), ratePos.toInt());

	}
}

void CXChartViewWnd::updateChartHandle()
{
	getViewPluginData();

	if (m_pChartOptionPage)
		m_pChartOptionPage->setTotalFileList(m_flightList);

}

void CXChartViewWnd::openCrossBtnHandle()
{
	if (m_pChartWidget)
	{
		m_pChartWidget->openCross();
	}
}

void CXChartViewWnd::fullBtnHandle()
{
	if (m_pChartWidget)
	{
		m_pChartWidget->fullScreen();
	}
}

void CXChartViewWnd::rotateBtnHandle()
{
	if (m_pChartRoatePage)
	{
		int nTaskOpenWndWidth = m_pChartRoatePage->width();
		int nTaskOpenWndHeight = m_pChartRoatePage->height();
		m_pChartRoatePage->move(720, 420);
		m_pChartRoatePage->show();
	}
}

void CXChartViewWnd::transBtnHandle()
{
	if (m_pChartTransPage)
	{
		int nTaskOpenWndWidth = m_pChartTransPage->width();
		int nTaskOpenWndHeight = m_pChartTransPage->height();
		m_pChartTransPage->move(720, 420);
		m_pChartTransPage->show();
	}
}

void CXChartViewWnd::moveBtnHandle()
{
    QMenu* pMenu = new QMenu();
	m_pMoveBtn->setMenu(pMenu);
    QAction* pQAMoveTop = new QAction(QStringLiteral("MoveUp"));
    QAction* pQAMoveBottom = new QAction(QStringLiteral("MoveDown"));
	pMenu->addAction(pQAMoveTop);
	pMenu->addAction(pQAMoveBottom);

	connect(pQAMoveTop, &QAction::triggered, this, &CXChartViewWnd::moveUpMenuHandle);
	connect(pQAMoveBottom, &QAction::triggered, this, &CXChartViewWnd::moveDownMenuHandle);

}

void CXChartViewWnd::setBtnHandle()
{

    QMenu* pMenu = new QMenu();
	m_pSetBtn->setMenu(pMenu);
    QAction* pQAParamSet = new QAction(QStringLiteral("param set"));
	pMenu->addAction(pQAParamSet);

	connect(pQAParamSet, &QAction::triggered, this, &CXChartViewWnd::paramSetHandle);

}

void CXChartViewWnd::moveUpMenuHandle()
{
	if (m_pChartWidget)
	{
		m_pChartWidget->MoveUp();
	}
}

void CXChartViewWnd::moveDownMenuHandle()
{
	if (m_pChartWidget)
	{
		m_pChartWidget->MoveDown();
	}
}

void CXChartViewWnd::paramSetHandle()
{
	if (m_pChartOptionPage)
	{
		QRect rect(0, 0, 550, 520);
		m_pChartOptionPage->move(500, 240);
		auto pos = m_pChartOptionPage->pos();
		auto geo = m_pChartOptionPage->geometry();
		m_pChartOptionPage->show();
	}

}

void CXChartViewWnd::backToDefaultHandle()
{
	if (m_pChartWidget)
		m_pChartWidget->backToDefault();
}

void CXChartViewWnd::updateWndMenu()
{

}

void CXChartViewWnd::rootMenuClicked()
{

}

void CXChartViewWnd::createToolBar()
{
	
}

void CXChartViewWnd::resizeEvent(QResizeEvent *event)
{
	QRect rtClient = rect();
	rtClient.setBottom(qMax(rtClient.top(), rtClient.bottom() - 4));

	//set curve rect
	QRect rtPreivew;
	rtPreivew.setTop(rtClient.top() + CTL_SPACE_8 + CTRL_HEIGHT);
	rtPreivew.setBottom(rtClient.bottom() - CTL_SPACE_10);
	rtPreivew.setLeft(CTL_SPACE_4);
	rtPreivew.setRight(rtClient.right() - CTL_SPACE_4);
	rtPreivew = previewRect(rtPreivew);
	m_pChartWidget->setGeometry(rtPreivew);

	//set top control rect
	//cross button
	int nBtnWidth = CTRL_WIDTH;
	int nBtnHeight = CTRL_HEIGHT;
	QSize szBtn(nBtnWidth, nBtnHeight);
	QRect rtCrossBtn;
	rtCrossBtn.setTop(rtPreivew.top() - CTL_SPACE_1 - nBtnHeight);
	rtCrossBtn.setLeft(rtPreivew.left());
	rtCrossBtn.setWidth(nBtnWidth);
	rtCrossBtn.setHeight(nBtnHeight);
	m_pCrossBtn->setGeometry(rtCrossBtn);

	//full screen button
	QRect rtKeyBtn;
	rtKeyBtn.setTop(rtCrossBtn.top());
	rtKeyBtn.setLeft(rtCrossBtn.right() + CTL_SPACE_1);
	rtKeyBtn.setWidth(nBtnWidth);
	rtKeyBtn.setHeight(nBtnHeight);
	m_pFullBtn->setGeometry(rtKeyBtn);

#if 0		//current do not use rotate 

	//rotate button
	QRect rtRotateBtn;
	rtRotateBtn.setTop(rtKeyBtn.top());
	rtRotateBtn.setLeft(rtKeyBtn.right() + CTL_SPACE_1);
	rtRotateBtn.setWidth(nBtnWidth);
	rtRotateBtn.setHeight(nBtnHeight);
	m_pRotateBtn->setGeometry(rtRotateBtn);

#else

	QRect rtTemp(0, 0, 0, 0);
	m_pRotateBtn->setGeometry(rtTemp);
	QRect rtRotateBtn(rtKeyBtn);


#endif // 0

	//trans button
	QRect rtTranslationBtn;
	rtTranslationBtn.setTop(rtRotateBtn.top());
	rtTranslationBtn.setLeft(rtRotateBtn.right() + CTL_SPACE_1);
	rtTranslationBtn.setWidth(nBtnWidth);
	rtTranslationBtn.setHeight(nBtnHeight);
	m_pTranslationBtn->setGeometry(rtTranslationBtn);

	//move button
	QRect rtMoveBtn;
	rtMoveBtn.setTop(rtTranslationBtn.top());
	rtMoveBtn.setLeft(rtTranslationBtn.right() + CTL_SPACE_1);
	rtMoveBtn.setWidth(nBtnWidth);
	rtMoveBtn.setHeight(nBtnHeight);
	m_pMoveBtn->setGeometry(rtMoveBtn);

	//set button
	QRect rtSetBtn;
	rtSetBtn.setTop(rtMoveBtn.top());
	rtSetBtn.setLeft(rtMoveBtn.right() + CTL_SPACE_1);
	rtSetBtn.setWidth(nBtnWidth);
	rtSetBtn.setHeight(nBtnHeight);
	m_pSetBtn->setGeometry(rtSetBtn);

	//default buttons
	QRect rtSetDefaultBtn;
	rtSetDefaultBtn.setTop(rtSetBtn.top());
	rtSetDefaultBtn.setLeft(rtSetBtn.right() + CTL_SPACE_1);
	rtSetDefaultBtn.setWidth(nBtnWidth);
	rtSetDefaultBtn.setHeight(nBtnHeight);
	m_pSetDefault->setGeometry(rtSetDefaultBtn);

	//time code
	QRect rtTimeCode;
	rtTimeCode.setTop(rtSetBtn.top());
	rtTimeCode.setLeft(rtPreivew.right() - CTL_SPACE_2 - (CTRL_WIDTH * 5));
	rtTimeCode.setWidth(CTRL_WIDTH * 5 - CTL_SPACE_2);
	rtTimeCode.setHeight(CTRL_HEIGHT);

}

QRect CXChartViewWnd::previewRect(const QRect& src)
{
    const double dbWRate = 16.00;
    const double dbHRate = 12.00;//9

    double n = (double)src.width() / dbWRate;
	n = qMin(n, (double)src.height() / dbHRate);
    uint32_t uWidth = n * dbWRate;
    uint32_t uHeight = n * dbHRate;

    uint32_t x = src.left() + (src.width() - uWidth) / 2;
    uint32_t y = src.top() + (src.height() - uHeight) / 2;
	return QRect(x, y, uWidth, uHeight);
}

void CXChartViewWnd::initOption()
{

}

void CXChartViewWnd::updateCurveItem()
{
	
}

CChartView* CXChartViewWnd::getChartView()
{
	if (m_pChartWidget)
	{
		return m_pChartWidget;
	}

	return NULL;
}

bool CXChartViewWnd::getProjectTime()
{
	bool bRet = true;

	return bRet;
}

bool CXChartViewWnd::getProjectTime(int& iStartSec, int& iEndSec)
{
	bool bRet = true;

	QDateTime qStartDateTime = QDateTime::fromString(m_ProjectTimeData.Min_time, "yyyy-MM-dd hh:mm:ss");
	QDateTime qEndDateTime = QDateTime::fromString(m_ProjectTimeData.Max_time, "yyyy-MM-dd hh:mm:ss");
	QTime qStartTime = qStartDateTime.time();
	QTime qEndTime = qEndDateTime.time();

	iStartSec = (qStartTime.hour() * 60 + qStartTime.minute()) * 60 + qStartTime.second();
	iEndSec = (qEndTime.hour() * 60 + qEndTime.minute()) * 60 + qEndTime.second();

	return bRet;
}

bool CXChartViewWnd::setChartProjectTime()
{
	bool bRet = true;

	QDateTime qStartDateTime = QDateTime::fromString(m_ProjectTimeData.Min_time, "yyyy-MM-dd hh:mm:ss");
	QDateTime qEndDateTime = QDateTime::fromString(m_ProjectTimeData.Max_time, "yyyy-MM-dd hh:mm:ss");
	QTime qStartTime = qStartDateTime.time();
	QTime qEndTime = qEndDateTime.time();

	int iStartSec = (qStartTime.hour() * 60 + qStartTime.minute()) * 60 + qStartTime.second();
	int iEndSec = (qEndTime.hour() * 60 + qEndTime.minute()) * 60 + qEndTime.second();

	if (m_pChartWidget)
		m_pChartWidget->setChartProjectTime(iStartSec, iEndSec);

	return bRet;
}

void CXChartViewWnd::updateCurTimeCodePos()
{

}

#if 0

//sub chart widget
//MV1
IMPLEMENT_LAYOUTTAB_CALL(CXChartViewWnd1, nullptr, nullptr, nullptr, nullptr)
IMPLEMENT_LAYOUT_ACTIVECALL(CXChartViewWnd1, nullptr)
IMPLEMENT_LAYOUT_GETMENU_CALL(CXChartViewWnd1, nullptr)
IMPLEMENT_WND_CALL(CXChartViewWnd1)
CXChartViewWnd1::CXChartViewWnd1(QWidget* pParent)
	: CXChartViewWnd(sm_pUnkHost, sm_pThisLayout, pParent)
{
}

CXChartViewWnd1::~CXChartViewWnd1()
{
}




//MV2
IMPLEMENT_LAYOUTTAB_CALL(CXChartViewWnd2, nullptr, nullptr, nullptr, nullptr)
IMPLEMENT_LAYOUT_ACTIVECALL(CXChartViewWnd2, nullptr)
IMPLEMENT_LAYOUT_GETMENU_CALL(CXChartViewWnd2, nullptr)
IMPLEMENT_WND_CALL(CXChartViewWnd2)
CXChartViewWnd2::CXChartViewWnd2(QWidget* pParent)
	: CXChartViewWnd(sm_pUnkHost, sm_pThisLayout, pParent)
{
}

CXChartViewWnd2::~CXChartViewWnd2()
{
}

//MV3
IMPLEMENT_LAYOUTTAB_CALL(CXChartViewWnd3, nullptr, nullptr, nullptr, nullptr)
IMPLEMENT_LAYOUT_ACTIVECALL(CXChartViewWnd3, nullptr)
IMPLEMENT_LAYOUT_GETMENU_CALL(CXChartViewWnd3, nullptr)
IMPLEMENT_WND_CALL(CXChartViewWnd3)
CXChartViewWnd3::CXChartViewWnd3(QWidget* pParent)
	: CXChartViewWnd(sm_pUnkHost, sm_pThisLayout, pParent)
{
}

CXChartViewWnd3::~CXChartViewWnd3()
{
}

//MV4
IMPLEMENT_LAYOUTTAB_CALL(CXChartViewWnd4, nullptr, nullptr, nullptr, nullptr)
IMPLEMENT_LAYOUT_ACTIVECALL(CXChartViewWnd4, nullptr)
IMPLEMENT_LAYOUT_GETMENU_CALL(CXChartViewWnd4, nullptr)
IMPLEMENT_WND_CALL(CXChartViewWnd4)
CXChartViewWnd4::CXChartViewWnd4(QWidget* pParent)
	: CXChartViewWnd(sm_pUnkHost, sm_pThisLayout, pParent)
{
}

CXChartViewWnd4::~CXChartViewWnd4()
{
}

#endif // 0
