


#include <QEvent>
#include <QComboBox>
#include "CChartOperatePage.h"
#include <QColorDialog>
#include <QScrollarea>
#include <HKColorCtrl.h>


//-----------------------------------------------
#define GET_TYPE_CTRL(ctrlType, ctrlID)     dynamic_cast<ctrlType>(m_mapCtrl.find(ctrlID)->second)

#define COL_ALIGN_CTRL(pCtrl, x, y, nWidth,nHeight)                        \
        {                                                           \
            if ((pCtrl)!= NULL)   \
            {                                                       \
                (pCtrl)->setGeometry(QRect(x,y,nWidth,nHeight));            \
            }                                                       \
        }

#define ADD_OPTION_STR_VAL(name, val)                                   \
{                                                                       \
    pVal = m_pValFact->NewValue(Option_str_type, name);       \
    pVal->SetOptionValue((void*)val);                                   \
    arrOptionVal.push_back(pVal);                                       \
}

#define ADD_OPTION_INT_VAL(name, val)                                            \
        {                                                                       \
        iVal = val;                                                            \
        pVal = m_pValFact->NewValue(Option_int_type, name);           \
        pVal->SetOptionValue(&iVal);                                            \
        arrOptionVal.push_back(pVal);                                           \
        }

#define ADD_OPTION_VAL(name,val,vtype)                                                    \
        {                                                                          \
        pVal = m_pValFact->NewValue(vtype,name);       \
        pVal->SetOptionValue(&val);                                        \
        arrOptionVal.push_back(pVal);                                  \
        }

#define TOTAL_CURVE_NUM 8

//default curve control number
#define DEFAULT_CURVE_NUM 1 //4

//default curve control number
#define DEFAULT_PARAM_NUM 3

int g_iTotalParamNumEX = 8;
std::vector<QString> g_sParamLabelEX;
std::vector<QString> g_sParamNameEX;
//-----------------------------------------------

#define CONFIWND_WIDTH 550
#define CONFIWND_HEIGHT 540
#define WND_WIDTH 320
#define WND_HEIGHT 300
#define CTRL_WIDTH 20
#define CTRL_WIDTHW 25
#define CTRL_HEIGHT 25

const short CTL_SPACE    = 2;    // 控件间间距
const short CTL_SPACE_1  = 1;    // 间距1
const short CTL_SPACE_2  = 2;    // 间距2
const short CTL_SPACE_4  = 4;    // 间距4
const short CTL_SPACE_6  = 6;    // 间距6
const short CTL_SPACE_8  = 8;    // 间距8
const short CTL_SPACE_10 = 10;   // 间距10
const short CTL_SPACE_12 = 12;   // 间距12
const short CTL_SPACE_16 = 16;   // 间距16
const short CTL_SPACE_20 = 20;   // 间距20

CChartRoatePage::CChartRoatePage(QWidget* parent) : QDialog(parent)
{
	initCtrl();
	initData();
	layout();
}

CChartRoatePage::~CChartRoatePage()
{

}


void CChartRoatePage::initCtrl()
{

	setFixedSize(WND_WIDTH, WND_HEIGHT);
    setWindowTitle("curve rotate");

	m_pWidget = new QWidget(this);
    m_pParamChooseLabel = new QLabel(m_pWidget);
    m_pParamChooseLabel->setText(QStringLiteral("param choose"));
	m_pParamChooseLabel->setFixedWidth(CTRL_WIDTH * 3);
	m_pParamChooseLabel->setFixedHeight(CTRL_HEIGHT);

    m_pParamCombo = new QComboBox(m_pWidget);
	m_pParamCombo->setFixedWidth(CTRL_WIDTH * 5);
	m_pParamCombo->setFixedHeight(CTRL_HEIGHT);
    m_pParamCombo->addItem(QStringLiteral("speed"));
    m_pParamCombo->addItem(QStringLiteral("height"));
	connect(m_pParamCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(changeParam(int)));

    m_pRotateChooseLabel = new QLabel(m_pWidget);
	m_pRotateChooseLabel->setText(QStringLiteral("rotate choose"));
	m_pRotateChooseLabel->setFixedWidth(CTRL_WIDTH * 4);
	m_pRotateChooseLabel->setFixedHeight(CTRL_HEIGHT);

    m_pXlabel = new QLabel(m_pWidget);
	m_pXlabel->setText(QStringLiteral("X"));
	m_pXlabel->setFixedWidth(CTRL_WIDTH);
	m_pXlabel->setFixedHeight(CTRL_HEIGHT);

    m_pXEdit = new QLineEdit(m_pWidget);
	m_pXEdit->setFixedWidth(CTRL_WIDTH * 3);
	m_pXEdit->setFixedHeight(CTRL_HEIGHT);

    m_pYlabel = new QLabel(m_pWidget);
	m_pYlabel->setText(QStringLiteral("Y"));
	m_pYlabel->setFixedWidth(CTRL_WIDTH);
	m_pYlabel->setFixedHeight(CTRL_HEIGHT);

    m_pYEdit = new QLineEdit(m_pWidget);
	m_pYEdit->setFixedWidth(CTRL_WIDTH * 3);
	m_pYEdit->setFixedHeight(CTRL_HEIGHT);

    m_pCoordinateSelectBtn = new QPushButton(m_pWidget);
    //m_pCoordinateSelectBtn->setBackColor(X_GetSysColor("BaseFrame"));
	QString strIcon = ":/skins/flight/chart/add";
    //m_pCoordinateSelectBtn->setBitmaps(strIcon, true);
	m_pCoordinateSelectBtn->setFixedWidth(CTRL_WIDTH*1.5);
	m_pCoordinateSelectBtn->setFixedHeight(CTRL_HEIGHT);
	m_pCoordinateSelectBtn->setToolTip(QStringLiteral("Coordinate selection"));
    connect(m_pCoordinateSelectBtn, &QPushButton::clicked, this, &CChartRoatePage::coordinateSelect);

    m_pRotateOrientationLabel = new QLabel(m_pWidget);
	m_pRotateOrientationLabel->setText(QStringLiteral("rotate orientation"));
	m_pRotateOrientationLabel->setFixedWidth(CTRL_WIDTH * 3);
	m_pRotateOrientationLabel->setFixedHeight(CTRL_HEIGHT);

    m_pOrientionCombo = new QComboBox(m_pWidget);
    m_pOrientionCombo->addItem(QStringLiteral("Clockwise"));
    m_pOrientionCombo->addItem(QStringLiteral("anti Clockwise"));
	m_pOrientionCombo->setFixedWidth(CTRL_WIDTH * 5);
	m_pOrientionCombo->setFixedHeight(CTRL_HEIGHT);
	connect(m_pOrientionCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(changeOriention(int)));

    m_pRotateAngleLabel = new QLabel(m_pWidget);
	m_pRotateAngleLabel->setText(QStringLiteral("rotate angle"));
	m_pRotateAngleLabel->setFixedWidth(CTRL_WIDTH * 3);
	m_pRotateAngleLabel->setFixedHeight(CTRL_HEIGHT);

    m_pAngleEdit = new QLineEdit(m_pWidget);
	m_pAngleEdit->setFixedWidth(CTRL_WIDTH * 3);
	m_pAngleEdit->setFixedHeight(CTRL_HEIGHT);

    m_pAngleLabel = new QLabel(m_pWidget);
	m_pAngleLabel->setText(QStringLiteral("angle"));
	m_pAngleLabel->setAlignment(Qt::AlignCenter);
	m_pAngleLabel->setFixedWidth(CTRL_WIDTH);
	m_pAngleLabel->setFixedHeight(CTRL_HEIGHT);

    m_pYesBtn = new QPushButton(this);
	m_pYesBtn->setText(QStringLiteral("yes"));
	m_pYesBtn->setFixedWidth(CTRL_WIDTH * 3);
	m_pYesBtn->setFixedHeight(CTRL_HEIGHT);
    connect(m_pYesBtn, &QPushButton::clicked, this, &CChartRoatePage::acceptBtnHandle);

    m_pNoBtn = new QPushButton(this);
	m_pNoBtn->setText(QStringLiteral("no"));
	m_pNoBtn->setFixedWidth(CTRL_WIDTH * 3);
	m_pNoBtn->setFixedHeight(CTRL_HEIGHT);
    connect(m_pNoBtn, &QPushButton::clicked, this, &CChartRoatePage::cancelBtnHandle);

    m_pApplyBtn = new QPushButton(this);
	m_pApplyBtn->setText(QStringLiteral("apply"));
	m_pApplyBtn->setFixedWidth(CTRL_WIDTH * 3);
	m_pApplyBtn->setFixedHeight(CTRL_HEIGHT);
    connect(m_pApplyBtn, &QPushButton::clicked, this, &CChartRoatePage::applyBtnHandle);

}

