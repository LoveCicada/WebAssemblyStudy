#pragma once

#include <QJsonObject>
#include <QJsonDocument>
#include <QApplication>
#include <QFile>
#include <QDialog>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QGroupBox>
#include <QSpinBox>
#include <QRadioButton>
#include <QTreeWidget>
#include "CChartView.h"
#include "CChartBaseData.h"

/*************************************************/

//get curveConfigure data
class CCurveConfigure
{
private:
	CCurveConfigure()
	{

	}


public:

	static CCurveConfigure* GetInstance()
	{
		static CCurveConfigure instance;
		return &instance;
	}

	bool LoadDataPath()
	{
		bool bRet = true;
		QString strAppPath = QApplication::applicationDirPath();
		QString fileName = "curveConfigure.json";
		filePath = strAppPath + "/data/" + fileName;

		QFile file(filePath);
		bool bExist = file.exists();
		if (!bExist)
		{
			file.open(QIODevice::ReadWrite);
			file.close();
		}

		return bRet;
	}

	bool TestDataPath()
	{
		bool bRet = true;
		QString strAppPath = QApplication::applicationDirPath();
		filePath = strAppPath + "/data/" + "curveConfigure2.json";
		return bRet;
	}

	bool ReadJson(const QJsonObject& jsonObject)
	{
		bool bRet = true;

		data.curvePluginVec.clear();
		data.pluginNumber = jsonObject.value("pluginNumber").toInt();
		data.currentPluginIndex = jsonObject.value("currentPluginIndex").toInt();
		data.paramNumber = jsonObject.value("paramNumber").toInt();

		const QJsonArray& jsonPluginArray = jsonObject.value("plugin").toArray();
		for (int i = 0; i < jsonPluginArray.size(); ++i)
		{
			const QJsonObject& jsonParamObject = jsonPluginArray.at(i).toObject();
			CCurvePlugin curvePlugin;
			curvePlugin.curveName = jsonParamObject.value("curveName").toString();
			curvePlugin.paramNum = jsonParamObject.value("paramNum").toInt();
			curvePlugin.currentParamIndex = jsonParamObject.value("currentParamIndex").toInt();

			const QJsonArray& jsonParamArray = jsonParamObject.value("paramVector").toArray();
			for (int j = 0; j < jsonParamArray.size(); ++j)
			{
				const QJsonObject& jsonParam = jsonParamArray.at(j).toObject();
				CParamGroup paramGroup;
				paramGroup.groupName = jsonParam.value("groupName").toString();
				paramGroup.paramChooseName = jsonParam.value("paramChooseName").toString();

				const QJsonArray& jsonParamVector = jsonParam.value("paramNameVector").toArray();
				for (int k = 0; k < jsonParamVector.size(); ++k)
				{
					const QJsonObject& jsonParamName = jsonParamVector.at(k).toObject();
					QString strName = jsonParamName.value("paramName").toString();
					paramGroup.paramNameVector.push_back(strName);
				}

				paramGroup.paramChooseIndex = jsonParam.value("paramChooseIndex").toInt();
				paramGroup.paramCurName = jsonParam.value("paramCurName").toString();
				QString colorStr = jsonParam.value("color").toString();
				paramGroup.color = QColor(colorStr);
				curvePlugin.paramVec.push_back(paramGroup);
			}

			data.curvePluginVec.push_back(curvePlugin);
		}

		return bRet;
	}

	CCurveConfigureData& GetData()
	{
		bool bRet = true;

		LoadDataPath();
		QFile file(filePath);
		bRet = file.open(QIODevice::ReadOnly);
		QByteArray byteData = file.readAll();
		file.close();

		if (!bRet)
			return data;

		QJsonDocument loadDoc(QJsonDocument::fromJson(byteData));
		const QJsonObject& jsonObject = loadDoc.object();
		ReadJson(jsonObject);

		return data;
	}

