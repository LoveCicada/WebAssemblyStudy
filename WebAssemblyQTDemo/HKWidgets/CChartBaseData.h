#pragma once

#include <vector>
#include <map>
#include <QString>
#include <QColor>
#include <QPoint>
#include <QDateTime>

struct CCurveItemParamEX
{
	int iTypeIndex;
	QString sName;
	QColor color;
};
typedef std::vector<std::shared_ptr<CCurveItemParamEX>> ItemParamVectorEX;

struct CCurveItemEX
{
	QString	sCurveName;
	ItemParamVectorEX vecCurveParam;
};
typedef std::vector<std::shared_ptr<CCurveItemEX>> CurveItemVectorEX;

typedef std::map<int, QString> ParamIndexMap;

/*-----------------------------------------------------------------*/
struct CParamGroup 
{
	QString groupName;
	QString paramChooseName;
	std::vector<QString> paramNameVector;
	int paramChooseIndex;
	QString paramCurName;
	QColor color;
};

typedef std::vector<CParamGroup> CParamGroupVec;

struct CCurvePlugin 
{
	QString curveName;
	int paramNum;
	int currentParamIndex;	//current param number index
	CParamGroupVec paramVec;
};

typedef std::vector<CCurvePlugin> CCurvePluginVec;

struct CCurveConfigureData
{
	int pluginNumber;
	int currentPluginIndex;
	int paramNumber;
	CCurvePluginVec curvePluginVec;
};

/*-----------------------------------------------------------------*/

struct CCRoateData
{
	CCRoateData()
	{
		index = 0;
		param = "";
		pt.setX(0);
		pt.setY(0);
		orientation = true;
		angle = 0.0;
	}

	int		index;			//��������
	QString param;			//������
	QPoint	pt;				//��ת��
	bool	orientation;	//��ת���� ˳ʱ�� true����ʱ�� false
	double	angle;			//��ת�Ƕ�

};

//����ƽ�ƻ�������
struct CCTransData
{
	CCTransData()
	{
		index = 0;
		param = "";
		pt.setX(0);
		pt.setY(0);
		orientation = true;
		time = QDateTime::currentDateTime();
	}

	int			index;			//��������
	QString		param;			//������
	QPoint		pt;				//ƽ�Ƶ�
	bool		orientation;	//��ת���� ���� true������ false	
	QDateTime	time;			//ʱ����
};