void CChartRoatePage::layout()
{
	QRect rtClient = rect();
	QRect rtWidget;
	rtWidget.setTop(rtWidget.top() + CTL_SPACE_20 * 2);
	rtWidget.setBottom(rtClient.bottom() - CTL_SPACE_20);
	rtWidget.setLeft(CTL_SPACE_2);
	rtWidget.setRight(rtClient.right() - CTL_SPACE_2);
	m_pWidget->setGeometry(rtWidget);

	QRect rtWidgetFrame = m_pWidget->rect();

	QPoint ptLeft, ptMid;
	ptLeft.setX(rtWidgetFrame.left() + CTL_SPACE_20);
	ptLeft.setY(rtWidgetFrame.top() + CTL_SPACE_10);

	ptMid.setX(ptLeft.x() + CTL_SPACE_20 * 4);
	ptMid.setY(ptLeft.y());

	// 1
	QPoint ptParamChooseLabel;
	ptParamChooseLabel.setX(ptLeft.x());
	ptParamChooseLabel.setY(ptLeft.y());
	m_pParamChooseLabel->move(ptParamChooseLabel);

	m_pParamCombo->move(ptMid);

	int nOffset = 0;
	// 2
	m_pRotateChooseLabel->move(ptLeft.x(), ptLeft.y() + CTL_SPACE_4 + CTRL_HEIGHT);
	m_pXlabel->move(ptMid.x(), ptMid.y() + CTL_SPACE_4 + CTRL_HEIGHT);
	nOffset = m_pXlabel->width() + CTL_SPACE_1;
	m_pXEdit->move(ptMid.x() + nOffset, ptMid.y() + CTL_SPACE_4 + CTRL_HEIGHT);
	
	nOffset += (m_pXEdit->width() + CTL_SPACE_8);
	m_pYlabel->move(ptMid.x() + nOffset, ptMid.y() + CTL_SPACE_4 + CTRL_HEIGHT);
	nOffset += (m_pYlabel->width() + CTL_SPACE_1);
	m_pYEdit->move(ptMid.x() + nOffset, ptMid.y() + CTL_SPACE_4 + CTRL_HEIGHT);

	nOffset += (m_pYEdit->width() + CTL_SPACE_4);
	m_pCoordinateSelectBtn->move(ptMid.x() + nOffset, ptMid.y() + CTL_SPACE_4 + CTRL_HEIGHT);

	// 3
	m_pRotateOrientationLabel->move(ptLeft.x(), ptLeft.y() + CTL_SPACE_4 * 2 + CTRL_HEIGHT * 2);
	nOffset = 0;
	m_pOrientionCombo->move(ptMid.x(), ptMid.y() + CTL_SPACE_4 * 2 + CTRL_HEIGHT * 2);

	// 4
	m_pRotateAngleLabel->move(ptLeft.x(), ptLeft.y() + CTL_SPACE_4 * 3 + CTRL_HEIGHT * 3);
	m_pAngleEdit->move(ptMid.x(), ptMid.y() + CTL_SPACE_4 * 3 + CTRL_HEIGHT * 3);
	nOffset = 0;
	nOffset += (m_pAngleEdit->width() + CTL_SPACE_1);
	m_pAngleLabel->move(ptMid.x() + nOffset, ptMid.y() + CTL_SPACE_4 * 3 + CTRL_HEIGHT * 3);


	//bottom button
	QPoint ptBottomRight;
	int nOffsetX = 0;
	int nOffsetY = 0;
	nOffsetX += (m_pApplyBtn->width() + CTL_SPACE_4);
	ptBottomRight.setX(rtClient.right() - nOffsetX);
	nOffsetY += (m_pApplyBtn->height() + CTL_SPACE_10);
	ptBottomRight.setY(rtClient.bottom() - nOffsetY);
	m_pApplyBtn->move(ptBottomRight);

	m_pNoBtn->move(m_pApplyBtn->pos().x() - m_pNoBtn->width() - CTL_SPACE_2, ptBottomRight.y());
	m_pYesBtn->move(m_pNoBtn->pos().x() - m_pYesBtn->width() - CTL_SPACE_2, ptBottomRight.y());



}

void CChartRoatePage::changeParam(int index)
{
	static int i = 0;
	i++;
}

void CChartRoatePage::changeOriention(int index)
{
	static int i = 0;
	i++;
}

void CChartRoatePage::coordinateSelect()
{
	static int i = 0;
	i++;
}

void CChartRoatePage::acceptBtnHandle()
{
	getData();
	
	if (m_pChartWidget)
	{
		m_pChartWidget->rotate(m_CCRoateData);
	}

	QDialog::accept();
}

void CChartRoatePage::cancelBtnHandle()
{
	QDialog::reject();
}

void CChartRoatePage::applyBtnHandle()
{
	getData();

	if (m_pChartWidget)
	{
		m_pChartWidget->rotate(m_CCRoateData);
	}
	
}

void CChartRoatePage::initData()
{

}

void CChartRoatePage::setData(const CCRoateData& data)
{

}

CCRoateData CChartRoatePage::getData()
{
	m_CCRoateData.index = m_pParamCombo->currentIndex();
	m_CCRoateData.param = m_pParamCombo->currentText();
	m_CCRoateData.pt.setX(m_pXEdit->text().toInt());
	bool bOrient = !(m_pOrientionCombo->currentText().compare(QStringLiteral("˳ʱ��")));
	m_CCRoateData.orientation = bOrient;
	m_CCRoateData.angle = m_pAngleEdit->text().toInt();

	return m_CCRoateData;
}

void CChartRoatePage::setChartWidget(CChartView* pChartWidget)
{
	m_pChartWidget = pChartWidget;
}

//---------------------------------------------

CChartTransPage::CChartTransPage(QWidget* parent) : QDialog(parent)
{
	initCtrl();
	initData();
	layout();
}

CChartTransPage::~CChartTransPage()
{

}