	bool WriteJson(QJsonObject& jsonObject)
	{
		bool bRet = true;

		//1
		int pluginNumber = data.pluginNumber;
		jsonObject.insert("pluginNumber", pluginNumber);
		int currentPluginIndex = data.currentPluginIndex;
		jsonObject.insert("currentPluginIndex", currentPluginIndex);
		int paramNumber = 0;

		//1.1 - plugin
		QJsonArray jsonPluginArray;
		CCurvePluginVec& curvePluginVec = data.curvePluginVec;
        for (int i = 0; i < (int)curvePluginVec.size(); ++i)
		{
			QJsonObject jsonParamObject;
			auto& pCCurvePlugin = curvePluginVec[i];
			jsonParamObject.insert("curveName", pCCurvePlugin.curveName);
			jsonParamObject.insert("paramNum", pCCurvePlugin.paramNum);
			jsonParamObject.insert("currentParamIndex", pCCurvePlugin.currentParamIndex);

			//1.1.1 - paramVector
			QJsonArray jsonParamArray;
			auto& paramVector = pCCurvePlugin.paramVec;
			for (int j = 0; j < paramVector.size(); ++j)
			{
				auto& pParam = paramVector[j];
				QJsonObject jsonParam;
				jsonParam.insert("groupName", pParam.groupName);
				jsonParam.insert("paramChooseName", pParam.paramChooseName);

				//1.1.1.1 - paramNameVector
				auto& paramNameVec = pParam.paramNameVector;
				paramNumber = paramNumber >= paramNameVec.size() ? paramNumber : paramNameVec.size();
				QJsonArray jsonParamVector;
				for (int k = 0; k < paramNameVec.size(); ++k)
				{
					auto& strName = paramNameVec[k];
					QJsonObject jsonParamName;
					jsonParamName.insert("paramName", strName);
					jsonParamVector.append(jsonParamName);
				}

				jsonParam.insert("paramNameVector", jsonParamVector);
				jsonParam.insert("paramChooseIndex", pParam.paramChooseIndex);
				jsonParam.insert("paramCurName", pParam.paramCurName);
				QString colorStr = pParam.color.name();
				jsonParam.insert("color", colorStr);
				jsonParamArray.append(jsonParam);
			}
			
			jsonParamObject.insert("paramVector", jsonParamArray);
			jsonPluginArray.append(jsonParamObject);
			
		}

		jsonObject.insert("plugin", jsonPluginArray);
		jsonObject.insert("paramNumber", paramNumber);

		return bRet;
	}


	bool SetData(CCurveConfigureData& data)
	{
		bool bRet = true;

		this->data = data;
		//TestDataPath();
		QFile file(filePath);
		bRet = file.open(QIODevice::ReadWrite | QIODevice::Truncate);

		QJsonObject jsonObject;
		WriteJson(jsonObject);

		QJsonDocument jsonDoc(jsonObject);
		file.write(jsonDoc.toJson());
		file.close();


		return bRet;
	}


private:
	QString filePath;
	CCurveConfigureData data;

};




























/*************************************************/







//rotate
class CChartRoatePage : public QDialog
{
	Q_OBJECT
public:
	CChartRoatePage(QWidget* parent = nullptr);
	~CChartRoatePage();

	void initCtrl();
	void initData();
	void setData(const CCRoateData& data);
	CCRoateData getData();
	void setChartWidget(CChartView* pChartWidget);
protected:
	void layout();

public slots:
	void changeParam(int index);
	void changeOriention(int index);
	void coordinateSelect();
	void acceptBtnHandle();
	void cancelBtnHandle();
	void applyBtnHandle();

private:

    QLabel* m_pParamChooseLabel;
    QComboBox* m_pParamCombo;

    QLabel* m_pRotateChooseLabel;
    QLabel* m_pXlabel;
    QLineEdit* m_pXEdit;
    QLabel* m_pYlabel;
    QLineEdit* m_pYEdit;
	//坐标选取
    QPushButton* m_pCoordinateSelectBtn;

    QLabel* m_pRotateOrientationLabel;
    QComboBox* m_pOrientionCombo;

    QLabel* m_pRotateAngleLabel;
    QLineEdit* m_pAngleEdit;
    QLabel* m_pAngleLabel;
	QWidget* m_pWidget;

    QPushButton* m_pYesBtn;
    QPushButton* m_pNoBtn;
    QPushButton* m_pApplyBtn;

	//data
	CCRoateData m_CCRoateData;
	CChartView* m_pChartWidget;
};



