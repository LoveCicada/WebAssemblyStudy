#include <QEvent>
#include "CXEGlobal.h"
#include "CXEVersion.h"
#include "CXChartOptionPage.h"
#include "CXEComboBox.h"
#include "CXESingleColorCtrl.h"
#include <QScrollarea>
#include "CXChartViewWnd.h"

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
#define DEFAULT_CURVE_NUM 4

#define DEFAULT_PARAM_NUM 3

int g_iTotalParamNum = 8;
std::vector<String> g_sParamLabel;
std::vector<String> g_sParamName;
//const WChar* g_sParamName[g_iTotalParamNum] =
//{
//	_T("height"),
//	_T("speed"),
//	_T("longitude"),
//	_T("Param name"),
//	_T("Param name"),
//	_T("Param name"),
//	_T("Param name"),
//	_T("Param name"),
//};

UInt32 g_ParamColor[8] =
{
	qRgba(128, 0, 0, 0xFF),
	qRgba(0, 128, 0, 0xFF),
	qRgba(0, 0, 128, 0xFF),
	qRgba(128, 0, 0, 0xFF),
	qRgba(128, 0, 0, 0xFF),
	qRgba(128, 0, 0, 0xFF),
	qRgba(128, 0, 0, 0xFF),
	qRgba(128, 0, 0, 0xFF),
};

CXChartOptionItem::CXChartOptionItem(IXUIOptionValueFactory* pValFact, CXChartViewWnd* pWnd, std::vector<String> vecLabe)
    : XUIOptionItem((_T("曲线控件")), _T("ChartOption"), _T("{BEA9DD76-BD39-49A7-9266-DF7FB88A91AD}"))
    , m_pOption(NULL)
    , m_pValFact(pValFact)
	, m_pChartWnd(pWnd)
{
	g_sParamLabel = vecLabe;
	g_sParamName = vecLabe;
	g_iTotalParamNum = vecLabe.size();

    XASSERT(m_pValFact != NULL);

    Int32 iVal;
    IXUIOptionValue* pVal;

	ADD_OPTION_INT_VAL(_T("CurveNum"), DEFAULT_CURVE_NUM);
	for (int iCurve = 0; iCurve < TOTAL_CURVE_NUM; iCurve++)
	{
		QString sName = QString(QString::fromStdWString(_T("曲线%1")).arg(QString::number(iCurve + 1)));

		ADD_OPTION_STR_VAL(_T("CurveName") + std::to_wstring(iCurve), sName.toStdWString().c_str());
		ADD_OPTION_INT_VAL(_T("ParamNum") + std::to_wstring(iCurve), DEFAULT_PARAM_NUM);

		for (int iParam = 0; iParam < g_iTotalParamNum; iParam++)
		{
			String sIndex = std::to_wstring(g_iTotalParamNum * iCurve + iParam);
			ADD_OPTION_INT_VAL(_T("ParamType") + sIndex, iParam);
			ADD_OPTION_STR_VAL(_T("ParamName") + sIndex, g_sParamName[iParam].c_str());
			ADD_OPTION_VAL(_T("ParamColor") + sIndex, g_ParamColor[iParam], Option_dword_type);
		}
	}

}

CXChartOptionItem::~CXChartOptionItem()
{
    XASSERT(m_pValFact != NULL);
    for (int i = 0 ; i < arrOptionVal.size() ; i++)
    {
        m_pValFact->DeleteValue(arrOptionVal[i]);
    }
    arrOptionVal.clear();
}

QWidget* CXChartOptionItem::CreateOptionsPage(QWidget* pParent, const QRect& rtWnd)
{
    if ( m_pOption != NULL )
        return m_pOption;

    m_pOption = new CXChartOptionPage(this, pParent);
	GetCurveParam();
	m_pOption->setCurveConfig(m_vecCurveItem);

	SetDefault();

    return m_pOption;
}

void CXChartOptionItem::DestoryOptionsPage(QWidget* pWnd)
{
    if ( pWnd == NULL ) return;
	CXChartOptionPage* pOptionPage = dynamic_cast<CXChartOptionPage*>(pWnd);
    XASSERT( pOptionPage != NULL );
    if ( pOptionPage == m_pOption )
    {
        m_pOption->close();
    }
    SAFE_DELETE(m_pOption);
}