void CChartTransPage::initCtrl()
{
	setFixedSize(WND_WIDTH, WND_HEIGHT);
    setWindowTitle("curve trans");

	m_pWidget = new QWidget(this);
    m_pParamChooseLabel = new QLabel(m_pWidget);
	m_pParamChooseLabel->setText(QStringLiteral("param choose"));
	m_pParamChooseLabel->setFixedWidth(CTRL_WIDTH * 3);
	m_pParamChooseLabel->setFixedHeight(CTRL_HEIGHT);

    m_pParamCombo = new QComboBox(m_pWidget);
	m_pParamCombo->setFixedWidth(CTRL_WIDTH * 5);
	m_pParamCombo->setFixedHeight(CTRL_HEIGHT);
    m_pParamCombo->addItem(QStringLiteral("speed"));
    m_pParamCombo->addItem(QStringLiteral("height"));
	connect(m_pParamCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(changeParam(int)));

    m_pTransChooseLabel = new QLabel(m_pWidget);
	m_pTransChooseLabel->setText(QStringLiteral("trans choose"));
	m_pTransChooseLabel->setFixedWidth(CTRL_WIDTH * 4);
	m_pTransChooseLabel->setFixedHeight(CTRL_HEIGHT);

    m_pXlabel = new QLabel(m_pWidget);
	m_pXlabel->setText(QStringLiteral("X"));
	m_pXlabel->setFixedWidth(CTRL_WIDTH);
	m_pXlabel->setFixedHeight(CTRL_HEIGHT);

    m_pXEdit = new QLineEdit(m_pWidget);
	m_pXEdit->setFixedWidth(CTRL_WIDTH * 3);
	m_pXEdit->setFixedHeight(CTRL_HEIGHT);

    m_pCoordinateSelectBtn = new QPushButton(m_pWidget);
    //m_pCoordinateSelectBtn->setBackColor(X_GetSysColor("BaseFrame"));
	QString strIcon = ":/skins/flight/chart/add";
    //m_pCoordinateSelectBtn->setBitmaps(strIcon, true);
	m_pCoordinateSelectBtn->setFixedWidth(CTRL_WIDTH * 1.5);
	m_pCoordinateSelectBtn->setFixedHeight(CTRL_HEIGHT);
	m_pCoordinateSelectBtn->setToolTip(QStringLiteral("Coordinate Select"));
    connect(m_pCoordinateSelectBtn, &QPushButton::clicked, this, &CChartTransPage::coordinateSelect);

    m_pTransOrientationLabel = new QLabel(m_pWidget);
	m_pTransOrientationLabel->setText(QStringLiteral("trans orientation"));
	m_pTransOrientationLabel->setFixedWidth(CTRL_WIDTH * 3);
	m_pTransOrientationLabel->setFixedHeight(CTRL_HEIGHT);

    m_pOrientionCombo = new QComboBox(m_pWidget);
    m_pOrientionCombo->addItem(QStringLiteral("positive"));
    m_pOrientionCombo->addItem(QStringLiteral("negative"));
	m_pOrientionCombo->setFixedWidth(CTRL_WIDTH * 5);
	m_pOrientionCombo->setFixedHeight(CTRL_HEIGHT);
	connect(m_pOrientionCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(changeOriention(int)));

    m_pTimeRangeLabel = new QLabel(m_pWidget);
	m_pTimeRangeLabel->setText(QStringLiteral("ʱtime range"));
	m_pTimeRangeLabel->setFixedWidth(CTRL_WIDTH * 3);
	m_pTimeRangeLabel->setFixedHeight(CTRL_HEIGHT);

    m_pHourEdit = new QLineEdit(m_pWidget);
	m_pHourEdit->setFixedWidth(CTRL_WIDTHW);
	m_pHourEdit->setFixedHeight(CTRL_HEIGHT);

    m_pHourLabel = new QLabel(m_pWidget);
	m_pHourLabel->setText(QStringLiteral("h"));
	m_pHourLabel->setAlignment(Qt::AlignCenter);
	m_pHourLabel->setFixedWidth(CTRL_WIDTH);
	m_pHourLabel->setFixedHeight(CTRL_HEIGHT);

    m_pMinEdit = new QLineEdit(m_pWidget);
	m_pMinEdit->setFixedWidth(CTRL_WIDTHW);
	m_pMinEdit->setFixedHeight(CTRL_HEIGHT);

    m_pMinLabel = new QLabel(m_pWidget);
	m_pMinLabel->setText(QStringLiteral("min"));
	m_pMinLabel->setAlignment(Qt::AlignCenter);
	m_pMinLabel->setFixedWidth(CTRL_WIDTH);
	m_pMinLabel->setFixedHeight(CTRL_HEIGHT);

    m_pSecEdit = new QLineEdit(m_pWidget);
	m_pSecEdit->setFixedWidth(CTRL_WIDTHW);
	m_pSecEdit->setFixedHeight(CTRL_HEIGHT);

    m_pSecLabel = new QLabel(m_pWidget);
	m_pSecLabel->setText(QStringLiteral("s"));
	m_pSecLabel->setAlignment(Qt::AlignCenter);
	m_pSecLabel->setFixedWidth(CTRL_WIDTH);
	m_pSecLabel->setFixedHeight(CTRL_HEIGHT);

    m_pMsecEdit = new QLineEdit(m_pWidget);
	m_pMsecEdit->setFixedWidth(CTRL_WIDTHW);
	m_pMsecEdit->setFixedHeight(CTRL_HEIGHT);

    m_pMsecLabel = new QLabel(m_pWidget);
	m_pMsecLabel->setText(QStringLiteral("ms"));
	m_pMsecLabel->setAlignment(Qt::AlignCenter);
	m_pMsecLabel->setFixedWidth(CTRL_WIDTH);
	m_pMsecLabel->setFixedHeight(CTRL_HEIGHT);

	//
    m_pYesBtn = new QPushButton(this);
	m_pYesBtn->setText(QStringLiteral("yes"));
	m_pYesBtn->setFixedWidth(CTRL_WIDTH * 3);
	m_pYesBtn->setFixedHeight(CTRL_HEIGHT);
    connect(m_pYesBtn, &QPushButton::clicked, this, &CChartTransPage::acceptBtnHandle);

    m_pNoBtn = new QPushButton(this);
	m_pNoBtn->setText(QStringLiteral("no"));
	m_pNoBtn->setFixedWidth(CTRL_WIDTH * 3);
	m_pNoBtn->setFixedHeight(CTRL_HEIGHT);
    connect(m_pNoBtn, &QPushButton::clicked, this, &CChartTransPage::cancelBtnHandle);

    m_pApplyBtn = new QPushButton(this);
	m_pApplyBtn->setText(QStringLiteral("apply"));
	m_pApplyBtn->setFixedWidth(CTRL_WIDTH * 3);
	m_pApplyBtn->setFixedHeight(CTRL_HEIGHT);
    connect(m_pApplyBtn, &QPushButton::clicked, this, &CChartTransPage::applyBtnHandle);

}