//trans 
class CChartTransPage : public QDialog
{
	Q_OBJECT
public:
	CChartTransPage(QWidget* parent = nullptr);
	~CChartTransPage();

	void initCtrl();
	void initData();
	void setData(const CCTransData& data);
	CCTransData getData();
	void setChartWidget(CChartView* pChartWidget);
	
protected:
	void layout();

public slots:
	void changeParam(int index);
	void changeOriention(int index);
	void coordinateSelect();
	void acceptBtnHandle();
	void cancelBtnHandle();
	void applyBtnHandle();
private:

    QLabel*     m_pParamChooseLabel;
    QComboBox*  m_pParamCombo;

    QLabel*     m_pTransChooseLabel;
    QLabel*     m_pXlabel;
    QLineEdit*  m_pXEdit;
	//坐标选取
    QPushButton* m_pCoordinateSelectBtn;

    QLabel*     m_pTransOrientationLabel;
    QComboBox*  m_pOrientionCombo;

    QLabel*     m_pTimeRangeLabel;
    QLineEdit*  m_pHourEdit;
    QLabel*     m_pHourLabel;
    QLineEdit*  m_pMinEdit;
    QLabel*     m_pMinLabel;
    QLineEdit*  m_pSecEdit;
    QLabel*     m_pSecLabel;
    QLineEdit*  m_pMsecEdit;
    QLabel*     m_pMsecLabel;

    QWidget*    m_pWidget;

    QPushButton* m_pYesBtn;
    QPushButton* m_pNoBtn;
    QPushButton* m_pApplyBtn;

	//data
	CCTransData m_CCTransData;
	CChartView* m_pChartWidget;
};





//move




//set




//新曲线控件设置中心
class CXChartOptionPageEX : public QDialog
{
	Q_OBJECT

public:
	CXChartOptionPageEX(QWidget* parent = nullptr);

	CXChartOptionPageEX(FlightItemDataVector& fileList, QWidget* parent = nullptr);

public:
	bool setTotalFileList(FlightItemDataVector& fileList);
	void init();
	void initCtrl();
	void getCurveConfig(CCurveConfigureData& curveConfigData);
	void setCurveConfig(CCurveConfigureData& curveConfigData);
	void setFileList(FlightItemDataVector& fileList);
	void initParamIndexMap();
	void setChartWidget(CChartView* pChartWidget);
	//获取不同曲线控件当前所选属性
	void getCurveItemVec();
	void updateChartView();
	void initConfigureData();
	void initChartPageData();


	//check default config data whether valid, if not than create valid default data
	bool checkConfigDataValid(CCurveConfigureData& flightConfData);
	//generate configure data by flight data
	bool genCurveConfigDataByFlighData(const FlightItemDataVector& flightList, CCurveConfigureData& curveConfigData);
	//compare flight conf data to configure data, and change configure data
	bool compareFlightConfToConfData(CCurveConfigureData& flightConfData, CCurveConfigureData& confFigData);
	bool saveCurveConfigData();

protected:
	void         layout();
public slots:
	void defaultBtnHandle();
	void acceptBtnHandle();
	void cancelBtnHandle();
	void applyBtnHandle();
	void updateEditText(QString str);

protected:
	void changeEvent(QEvent* event);
	void resizeEvent(QResizeEvent* event);
	void onCurveNumChange(const QString& str);
	void onCurveItemChange(QTreeWidgetItem* current, QTreeWidgetItem* previous);
	void onParamNumChange(const QString& str);
	void showCtrl();

private:

	std::map<int, QWidget*>   m_mapCtrl;

    QPushButton* m_pDefaultBtn;
    QPushButton* m_pYesBtn;
    QPushButton* m_pNoBtn;
    QPushButton* m_pApplyBtn;

private:
	//data
	//曲线控件数量
	int m_CurveNum;
	//曲线参数数量
	int m_ParamNum;

	//all param data
	FlightItemDataVector m_flightList;

	//curve chart (不同的曲线视图，例如曲线控件1/2/3...)
	CurveItemVectorEX m_CurveItemVectorEX;
	CChartView* m_pChartWidget;

	int m_iTotalParamNum;
	ParamIndexMap m_paramIndexMap;

	CCurveConfigureData m_CurveConfigData;
	CCurveConfigureData m_CurveConfigFlight;


};