void CXChartOptionItem::Apply()
{
    if (m_pOption != NULL)
        m_pOption->getCurveConfig(m_vecCurveItem);

	m_pChartWnd->updateCurveItem();
	setOptionData();
}

void CXChartOptionItem::SetDefault()
{
	m_vecCurveItem.clear();
	for (int iCurve = 0; iCurve < DEFAULT_CURVE_NUM; iCurve++)
	{
		QString sName = QString(QString::fromStdWString(_T("曲线%1")).arg(QString::number(iCurve + 1)));
		std::shared_ptr<CCurveItem> pCurveItem(new CCurveItem);
		pCurveItem->sCurveName = sName.toStdWString();

		for (int iParam = 0; iParam < DEFAULT_PARAM_NUM; iParam++)
		{
			if (g_sParamName.size() <= iParam)
			{
				break;
			}
			std::shared_ptr<CCurveItemParam> pCurveParam(new CCurveItemParam);
			pCurveParam->iTypeIndex = iParam;
			pCurveParam->sName = g_sParamName[iParam];
			pCurveParam->color = g_ParamColor[iParam];
			pCurveItem->vecCurveParam.push_back(pCurveParam);
		}
		m_vecCurveItem.push_back(pCurveItem);
	}
    if (m_pOption != NULL)
        m_pOption->setCurveConfig(m_vecCurveItem);
}

CurveItemVector&	CXChartOptionItem::GetCurveParam()
{
	if (m_vecCurveItem.size() == 0)
	{
		getOptionData();
	}
	return m_vecCurveItem;
}

void CXChartOptionItem::setOptionData()
{
	int index = 0;
	int iCurveNum = m_vecCurveItem.size();
	arrOptionVal[index++]->SetOptionValue(&iCurveNum);
	for (int iCurve = 0; iCurve < iCurveNum; iCurve++)
	{
		std::shared_ptr<CCurveItem> pCurveItem = m_vecCurveItem.at(iCurve);
		arrOptionVal[index++]->SetOptionValue((void*)(pCurveItem->sCurveName.c_str()));
		int iParamNum = pCurveItem->vecCurveParam.size();
		arrOptionVal[index++]->SetOptionValue(&iParamNum);
		for (int iParam = 0; iParam < g_iTotalParamNum; iParam++)
		{
			if (iParam >= iParamNum)
			{
				index += 3;
			}
			else
			{
				std::shared_ptr < CCurveItemParam> pCurveParam = pCurveItem->vecCurveParam.at(iParam);
				arrOptionVal[index++]->SetOptionValue(&(pCurveParam->iTypeIndex));
				arrOptionVal[index++]->SetOptionValue((void*)(pCurveParam->sName.c_str()));
				arrOptionVal[index++]->SetOptionValue(&(pCurveParam->color));
			}
		}
	}
}
void CXChartOptionItem::getOptionData()
{
	int index = 0;
	int iCurveNum = 0;
	arrOptionVal[index++]->GetOptionValue(&iCurveNum);
	for (int iCurve = 0; iCurve < iCurveNum; iCurve++)
	{
		std::shared_ptr<CCurveItem> pCurveItem(new CCurveItem);
		int size = arrOptionVal[index]->GetOptionValue(NULL);
		xwchar* ws = new xwchar[size];
		arrOptionVal[index++]->GetOptionValue(ws);
		pCurveItem->sCurveName = ws;
		SAFE_DELETE_ARRAY(ws);
		int iParamNum = 0;
		arrOptionVal[index++]->GetOptionValue(&iParamNum);
		for (int iParam = 0; iParam < g_iTotalParamNum; iParam++)
		{
			if (iParam >= iParamNum)
			{
				index += 3;
			}
			else
			{
				std::shared_ptr < CCurveItemParam> pCurveParam(new CCurveItemParam);
				arrOptionVal[index++]->GetOptionValue(&(pCurveParam->iTypeIndex));

				int size = arrOptionVal[index]->GetOptionValue(NULL);
				xwchar* ws = new xwchar[size];
				arrOptionVal[index++]->GetOptionValue(ws);
				pCurveParam->sName = ws;
				SAFE_DELETE_ARRAY(ws);

				arrOptionVal[index++]->GetOptionValue(&(pCurveParam->color));
				pCurveItem->vecCurveParam.push_back(pCurveParam);
			}
		}
		m_vecCurveItem.push_back(pCurveItem);
	}
}

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