void CChartTransPage::layout()
{
	QRect rtClient = rect();
	QRect rtWidget;
	rtWidget.setTop(rtWidget.top() + CTL_SPACE_20 * 2);
	rtWidget.setBottom(rtClient.bottom() - CTL_SPACE_20);
	rtWidget.setLeft(CTL_SPACE_2);
	rtWidget.setRight(rtClient.right() - CTL_SPACE_2);
	m_pWidget->setGeometry(rtWidget);

	QRect rtWidgetFrame = m_pWidget->rect();

	QPoint ptLeft, ptMid;
	ptLeft.setX(rtWidgetFrame.left() + CTL_SPACE_20);
	ptLeft.setY(rtWidgetFrame.top() + CTL_SPACE_10);

	ptMid.setX(ptLeft.x() + CTL_SPACE_20 * 4);
	ptMid.setY(ptLeft.y());

	// 1
	QPoint ptParamChooseLabel;
	ptParamChooseLabel.setX(ptLeft.x());
	ptParamChooseLabel.setY(ptLeft.y());
	m_pParamChooseLabel->move(ptParamChooseLabel);

	m_pParamCombo->move(ptMid);

	int nOffset = 0;
	// 2
	m_pTransChooseLabel->move(ptLeft.x(), ptLeft.y() + CTL_SPACE_4 + CTRL_HEIGHT);
	m_pXlabel->move(ptMid.x(), ptMid.y() + CTL_SPACE_4 + CTRL_HEIGHT);
	nOffset = m_pXlabel->width() + CTL_SPACE_1;
	m_pXEdit->move(ptMid.x() + nOffset, ptMid.y() + CTL_SPACE_4 + CTRL_HEIGHT);

	nOffset += (m_pXEdit->width() + CTL_SPACE_4);
	m_pCoordinateSelectBtn->move(ptMid.x() + nOffset, ptMid.y() + CTL_SPACE_4 + CTRL_HEIGHT);

	// 3
	m_pTransOrientationLabel->move(ptLeft.x(), ptLeft.y() + CTL_SPACE_4 * 2 + CTRL_HEIGHT * 2);
	nOffset = 0;
	m_pOrientionCombo->move(ptMid.x(), ptMid.y() + CTL_SPACE_4 * 2 + CTRL_HEIGHT * 2);

	// 4
	m_pTimeRangeLabel->move(ptLeft.x(), ptLeft.y() + CTL_SPACE_4 * 3 + CTRL_HEIGHT * 3);
	m_pHourEdit->move(ptMid.x(), ptMid.y() + CTL_SPACE_4 * 3 + CTRL_HEIGHT * 3);
	nOffset = 0;
	nOffset += (m_pHourEdit->width() + CTL_SPACE_1);
	m_pHourLabel->move(ptMid.x() + nOffset, ptMid.y() + CTL_SPACE_4 * 3 + CTRL_HEIGHT * 3);
	nOffset += (m_pHourLabel->width() + CTL_SPACE_1);
	m_pMinEdit->move(ptMid.x() + nOffset, ptMid.y() + CTL_SPACE_4 * 3 + CTRL_HEIGHT * 3);
	nOffset += (m_pMinEdit->width() + CTL_SPACE_1);
	m_pMinLabel->move(ptMid.x() + nOffset, ptMid.y() + CTL_SPACE_4 * 3 + CTRL_HEIGHT * 3);
	nOffset += (m_pMinLabel->width() + CTL_SPACE_1);
	m_pSecEdit->move(ptMid.x() + nOffset, ptMid.y() + CTL_SPACE_4 * 3 + CTRL_HEIGHT * 3);
	nOffset += (m_pSecEdit->width() + CTL_SPACE_1);
	m_pSecLabel->move(ptMid.x() + nOffset, ptMid.y() + CTL_SPACE_4 * 3 + CTRL_HEIGHT * 3);
	nOffset += (m_pSecLabel->width() + CTL_SPACE_1);
	m_pMsecEdit->move(ptMid.x() + nOffset, ptMid.y() + CTL_SPACE_4 * 3 + CTRL_HEIGHT * 3);
	nOffset += (m_pMsecEdit->width() + CTL_SPACE_1);
	m_pMsecLabel->move(ptMid.x() + nOffset, ptMid.y() + CTL_SPACE_4 * 3 + CTRL_HEIGHT * 3);

	//bottom button
	QPoint ptBottomRight;
	int nOffsetX = 0;
	int nOffsetY = 0;
	nOffsetX += (m_pApplyBtn->width() + CTL_SPACE_4);
	ptBottomRight.setX(rtClient.right() - nOffsetX);
	nOffsetY += (m_pApplyBtn->height() + CTL_SPACE_10);
	ptBottomRight.setY(rtClient.bottom() - nOffsetY);
	m_pApplyBtn->move(ptBottomRight);

	m_pNoBtn->move(m_pApplyBtn->pos().x() - m_pNoBtn->width() - CTL_SPACE_2, ptBottomRight.y());
	m_pYesBtn->move(m_pNoBtn->pos().x() - m_pYesBtn->width() - CTL_SPACE_2, ptBottomRight.y());

}

void CChartTransPage::changeParam(int index)
{
	static int i = 0;
	i++;
}

void CChartTransPage::changeOriention(int index)
{
	static int i = 0;
	i++;
}

void CChartTransPage::coordinateSelect()
{
	static int i = 0;
	i++;
}

void CChartTransPage::acceptBtnHandle()
{
	if (m_pChartWidget)
	{
		m_pChartWidget->trans(m_CCTransData);
	}

    QDialog::accept();
}

void CChartTransPage::cancelBtnHandle()
{
    QDialog::reject();
}

void CChartTransPage::applyBtnHandle()
{
	getData();

	if (m_pChartWidget)
	{
		m_pChartWidget->trans(m_CCTransData);
	}

	/*test*/

	CCurveConfigureData& data = CCurveConfigure::GetInstance()->GetData();
	CCurveConfigure::GetInstance()->SetData(data);
}

void CChartTransPage::initData()
{

}

void CChartTransPage::setData(const CCTransData& data)
{

}

CCTransData CChartTransPage::getData()
{
	m_CCTransData.index = m_pParamCombo->currentIndex();
	m_CCTransData.param = m_pParamCombo->currentText();
	m_CCTransData.pt.setX(m_pXEdit->text().toInt());
	bool bOrient = !(m_pOrientionCombo->currentText().compare(QStringLiteral("����")));
	m_CCTransData.orientation = bOrient;
	int nH = m_pHourEdit->text().toInt();
	int nM = m_pMinEdit->text().toInt();
	int nS = m_pSecEdit->text().toInt();
	int nMs = m_pMsecLabel->text().toInt();
	QDateTime time;
	//
	m_CCTransData.time = time;

	return m_CCTransData;
}

void CChartTransPage::setChartWidget(CChartView* pChartWidget)
{
	m_pChartWidget = pChartWidget;
}

//------------------------

//----------------------------------------------
//----------------------------------------------
#define ID_GROUP_CURVE	1000
#define ID_STATIC_CTRLNUM 1001
#define ID_COMBO_CTRLNUM 1002
#define ID_TREE_CURVE	1003

#define ID_STATIC_NAME	1004
#define ID_STATIC_PARAMNUM 1005

#define ID_NAME_BEGIN 1100
#define ID_NUM_BEGIN   1200
#define ID_SCROLL_BEGIN 1300
#define ID_PARAM_BEGIN 1400

#define GET_PARAMCTRL_ID	(ID_PARAM_BEGIN + iCurve * m_iTotalParamNum * 7 + iParam * 7)




CXChartOptionPageEX::CXChartOptionPageEX(QWidget* parent):QDialog(parent)
{
	
}

CXChartOptionPageEX::CXChartOptionPageEX(FlightItemDataVector& fileList, QWidget* parent)
	: m_flightList(fileList), QDialog(parent)
{

}

void CXChartOptionPageEX::init()
{
	genCurveConfigDataByFlighData(m_flightList, m_CurveConfigFlight);
	initConfigureData();
	compareFlightConfToConfData(m_CurveConfigFlight, m_CurveConfigData);
	initCtrl();
	setCurveConfig(m_CurveConfigData);
	updateChartView();
	saveCurveConfigData();
}

bool CXChartOptionPageEX::setTotalFileList(FlightItemDataVector& fileList)
{
	bool bRet = true;
	static bool bInit = false;
	if (fileList.size() <= 0)
	{
		return bRet;
	}

	if (!bInit)
	{
		m_flightList = fileList;
		init();
		bInit = true;
	}
	return bRet;
}


