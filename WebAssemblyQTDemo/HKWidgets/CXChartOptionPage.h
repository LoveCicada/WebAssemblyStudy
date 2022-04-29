#ifndef CXECHARTOPTIONPAGE_H
#define CXECHARTOPTIONPAGE_H

#include <QFrame>
#include <QLabel>
#include <QGroupBox>
#include <QSpinBox>
#include <QRadioButton>
#include <QTreeWidget>
#include "XFlightData.h"

struct CCurveItemParam
{
	int iTypeIndex;
	String sName;
	UInt32 color;
};
typedef std::vector<std::shared_ptr<CCurveItemParam>> ItemParamVector;

typedef struct CCurveItem
{
	String	sCurveName;
	ItemParamVector vecCurveParam;
};
typedef std::vector<std::shared_ptr<CCurveItem>> CurveItemVector;



class CXChartOptionPage : public QFrame
{
    Q_OBJECT
public:
    explicit CXChartOptionPage(LPXUIOptionItem pOptionItem, QWidget *parent = nullptr);

    void initCtrl();
    void getCurveConfig(CurveItemVector &vecCurveItem);
    void setCurveConfig(CurveItemVector &vecCurveItem);

protected:
    void         layout();

protected:
    void changeEvent(QEvent *event);
    void resizeEvent(QResizeEvent *event);
	void onCurveNumChange(const QString & str);
	void onCurveItemChange(QTreeWidgetItem* current, QTreeWidgetItem *previous);
	void onParamNumChange(const QString & str);
	void showCtrl();

private:

	std::map<int, QWidget*>   m_mapCtrl;

private:
    LPXUIOptionItem m_pOptionItem;
};

class CXChartViewWnd;
struct CXChartOptionItem : public XUIOptionItem
{
    CXChartOptionItem(IXUIOptionValueFactory* pValFact, CXChartViewWnd* pWnd, std::vector<String> vecLabel);
    virtual ~CXChartOptionItem();

    virtual QWidget*   CreateOptionsPage(QWidget* pParent, const QRect& rtWnd);
    virtual void    DestoryOptionsPage(QWidget* pWnd);
    virtual void    Apply();
    virtual void    SetDefault();
	CurveItemVector&	GetCurveParam();

private:
	
	void setOptionData();
	void getOptionData();

	CurveItemVector m_vecCurveItem;

    CXChartOptionPage*   m_pOption;
    IXUIOptionValueFactory*    m_pValFact;
	CXChartViewWnd* 		m_pChartWnd;

	std::vector<String> m_vecLabel;
};

#endif // CXECHARTOPTIONPAGE_H