#define GET_PARAMCTRL_ID	(ID_PARAM_BEGIN + iCurve * g_iTotalParamNum * 7 + iParam * 7)

CXChartOptionPage::CXChartOptionPage(LPXUIOptionItem pOptionItem, QWidget *parent)
    : QFrame(parent)
    , m_pOptionItem(pOptionItem)
{
    initCtrl();
}


void CXChartOptionPage::initCtrl()
{
	//曲线设置
	m_mapCtrl[ID_GROUP_CURVE] = new CXEGroupBox(QString::fromStdWString(_T("曲线设置")), this);
	m_mapCtrl[ID_STATIC_CTRLNUM] = new CXEStatic(QString::fromStdWString(_T("控件数量")), m_mapCtrl[ID_GROUP_CURVE]);
	CXEComboBox* pComboCurveNum = new CXEComboBox(m_mapCtrl[ID_GROUP_CURVE]);
	for (int i = 0; i < TOTAL_CURVE_NUM; i++)
	{
		pComboCurveNum->AddItem(QString::number(i + 1));
	}
	connect(pComboCurveNum, &CXEComboBox::currentTextChanged, this, &CXChartOptionPage::onCurveNumChange);
	m_mapCtrl[ID_COMBO_CTRLNUM] = pComboCurveNum;
	CXETreeCtrl* pTreeCurve = new CXETreeCtrl(m_mapCtrl[ID_GROUP_CURVE]);
	pTreeCurve->setHeaderHidden(true);
	connect(pTreeCurve, &CXETreeCtrl::currentItemChanged, this, &CXChartOptionPage::onCurveItemChange);
	m_mapCtrl[ID_TREE_CURVE] = pTreeCurve;

	m_mapCtrl[ID_STATIC_NAME] = new CXEStatic(QString::fromStdWString(_T("曲线名称")), this);
	m_mapCtrl[ID_STATIC_PARAMNUM] = new CXEStatic(QString::fromStdWString(_T("参数数量")), this);

	for (int iCurve = 0; iCurve < TOTAL_CURVE_NUM; iCurve++)
	{
		//曲线名称
		m_mapCtrl[ID_NAME_BEGIN + iCurve] = new CXELineEdit(this);
		//参数数量
		CXEComboBox* pComboParamNum = new CXEComboBox(this);
		for (int i = 0; i < g_iTotalParamNum; i++)
		{
			pComboParamNum->AddItem(QString::number(i + 1));
		}
		connect(pComboParamNum, &CXEComboBox::currentTextChanged, this, &CXChartOptionPage::onParamNumChange);
		m_mapCtrl[ID_NUM_BEGIN + iCurve] = pComboParamNum;
		//参数区域
		QScrollArea* pScrollArea = new QScrollArea(this);
		pScrollArea->setStyleSheet("background-color:rgb(46,46,46);");
		QWidget* qScrollWidget = new QWidget(pScrollArea);
		pScrollArea->setWidget(qScrollWidget);
		m_mapCtrl[ID_SCROLL_BEGIN + iCurve] = pScrollArea;

		for (int iParam = 0; iParam < g_iTotalParamNum; iParam++)
		{
			m_mapCtrl[GET_PARAMCTRL_ID] = new CXEGroupBox(QString(QString::fromStdWString(_T("讲评参数%1"))).arg(QString::number(iParam + 1)), qScrollWidget);
			CXEComboBox* pComboParamType = new CXEComboBox(qScrollWidget);
			for (int i = 0; i < g_iTotalParamNum; i++)
			{
				pComboParamType->AddItem(QString::fromStdWString(g_sParamLabel[i]));
			}
			pComboParamType->setCurrentIndex(iParam);

			m_mapCtrl[GET_PARAMCTRL_ID + 1] = new CXEStatic(QString::fromStdWString(_T("参数选择")), qScrollWidget);
			m_mapCtrl[GET_PARAMCTRL_ID + 2] = pComboParamType;

			m_mapCtrl[GET_PARAMCTRL_ID + 3] = new CXEStatic(QString::fromStdWString(_T("参数名称")), qScrollWidget);
			m_mapCtrl[GET_PARAMCTRL_ID + 4] = new CXELineEdit(qScrollWidget);

			m_mapCtrl[GET_PARAMCTRL_ID + 5] = new CXEStatic(QString::fromStdWString(_T("显示颜色")), qScrollWidget);
			CXESingleColorCtrl* pColorCtrl = new CXESingleColorCtrl(qScrollWidget);
			pColorCtrl->SetVersion(XSINGLECOLORCTRL_VERSION_XPRI);
			pColorCtrl->SetAlpha(False);
			m_mapCtrl[GET_PARAMCTRL_ID + 6] = pColorCtrl;
		}
	}
}