void CXChartOptionPageEX::initCtrl()
{
    setFixedSize(CONFIWND_WIDTH, CONFIWND_HEIGHT);
    setWindowTitle("curve set");

	auto& pluginNum = m_CurveConfigData.pluginNumber;
	auto& paramNum = m_CurveConfigData.paramNumber;

	//curve set
    m_mapCtrl[ID_GROUP_CURVE] = new QGroupBox(QStringLiteral("curve set"), this);
    m_mapCtrl[ID_STATIC_CTRLNUM] = new QLabel(QStringLiteral("control number"), m_mapCtrl[ID_GROUP_CURVE]);
    QComboBox* pComboCurveNum = new QComboBox(m_mapCtrl[ID_GROUP_CURVE]);
	for (int i = 0; i < pluginNum; i++)
	{
        pComboCurveNum->addItem(QString::number(i + 1));
	}
    connect(pComboCurveNum, &QComboBox::currentTextChanged, this, &CXChartOptionPageEX::onCurveNumChange);
	m_mapCtrl[ID_COMBO_CTRLNUM] = pComboCurveNum;
    QTreeWidget* pTreeCurve = new QTreeWidget(m_mapCtrl[ID_GROUP_CURVE]);
	pTreeCurve->setHeaderHidden(true);
    connect(pTreeCurve, &QTreeWidget::currentItemChanged, this, &CXChartOptionPageEX::onCurveItemChange);
	m_mapCtrl[ID_TREE_CURVE] = pTreeCurve;

    m_mapCtrl[ID_STATIC_NAME] = new QLabel("curve name", this);
    m_mapCtrl[ID_STATIC_PARAMNUM] = new QLabel("curve number", this);

	//different ctrl 
	for (int iCurve = 0; iCurve < pluginNum; iCurve++)
	{
		auto& curvePlugin = m_CurveConfigData.curvePluginVec[iCurve];

		//curve name
        m_mapCtrl[ID_NAME_BEGIN + iCurve] = new QLineEdit(this);
		//param number
        QComboBox* pComboParamNum = new QComboBox(this);

		//total param number
		int nTotal = curvePlugin.paramNum;
		qDebug() << nTotal;

		for (int i = 0; i < paramNum; i++)
		{
            pComboParamNum->addItem(QString::number(i + 1));
		}
        connect(pComboParamNum, &QComboBox::currentTextChanged, this, &CXChartOptionPageEX::onParamNumChange);
		m_mapCtrl[ID_NUM_BEGIN + iCurve] = pComboParamNum;
		//param area
		QScrollArea* pScrollArea = new QScrollArea(this);
#if 0
		pScrollArea->setStyleSheet("background-color:rgb(46,46,46);");
#endif // 0

		QWidget* qScrollWidget = new QWidget(pScrollArea);
		pScrollArea->setWidget(qScrollWidget);
		m_mapCtrl[ID_SCROLL_BEGIN + iCurve] = pScrollArea;

		for (int iParam = 0; iParam < paramNum; iParam++)
		{
			auto& paramGroup = curvePlugin.paramVec[iParam];
			auto& groupName = paramGroup.groupName;
			qDebug() << groupName;

            m_mapCtrl[GET_PARAMCTRL_ID] = new QGroupBox(QString("teach param%1").arg(QString::number(iParam + 1)), qScrollWidget);
			
			//param choose combox list
            QComboBox* pComboParamType = new QComboBox(qScrollWidget);
			for (int i = 0; i < paramNum; i++)
			{

				auto& strParamName = paramGroup.paramNameVector[i];
				pComboParamType->addItem(strParamName);

				qDebug() << strParamName;
			}

			auto& nParamIndex = paramGroup.paramChooseIndex;
			qDebug() << nParamIndex;

			pComboParamType->setCurrentIndex(nParamIndex);

            m_mapCtrl[GET_PARAMCTRL_ID + 1] = new QLabel("param choose", qScrollWidget);
			m_mapCtrl[GET_PARAMCTRL_ID + 2] = pComboParamType;

            m_mapCtrl[GET_PARAMCTRL_ID + 3] = new QLabel("param name", qScrollWidget);
			auto& paramName = paramGroup.paramCurName;
            QLineEdit* pEdit = new QLineEdit(qScrollWidget);
			pEdit->setText(paramName);
			m_mapCtrl[GET_PARAMCTRL_ID + 4] = pEdit;

			//update edit value
			//connect(pComboParamType, &CXEComboBox::onCurrentTextChange, pEdit, &CXELineEdit::setText);
			connect(pComboParamType, SIGNAL(currentTextChanged(const QString&)), pEdit, SIGNAL(setText(const QString&)));

            m_mapCtrl[GET_PARAMCTRL_ID + 5] = new QLabel("show color", qScrollWidget);
            HKColorCtrl* pColorCtrl = new HKColorCtrl(qScrollWidget);
			m_mapCtrl[GET_PARAMCTRL_ID + 6] = pColorCtrl;
		}
	}


	//bottom button
    m_pDefaultBtn = new QPushButton(this);
	m_pDefaultBtn->setText(QStringLiteral("default"));
	m_pDefaultBtn->setFixedWidth(CTRL_WIDTH * 6);
	m_pDefaultBtn->setFixedHeight(CTRL_HEIGHT);
    connect(m_pDefaultBtn, &QPushButton::clicked, this, &CXChartOptionPageEX::defaultBtnHandle);

    m_pYesBtn = new QPushButton(this);
	m_pYesBtn->setText(QStringLiteral("yes"));
	m_pYesBtn->setFixedWidth(CTRL_WIDTH * 3);
	m_pYesBtn->setFixedHeight(CTRL_HEIGHT);
    connect(m_pYesBtn, &QPushButton::clicked, this, &CXChartOptionPageEX::acceptBtnHandle);

    m_pNoBtn = new QPushButton(this);
	m_pNoBtn->setText(QStringLiteral("cancel"));
	m_pNoBtn->setFixedWidth(CTRL_WIDTH * 3);
	m_pNoBtn->setFixedHeight(CTRL_HEIGHT);
    connect(m_pNoBtn, &QPushButton::clicked, this, &CXChartOptionPageEX::cancelBtnHandle);

    m_pApplyBtn = new QPushButton(this);
	m_pApplyBtn->setText(QStringLiteral("apply"));
	m_pApplyBtn->setFixedWidth(CTRL_WIDTH * 3);
	m_pApplyBtn->setFixedHeight(CTRL_HEIGHT);
    connect(m_pApplyBtn, &QPushButton::clicked, this, &CXChartOptionPageEX::applyBtnHandle);
}

#define STATIC_WIDTH 80
#define STATIC_HEIGHT 24
#define EDITT_WIDTH	120

void CXChartOptionPageEX::layout()
{
	QRect rtClient = rect();

	//curve set
	int x = 0;
	int y = 10;
	COL_ALIGN_CTRL(m_mapCtrl[ID_GROUP_CURVE], x, y, 200, 475);

	x += 20;
	y += 20;
	COL_ALIGN_CTRL(m_mapCtrl[ID_STATIC_CTRLNUM], x, y, STATIC_WIDTH, STATIC_HEIGHT);

	x += STATIC_WIDTH;
	COL_ALIGN_CTRL(m_mapCtrl[ID_COMBO_CTRLNUM], x, y, STATIC_WIDTH, STATIC_HEIGHT);

	x = 10;
	y += STATIC_HEIGHT + 10;
	COL_ALIGN_CTRL(m_mapCtrl[ID_TREE_CURVE], x, y, 180, 400);

	//curve name
	x = 200 + 20;
	y = 20;
	COL_ALIGN_CTRL(m_mapCtrl[ID_STATIC_NAME], x, y, STATIC_WIDTH, STATIC_HEIGHT);

    QModelIndex modeIndex = GET_TYPE_CTRL(QTreeWidget*, ID_TREE_CURVE)->currentIndex();
	int iIndex = modeIndex.row();
	x += STATIC_WIDTH + 10;
	for (int iCurve = 0; iCurve < TOTAL_CURVE_NUM; iCurve++)
	{
		COL_ALIGN_CTRL(m_mapCtrl[ID_NAME_BEGIN + iCurve], x, y, 120, STATIC_HEIGHT);
	}

	//param number
	x = 200 + 20;
	y += STATIC_HEIGHT + 10;
	COL_ALIGN_CTRL(m_mapCtrl[ID_STATIC_PARAMNUM], x, y, STATIC_WIDTH, STATIC_HEIGHT);

	x += STATIC_WIDTH + 10;
	for (int iCurve = 0; iCurve < TOTAL_CURVE_NUM; iCurve++)
	{
		COL_ALIGN_CTRL(m_mapCtrl[ID_NUM_BEGIN + iCurve], x, y, 120, STATIC_HEIGHT);
	}


	//param area
	int scrollY = y + STATIC_HEIGHT + 10;
	for (int iCurve = 0; iCurve < m_CurveNum; iCurve++)
	{
		x = 200 + 10;
		y = scrollY;
		COL_ALIGN_CTRL(m_mapCtrl[ID_SCROLL_BEGIN + iCurve], x, y, 280, 400);
		COL_ALIGN_CTRL(GET_TYPE_CTRL(QScrollArea*, ID_SCROLL_BEGIN + iCurve)->widget(), x, y, 240, 400);
		x = 0; y = 0;
		for (int iParam = 0; iParam < m_iTotalParamNum; iParam++)
		{
			x = 10;
			y += 10;
			COL_ALIGN_CTRL(m_mapCtrl[GET_PARAMCTRL_ID], x, y, 230, 120);

			x += 10;
			y += 20;
			COL_ALIGN_CTRL(m_mapCtrl[GET_PARAMCTRL_ID + 1], x, y, STATIC_WIDTH, STATIC_HEIGHT);
			x += STATIC_WIDTH;
			COL_ALIGN_CTRL(m_mapCtrl[GET_PARAMCTRL_ID + 2], x, y, EDITT_WIDTH, STATIC_HEIGHT);

			x = 10 + 10;
			y += STATIC_HEIGHT + 10;
			COL_ALIGN_CTRL(m_mapCtrl[GET_PARAMCTRL_ID + 3], x, y, STATIC_WIDTH, STATIC_HEIGHT);
			x += STATIC_WIDTH;
			COL_ALIGN_CTRL(m_mapCtrl[GET_PARAMCTRL_ID + 4], x, y, EDITT_WIDTH, STATIC_HEIGHT);

			x = 10 + 10;
			y += STATIC_HEIGHT + 10;
			COL_ALIGN_CTRL(m_mapCtrl[GET_PARAMCTRL_ID + 5], x, y, STATIC_WIDTH, STATIC_HEIGHT);
			x += STATIC_WIDTH;
			COL_ALIGN_CTRL(m_mapCtrl[GET_PARAMCTRL_ID + 6], x, y, EDITT_WIDTH, STATIC_HEIGHT);
			y += STATIC_HEIGHT + 10;
		}
	}
	showCtrl();

	//bottom button
	QPoint ptBottomLeft;
	ptBottomLeft.setX(rtClient.left() + CTL_SPACE_4 * 2);
	ptBottomLeft.setY(rtClient.bottom() - (m_pDefaultBtn->height() + CTL_SPACE_10));
	m_pDefaultBtn->move(ptBottomLeft);

	QPoint ptBottomRight;
	int nOffsetX = 0;
	int nOffsetY = 0;
	nOffsetX += (m_pApplyBtn->width() + CTL_SPACE_4 * 2);
	ptBottomRight.setX(rtClient.right() - nOffsetX);
	nOffsetY += (m_pApplyBtn->height() + CTL_SPACE_10);
	ptBottomRight.setY(rtClient.bottom() - nOffsetY);
	m_pApplyBtn->move(ptBottomRight);

	m_pNoBtn->move(m_pApplyBtn->pos().x() - m_pNoBtn->width() - CTL_SPACE_2, ptBottomRight.y());
	m_pYesBtn->move(m_pNoBtn->pos().x() - m_pYesBtn->width() - CTL_SPACE_2, ptBottomRight.y());


}

void CXChartOptionPageEX::changeEvent(QEvent* event)
{

}

void CXChartOptionPageEX::resizeEvent(QResizeEvent* event)
{
	layout();
}

void CXChartOptionPageEX::onCurveNumChange(const QString& str)
{
    int iCurveNum = GET_TYPE_CTRL(QComboBox*, ID_COMBO_CTRLNUM)->currentIndex() + 1;

    QTreeWidget* pTreeCurve = GET_TYPE_CTRL(QTreeWidget*, ID_TREE_CURVE);
	pTreeCurve->clear();
	for (int iCurve = 0; iCurve < iCurveNum; iCurve++)
	{
        QString sName = GET_TYPE_CTRL(QLineEdit*, ID_NAME_BEGIN + iCurve)->text();
		QTreeWidgetItem* pItem = new QTreeWidgetItem();
		pItem->setText(0, sName);
		pTreeCurve->addTopLevelItem(pItem);
		if (iCurve == 0)
			pTreeCurve->setCurrentItem(pItem);
	}
	showCtrl();
}

void CXChartOptionPageEX::onCurveItemChange(QTreeWidgetItem* current, QTreeWidgetItem* previous)
{
	showCtrl();
}

void CXChartOptionPageEX::onParamNumChange(const QString& str)
{
	showCtrl();
}

void CXChartOptionPageEX::showCtrl()
{
    QModelIndex modeIndex = GET_TYPE_CTRL(QTreeWidget*, ID_TREE_CURVE)->currentIndex();
	int iIndex = modeIndex.row();

	for (int iCurve = 0; iCurve < m_CurveNum; iCurve++)
	{
		if (iCurve == iIndex)
		{
			m_mapCtrl[ID_NAME_BEGIN + iCurve]->show();
		}
		else
		{
			m_mapCtrl[ID_NAME_BEGIN + iCurve]->hide();
		}
	}

	for (int iCurve = 0; iCurve < m_CurveNum; iCurve++)
	{
		if (iCurve == iIndex)
		{
			m_mapCtrl[ID_NUM_BEGIN + iCurve]->show();
		}
		else
		{
			m_mapCtrl[ID_NUM_BEGIN + iCurve]->hide();
		}
	}

	for (int iCurve = 0; iCurve < m_CurveNum; iCurve++)
	{
		if (iCurve == iIndex)
		{
			int iHeight = 0;
			m_mapCtrl[ID_SCROLL_BEGIN + iCurve]->show();
            int iParamNum = GET_TYPE_CTRL(QComboBox*, ID_NUM_BEGIN + iCurve)->currentIndex() + 1;
			for (int iParam = 0; iParam < m_iTotalParamNum; iParam++)
			{
				if (iParam >= iParamNum)
				{
					for (int i = 0; i < 7; i++)
					{
						m_mapCtrl[GET_PARAMCTRL_ID + i]->hide();
					}
				}
				else
				{
					for (int i = 0; i < 7; i++)
					{
						m_mapCtrl[GET_PARAMCTRL_ID + i]->show();
					}
					iHeight = m_mapCtrl[GET_PARAMCTRL_ID]->pos().y() + m_mapCtrl[GET_PARAMCTRL_ID]->rect().height();
				}
			}
			QWidget* widget = GET_TYPE_CTRL(QScrollArea*, ID_SCROLL_BEGIN + iCurve)->widget();
			QRect rect = widget->rect();
			rect.setHeight(iHeight);
			widget->setGeometry(rect);
		}
		else
		{
			m_mapCtrl[ID_SCROLL_BEGIN + iCurve]->hide();
		}
	}
}