#define STATIC_WIDTH 80
#define STATIC_HEIGHT 24
#define EDITT_WIDTH	120

void CXChartOptionPage::layout()
{
    QRect rtClient = rect();

	//曲线设置
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
	
	//曲线名称
	x = 200 + 20;
    y = 20;
    COL_ALIGN_CTRL(m_mapCtrl[ID_STATIC_NAME], x, y, STATIC_WIDTH, STATIC_HEIGHT);

	QModelIndex modeIndex = GET_TYPE_CTRL(CXETreeCtrl*, ID_TREE_CURVE)->currentIndex();
	int iIndex = modeIndex.row();
	x += STATIC_WIDTH + 10;
	for (int iCurve = 0; iCurve < TOTAL_CURVE_NUM; iCurve++)
	{
		COL_ALIGN_CTRL(m_mapCtrl[ID_NAME_BEGIN + iCurve], x, y, 120, STATIC_HEIGHT);
	}

	//参数数量
	x = 200 + 20;
	y += STATIC_HEIGHT + 10;
	COL_ALIGN_CTRL(m_mapCtrl[ID_STATIC_PARAMNUM], x, y, STATIC_WIDTH, STATIC_HEIGHT);

	x += STATIC_WIDTH + 10;
	for (int iCurve = 0; iCurve < TOTAL_CURVE_NUM; iCurve++)
	{		
		COL_ALIGN_CTRL(m_mapCtrl[ID_NUM_BEGIN + iCurve], x, y, 120, STATIC_HEIGHT);
	}


	//参数区
	int scrollY = y + STATIC_HEIGHT + 10;
	for (int iCurve = 0; iCurve < TOTAL_CURVE_NUM; iCurve++)
	{
		x = 200 + 10;
		y = scrollY;
		COL_ALIGN_CTRL(m_mapCtrl[ID_SCROLL_BEGIN + iCurve], x, y, 280, 400);
		COL_ALIGN_CTRL(GET_TYPE_CTRL(QScrollArea*, ID_SCROLL_BEGIN + iCurve)->widget(), x, y, 240, 400);
		x = 0; y = 0;
		for (int iParam = 0; iParam < g_iTotalParamNum; iParam++)
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
}

void CXChartOptionPage::changeEvent(QEvent *event)
{
    
}

void CXChartOptionPage::resizeEvent(QResizeEvent *event)
{
    layout();
}

void CXChartOptionPage::onCurveNumChange(const QString & str)
{
	int iCurveNum = GET_TYPE_CTRL(CXEComboBox*, ID_COMBO_CTRLNUM)->currentIndex() + 1;

	CXETreeCtrl* pTreeCurve = GET_TYPE_CTRL(CXETreeCtrl*, ID_TREE_CURVE);
	pTreeCurve->clear();
	for (int iCurve = 0; iCurve < iCurveNum; iCurve++)
	{
		QString sName =  GET_TYPE_CTRL(CXELineEdit*, ID_NAME_BEGIN + iCurve)->text();
		QTreeWidgetItem* pItem = new QTreeWidgetItem();
		pItem->setText(0, sName);
		pTreeCurve->addTopLevelItem(pItem);
		if (iCurve == 0)
			pTreeCurve->setCurrentItem(pItem);
	}
	showCtrl();
}

void CXChartOptionPage::onCurveItemChange(QTreeWidgetItem* current, QTreeWidgetItem *previous)
{
	showCtrl();
}

void CXChartOptionPage::onParamNumChange(const QString & str)
{
	showCtrl();
}

void CXChartOptionPage::showCtrl()
{
	QModelIndex modeIndex = GET_TYPE_CTRL(CXETreeCtrl*, ID_TREE_CURVE)->currentIndex();
	int iIndex = modeIndex.row();

	for (int iCurve = 0; iCurve < TOTAL_CURVE_NUM; iCurve++)
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

	for (int iCurve = 0; iCurve < TOTAL_CURVE_NUM; iCurve++)
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

	for (int iCurve = 0; iCurve < TOTAL_CURVE_NUM; iCurve++)
	{
		if (iCurve == iIndex)
		{
			int iHeight = 0;
			m_mapCtrl[ID_SCROLL_BEGIN + iCurve]->show();
			int iParamNum = GET_TYPE_CTRL(CXEComboBox*, ID_NUM_BEGIN + iCurve)->currentIndex() + 1;
			for (int iParam = 0; iParam < g_iTotalParamNum; iParam++)
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
			rect.setHeight(iHeight );
			widget->setGeometry(rect);
		}
		else
		{
			m_mapCtrl[ID_SCROLL_BEGIN + iCurve]->hide();
		}
	}
}

void CXChartOptionPage::getCurveConfig(CurveItemVector &vecCurveItem)
{

	vecCurveItem.clear();

	int iCurveNun = GET_TYPE_CTRL(CXEComboBox*, ID_COMBO_CTRLNUM)->currentIndex() + 1;
	for (int iCurve = 0; iCurve < iCurveNun; iCurve++)
	{
		std::shared_ptr <CCurveItem> pCurveItem(new CCurveItem);
		pCurveItem->sCurveName = GET_TYPE_CTRL(CXELineEdit*, ID_NAME_BEGIN + iCurve)->text().toStdWString();
		int iParamNum = GET_TYPE_CTRL(CXEComboBox*, ID_NUM_BEGIN + iCurve)->currentIndex() + 1;
		for (int iParam = 0; iParam < iParamNum; iParam++)
		{
			std::shared_ptr <CCurveItemParam> pParam(new CCurveItemParam);
			pParam->iTypeIndex = GET_TYPE_CTRL(CXEComboBox*, GET_PARAMCTRL_ID + 2)->currentIndex();
			pParam->sName = GET_TYPE_CTRL(CXELineEdit*, GET_PARAMCTRL_ID + 4)->text().toStdWString();
			pParam->color = GET_TYPE_CTRL(CXESingleColorCtrl*, GET_PARAMCTRL_ID + 6)->GetColor();
			pCurveItem->vecCurveParam.push_back(pParam);
		}
		vecCurveItem.push_back(pCurveItem);
	}
}


void CXChartOptionPage::setCurveConfig(CurveItemVector &vecCurveItem)
{
	GET_TYPE_CTRL(CXEComboBox*, ID_COMBO_CTRLNUM)->setCurrentIndex(vecCurveItem.size() - 1);

	CXETreeCtrl* pTreeCurve = GET_TYPE_CTRL(CXETreeCtrl*, ID_TREE_CURVE);
	pTreeCurve->clear();
	for (int iCurve = 0; iCurve < vecCurveItem.size(); iCurve++)
	{
		std::shared_ptr <CCurveItem> pCurveItem = vecCurveItem.at(iCurve);
		QTreeWidgetItem* pItem = new QTreeWidgetItem();
		pItem->setText(0, QString::fromStdWString(pCurveItem->sCurveName));
		pTreeCurve->addTopLevelItem(pItem);
		if (iCurve == 0)
		{
			pTreeCurve->setCurrentItem(pItem);
		}

		GET_TYPE_CTRL(CXELineEdit*, ID_NAME_BEGIN + iCurve)->setText(QString::fromStdWString(pCurveItem->sCurveName));
		GET_TYPE_CTRL(CXEComboBox*, ID_NUM_BEGIN + iCurve)->setCurrentIndex(pCurveItem->vecCurveParam.size() - 1);
		for (int iParam = 0; iParam < pCurveItem->vecCurveParam.size(); iParam++)
		{
			std::shared_ptr <CCurveItemParam> pParam = pCurveItem->vecCurveParam.at(iParam);
			GET_TYPE_CTRL(CXEComboBox*, GET_PARAMCTRL_ID + 2)->setCurrentIndex(pParam->iTypeIndex);
			GET_TYPE_CTRL(CXELineEdit*, GET_PARAMCTRL_ID + 4)->setText(QString::fromStdWString(pParam->sName));
			GET_TYPE_CTRL(CXESingleColorCtrl*, GET_PARAMCTRL_ID + 6)->SetColor(pParam->color, false);
		}
	}
	update();
}