void CXChartOptionPageEX::getCurveConfig(CCurveConfigureData& curveConfigData)
{

    int iCurveNun = GET_TYPE_CTRL(QComboBox*, ID_COMBO_CTRLNUM)->currentIndex() + 1;
	for (int iCurve = 0; iCurve < iCurveNun; iCurve++)
	{
		auto& curvePlugin = curveConfigData.curvePluginVec[iCurve];
		auto& curveName	  = curvePlugin.curveName;
		auto& curveIndex  = curvePlugin.currentParamIndex;
		auto& paramNum	  = curvePlugin.paramNum;

        curveName = GET_TYPE_CTRL(QLineEdit*, ID_NAME_BEGIN + iCurve)->text();
        curveIndex = GET_TYPE_CTRL(QComboBox*, ID_NUM_BEGIN + iCurve)->currentIndex();
		for (int iParam = 0; iParam < paramNum; iParam++)
		{
			auto& paramGroup = curvePlugin.paramVec[iParam];
            paramGroup.paramChooseIndex = GET_TYPE_CTRL(QComboBox*, GET_PARAMCTRL_ID + 2)->currentIndex();
            paramGroup.paramChooseName = GET_TYPE_CTRL(QComboBox*, GET_PARAMCTRL_ID + 2)->currentText();
            paramGroup.paramCurName = GET_TYPE_CTRL(QLineEdit*, GET_PARAMCTRL_ID + 4)->text();
            paramGroup.color = GET_TYPE_CTRL(HKColorCtrl*, GET_PARAMCTRL_ID + 6)->getColor();
		}
	}
}


void CXChartOptionPageEX::setCurveConfig(CCurveConfigureData& curveConfigData)
{

	auto& currentPluginIndex = curveConfigData.currentPluginIndex;
    GET_TYPE_CTRL(QComboBox*, ID_COMBO_CTRLNUM)->setCurrentIndex(currentPluginIndex);

    QTreeWidget* pTreeCurve = GET_TYPE_CTRL(QTreeWidget*, ID_TREE_CURVE);
	pTreeCurve->clear();

	auto& curveNum = curveConfigData.pluginNumber;
	for (int iCurve = 0; iCurve < curveNum; iCurve++)
	{
		auto& curvePlugin = m_CurveConfigData.curvePluginVec[iCurve];
		auto& curveName = curvePlugin.curveName;
		auto& curveIndex = curvePlugin.currentParamIndex;

		QTreeWidgetItem* pItem = new QTreeWidgetItem();
		pItem->setText(0, curveName);
		pTreeCurve->addTopLevelItem(pItem);
		if (iCurve == 0)
		{
			pTreeCurve->setCurrentItem(pItem);
		}

        GET_TYPE_CTRL(QLineEdit*, ID_NAME_BEGIN + iCurve)->setText(curveName);
        GET_TYPE_CTRL(QComboBox*, ID_NUM_BEGIN + iCurve)->setCurrentIndex(curveIndex);
		for (int iParam = 0; iParam < curvePlugin.paramNum; iParam++)
		{
			auto& paramGroupVec = curvePlugin.paramVec[iParam];
			auto& currentParamIndex = paramGroupVec.paramChooseIndex;
			auto& chooseParamName = paramGroupVec.paramChooseName;
			auto& color = paramGroupVec.color;

            GET_TYPE_CTRL(QComboBox*, GET_PARAMCTRL_ID + 2)->setCurrentIndex(currentParamIndex);
            GET_TYPE_CTRL(QLineEdit*, GET_PARAMCTRL_ID + 4)->setText(chooseParamName);
            GET_TYPE_CTRL(HKColorCtrl*, GET_PARAMCTRL_ID + 6)->setColor(color);  //wait by modify
		}
	}
	update();
}

void CXChartOptionPageEX::defaultBtnHandle()
{
    QDialog::accept();
}

void CXChartOptionPageEX::acceptBtnHandle()
{
	getCurveConfig(m_CurveConfigData);
	updateChartView();
	saveCurveConfigData();

    QDialog::accept();
}

void CXChartOptionPageEX::cancelBtnHandle()
{
    QDialog::reject();
}

void CXChartOptionPageEX::applyBtnHandle()
{
	getCurveConfig(m_CurveConfigData);
	updateChartView();
	saveCurveConfigData();
}

void CXChartOptionPageEX::updateEditText(QString str)
{

}

void CXChartOptionPageEX::setFileList(FlightItemDataVector& fileList)
{
	m_flightList = fileList;
}

void CXChartOptionPageEX::initParamIndexMap()
{
	m_iTotalParamNum = m_flightList.size();
	for (int i = 0; i < m_iTotalParamNum; ++i)
	{
		m_paramIndexMap[i] = m_flightList[i].strLabel;
	}
}

void CXChartOptionPageEX::setChartWidget(CChartView* pChartWidget)
{
	m_pChartWidget = pChartWidget;
}

void CXChartOptionPageEX::getCurveItemVec()
{

}

void CXChartOptionPageEX::updateChartView()
{

	if (m_pChartWidget)
	{
		//set curve property
		auto& curvePluginVec = m_CurveConfigData.curvePluginVec;
		for (int i = 0; i< curvePluginVec.size(); ++i)
		{
			auto strCurveName = curvePluginVec[i].curveName;
			auto vecCureParam = curvePluginVec[i].paramVec;
			auto nCurIndex    = curvePluginVec[i].currentParamIndex;
			auto curParamNum  = nCurIndex + 1;

			ChartPropertyVec chartPropertyVec;
			FlightItemDataVector flightDataList;
			for (int j = 0; j< curParamNum; ++j)
			{
				auto iTypeIndex = vecCureParam[j].paramChooseIndex;
				auto sName = vecCureParam[j].paramChooseName;
				auto color = vecCureParam[j].color;

				CChartViewProperty chartViewProperty;
				chartViewProperty.strTitle = sName;
				chartViewProperty.color = color;
				chartViewProperty.dWidth = 2;
				chartPropertyVec.push_back(chartViewProperty);

				// choose current data to set curve view
				for (int idata = 0; idata < m_flightList.size(); idata++)
				{
					if (m_flightList.at(idata).strLabel == sName)
					{
						flightDataList.push_back(m_flightList.at(idata));
						break;
					}
				}
			}

			//set curve new property + data
			m_pChartWidget->SetChart(chartPropertyVec, flightDataList);
		}

	}

}

void CXChartOptionPageEX::initConfigureData()
{
	m_CurveConfigData = CCurveConfigure::GetInstance()->GetData();
	checkConfigDataValid(m_CurveConfigData);

	m_CurveNum = m_CurveConfigData.pluginNumber;
	m_ParamNum = m_CurveConfigData.paramNumber;
}

void CXChartOptionPageEX::initChartPageData()
{
	//compare configure data to current data

	m_CurveItemVectorEX.clear();

	QString str = QStringLiteral("curve");
	for (int i = 0; i < m_CurveNum; ++i)
	{
		std::shared_ptr<CCurveItemEX> pCurveItem(new CCurveItemEX);
		pCurveItem->sCurveName = str + QString("%1").arg(QString::number(i));

		auto& paramVector = m_CurveConfigData.curvePluginVec[i];
		ChartPropertyVec chartPropertyVec;
		FlightItemDataVector flightDataList;

		const int nParamNum = m_flightList.size();
		for (int j = 0; j < nParamNum; ++j)
		{
			std::shared_ptr<CCurveItemParamEX> pCurveParam(new CCurveItemParamEX);

			auto& configStr = paramVector.paramVec[j].paramChooseName;
			auto& dataStr = m_flightList.at(j).strLabel;
			bool bCompare = (dataStr == configStr);
			auto& configColor = paramVector.paramVec[j].color;
			bool bValidColor = configColor.isValid();
			if (bValidColor)
			{
				pCurveParam->color = configColor;
			}
			else
			{
				//set default color
				int k = j % 3;
				QColor qColor(Qt::black);
				if (0 == k)
				{
					qColor = Qt::darkYellow;
				}
				else if (1 == k)
				{
					qColor = Qt::darkMagenta;
				}
				else if (2 == k)
				{
					qColor = Qt::darkCyan;
				}

				pCurveParam->color = qColor;
			}
			
			pCurveParam->iTypeIndex = j;
			pCurveParam->sName = dataStr;
			pCurveItem->vecCurveParam.push_back(pCurveParam);

			CChartViewProperty chartViewProperty;
			chartViewProperty.strTitle = pCurveParam->sName;
			chartViewProperty.color = pCurveParam->color;
			chartViewProperty.dWidth = 3;
			chartPropertyVec.push_back(chartViewProperty);

			flightDataList.push_back(m_flightList.at(j));
		}

		m_CurveItemVectorEX.push_back(pCurveItem);
	}
}

bool CXChartOptionPageEX::saveCurveConfigData()
{
	bool bRet = true;

	CCurveConfigure::GetInstance()->SetData(m_CurveConfigData);

	return bRet;
}

bool CXChartOptionPageEX::genCurveConfigDataByFlighData
		(const FlightItemDataVector& flightList, CCurveConfigureData& curveConfigData)
{
	bool bRet = true;

	if (flightList.size() <= 0)
		return false;

	m_iTotalParamNum = flightList.size();
	curveConfigData.paramNumber = flightList.size();
	curveConfigData.pluginNumber = DEFAULT_CURVE_NUM;
	curveConfigData.currentPluginIndex = 0;

	curveConfigData.curvePluginVec;

	//generate different plugin data
	for (int i = 0; i < curveConfigData.pluginNumber; ++i)
	{
		CCurvePlugin curvePlugin;
		curvePlugin.paramNum = curveConfigData.paramNumber;
		int nCurrentParamIndex = std::min(curvePlugin.paramNum, DEFAULT_PARAM_NUM);
		curvePlugin.currentParamIndex = nCurrentParamIndex;
		curvePlugin.paramVec;

		for (int j = 0; j < curveConfigData.paramNumber; ++j)
		{
			CParamGroup paramGroup;
			paramGroup.paramChooseIndex = j;
			paramGroup.paramChooseName = m_flightList.at(j).strLabel;
			paramGroup.paramCurName = paramGroup.paramChooseName;

			//set default color
			int k = j % 3;
			QColor qColor(Qt::black);
			if (0 == k)
			{
				qColor = Qt::darkYellow;
			}
			else if (1 == k)
			{
				qColor = Qt::darkMagenta;
			}
			else if (2 == k)
			{
				qColor = Qt::darkCyan;
			}
			paramGroup.color = qColor;

			//add all param name
			for (int k = 0; k < curveConfigData.paramNumber; ++k)
			{
				auto& paramName = m_flightList.at(k).strLabel;
				paramGroup.paramNameVector.push_back(paramName);
			}

			curvePlugin.paramVec.push_back(paramGroup);

		}

		curveConfigData.curvePluginVec.push_back(curvePlugin);

	}

	return bRet;
}

//src(flight)  --->  dst(configure)
bool CXChartOptionPageEX::compareFlightConfToConfData(CCurveConfigureData& flightConfData, CCurveConfigureData& confFigData)
{
	bool bRet = true;

	auto& srcPluginNum	= flightConfData.pluginNumber;
	auto& srcParamNum	= flightConfData.paramNumber;
	auto& dstPluginNum	= confFigData.pluginNumber;
	auto& dstParamNum	= confFigData.paramNumber;

	int i = 0;
	for ( ; i < srcPluginNum; ++i)
	{	
		auto& srcPlugin = flightConfData.curvePluginVec[i];
		auto& dstPlugin = confFigData.curvePluginVec[i];
		dstPlugin.paramNum = srcPlugin.paramNum;

		auto srcParamVecSize = srcPlugin.paramVec.size();
		auto dstParamVecSize = dstPlugin.paramVec.size();

		//two condition
		if (dstParamVecSize > srcParamVecSize)
		{
			// delete dst unnecessary data
			auto itor = dstPlugin.paramVec.begin();
			int nIndex = srcPlugin.paramNum;
			dstPlugin.paramVec.erase(itor + nIndex, dstPlugin.paramVec.end());

			//update paramNum and current ParamIndex
			dstPlugin.currentParamIndex =
				(dstPlugin.currentParamIndex > dstPlugin.paramNum) ? (dstPlugin.paramNum - 1) : dstPlugin.currentParamIndex;
		}
		else if (dstParamVecSize < srcParamVecSize)
		{
			// add dst necessary data
			int nn = dstParamVecSize;
			for (nn; nn < srcParamVecSize; ++nn)
			{
				CParamGroup paramGroup;
				dstPlugin.paramVec.push_back(paramGroup);
			}
		}

		//update dst param number 
		//dstPlugin.paramNum = srcPlugin.paramNum;
		int j = 0;
		for ( ; j < srcParamNum; ++j)
		{
			auto& srcParam = srcPlugin.paramVec[j];
			auto& dstParam = dstPlugin.paramVec[j];

			dstParam.paramNameVector.clear();
			bool bExist = false;
			for (int k = 0; k < srcParam.paramNameVector.size(); ++k)
			{
				auto& str = srcParam.paramNameVector[k];
				dstParam.paramNameVector.push_back(str);
				bExist = (dstParam.paramChooseName == str);
			}

			bool bValidColor = dstParam.color.isValid();
			if (!bValidColor)
			{
				dstParam.color = srcParam.color;
			}

			dstParam.paramChooseIndex = bExist ? dstParam.paramChooseIndex : srcParam.paramChooseIndex;
			dstParam.paramChooseName = bExist ? dstParam.paramChooseName : srcParam.paramChooseName;
			dstParam.paramCurName = srcParam.paramCurName;

		}

		// when dst param data more than src param data,delete other param data
		if (dstParamNum > srcParamNum)
		{
			auto itor = dstPlugin.paramVec.begin();
			dstPlugin.paramVec.erase(itor + j, dstPlugin.paramVec.end());
		}

	}

	confFigData.paramNumber		= flightConfData.paramNumber;
	confFigData.pluginNumber	= flightConfData.pluginNumber;
	

	return bRet;
}
 
bool CXChartOptionPageEX::checkConfigDataValid(CCurveConfigureData& flightConfData)
{
	bool bRet = true;

	//if conf data have nothing,we need create new default data
	bool bValid = (flightConfData.pluginNumber == 0) || (flightConfData.paramNumber == 0)
		|| (flightConfData.curvePluginVec.size() == 0);

	if (!bValid)
		return true;

	flightConfData.pluginNumber = DEFAULT_CURVE_NUM;
	flightConfData.paramNumber	= DEFAULT_PARAM_NUM;
	flightConfData.currentPluginIndex = 0;

	for (int i = 0; i < flightConfData.pluginNumber; ++i)
	{
		CCurvePlugin curvePlugin;
        QString sName = QString("curve%1").arg(QString::number(i));
		curvePlugin.curveName = sName;
		curvePlugin.paramNum = DEFAULT_PARAM_NUM;
		curvePlugin.currentParamIndex = DEFAULT_PARAM_NUM - 1;
		flightConfData.curvePluginVec.push_back(curvePlugin);

	}

	return bRet;
}
