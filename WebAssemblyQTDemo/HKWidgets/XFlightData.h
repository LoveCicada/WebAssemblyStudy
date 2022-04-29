#pragma once

#include <QtCore/QUuid>
#include <QtCore/QDate>
#include <vector>
#include <map>
#include <memory>
#include <QDateTime>

//���У�����
enum EFlightState
{
	EFlight_Sky,
	EFlight_Ground,
};

//����״̬
enum ETaskState
{
	ET_COMMENT,		//������
	ET_COMMENTING,	//���ڽ���
	ET_COMMENTED,	//�ѽ���
};

enum EFlightDataType
{
	FLIGHT_UNKNOW,
	FLIGHT_MEDIAINFO,
	FLIGHT_PROJECTDATA,
	FLIGHT_3DOBJECT,
	FLIGHT_TASKINFO,
};

enum EChannelType
{
	CHANNELTYPE_C1,
	CHANNELTYPE_C2,
	CHANNELTYPE_C3,
	CHANNELTYPE_C4,
	CHANNELTYPE_C5,
	CHANNELTYPE_C6,
	CHANNELTYPE_C7,
	CHANNELTYPE_C8,
};


struct CDataBase
{
	CDataBase()
	{
        timein = QDateTime::currentDateTime();
        timeout = QDateTime::currentDateTime();
		datatype = FLIGHT_UNKNOW;
		chantype = CHANNELTYPE_C1;
	}
	QUuid idData;
    QDateTime timein;
    QDateTime timeout;
	EFlightDataType  datatype;
	EChannelType chantype;
};

struct CFlightBaseData
{

};


//1. ��¼��Ϣ
struct CLoginInfo : public CFlightBaseData
{
	QString strUser;
	QString strPw;

	QString accessToken;
	QString tokenType;
	QString refreshToken;
	int		expiresIn;
	QString scope;

	QString error;
	QString error_description;
};

//2. ��ѯ��������
struct CFlightDateData : public CFlightBaseData
{
	//�����������
	std::map<QString, bool> groundDate;
	//���з�������
	std::map<QString, bool> flyDate;
	//��������
	std::map<QString, bool> planDate;

	void Clear()
	{
		groundDate.clear();
		flyDate.clear();
		planDate.clear();
	}
};


//3. ��ѯ������־
struct CFlightRecordInfoData : public CFlightBaseData
{
	QString id;
	QString gmtCreate;
	QString gmtModified;
	EFlightState testType;
	QString productCode;
	QString batchNo;
	QString planNoList;
	QString flayplanName;
	int startTime;
	int endTime;
	int flyTime;
	QString flyPlace;
	int engStartTime;
	int engEndTime;
	QString classificat;
	QString upDown;
	QString high;
	QString angle;
	double bigSpeed;
	double miniSpeed;
	QString normalOverload;
	QString fault;
	QString staff;
	QString listNo;
	QString effect;
	QString config;
	QString dayPlan;
	QString flyUpDownId;
	QString mnum;
};

typedef std::vector<CFlightRecordInfoData> FlightRecordDataList;


struct CFlightTaskFile
{
	QString id;
	QString gmtCreate;
	QString gmtModified;
	QString dataType;
	QString dataFile;
	QString confFile;
	int dataSize;
	int confSize;
	QString format;
	int state;
	QString classification;
	//�Ƿ񱾵�
	int local;
	QString dataAddr;
	QString confAddr;
	QString planId;
};

typedef std::vector<CFlightTaskFile> FlightTaskFileList;

//4. ������־����
struct CFlightTaskInfoData : public CFlightBaseData
{
	QString id;
	QString gmtCreate;
	QString gmtModified;
	EFlightState testType;
	QString productCode;
	QString batchNo;
	QString planNoList;
	QString flayplanName;
	int startTime;
	int endTime;
	int flyTime;
	QString flyPlace;
	int engStartTime;
	int engEndTime;
	QString classificat;
	QString upDown;
	QString high;
	QString angle;
	double bigSpeed;
	double miniSpeed;
	QString normalOverload;
	QString fault;
	QString staff;
	QString listNo;
	QString effect;
	QString config;
	QString dayPlan;
	QString flyUpDownId;
	QString mnum;
	FlightTaskFileList fileList;
};

typedef std::vector<CFlightTaskInfoData> FlightTaskInfoDataList;

//5. ��ѯ�ļ������ݷ�����Ϣ
struct CFlightGroupInfoData : public CFlightBaseData
{
	QString id;
	QString gmtCreate;
	QString gmtModified;
	int	isDelete;
	QString groupName;
	QString major;
	QString samplingRate;
	QString parametersTotal;
	QString subscribeUnit;
	QString productCode;
	QString batchNo;
	QString planNoList;
};

typedef std::vector<CFlightGroupInfoData> FlightGroupInfoDataList;


struct CFlightParamGroupInfoPara
{
	QString id;
	QString gmtCreate;
	QString gmtModified;
	int isDelete;
	QString productCode;
	QString batchNo;
	QString planNoList;
	QString parameterName;
	QString chineseName;
	QString parametersSymbol;
	QString parameters;
	QString unitSymbols;
	QString precisions;
	int samplingRate;
	QString parameterType;
	QString parametersSource;
	QString note;
};

typedef std::vector<CFlightParamGroupInfoPara> FlightParamGroupInfoParaList;

struct CFlightParamGroupInfoGroup
{
	QString id;
	QString gmtCreate;
	QString gmtModified;
	int isDelete;
	QString groupName;
	QString major;
	QString samplingRate;
	QString parametersTotal;
	QString subscribeUnit;
	QString productCode;
	QString batchNo;
	QString planNoList;
};

typedef std::vector<CFlightParamGroupInfoGroup> FlightParamGroupInfoGroupList;


//6. ��ѯ������������
struct CFlightParamGroupInfoData : public CFlightBaseData
{
	//para
	FlightParamGroupInfoParaList	paraList;
	//group
	CFlightParamGroupInfoGroup		group;
};

typedef std::vector<CFlightParamGroupInfoData> FlightParamGroupInfoDataList;

struct CFlightProjectInfoBaseData
{
	QDateTime dateTime;
	std::map<QString, double> valueMap;
};

typedef std::vector<CFlightProjectInfoBaseData> FlightProjectInfoBaseDataList;
typedef std::map<QString, CFlightProjectInfoBaseData> InfoBaseDataMap;

//7. ��ѯ�������ݣ�ʱ�����ݿ⣩
struct CFlightProjectInfoData : public CFlightBaseData
{
	FlightProjectInfoBaseDataList baseDataList;
};

typedef std::vector<CFlightProjectInfoData> FlightProjectInfoDataList;


//8. ��ѯ�������������Сʱ�䣨ʱ�����ݿ⣩
struct CFlightProjectTimeData : public CFlightBaseData
{
	QString Min_time;
	QString Max_time;
};

typedef std::vector<CFlightProjectTimeData> CFlightProjectTimeDataList;




//������������
struct CFlightTaskInfo
{
	//���� ���� �Էɵص� ����� ���ʱ�� ��½ʱ�� ����״̬
	QString id;//������־ID
	QString model;
	QString batch;
	QString flyAddress;
	QString upDownId;
	QString	takeOffTime;
	QString	landTime;
	QString taskState;
	EFlightState flightState;
};

typedef std::vector<CFlightTaskInfo> CTaskInfoList;

//����������������
struct CTaskInfoData
{
	CTaskInfoList taskInfoList;
};

struct CDataGroupInfo
{
	std::vector<QString> strChooseFile;
	std::vector<QString> strGroupInfo;
};
typedef std::vector<CDataGroupInfo> CDataGroupInfoList;


//�ļ���������
struct CDataFileInfo
{
	CDataGroupInfoList vecDataGroup;
};
//typedef std::vector<CDataFileInfo> CDataFileInfoList;

struct CFileInfo
{
	QString strFullPathFileName;
	int iFileIn;
	int iFileOut;
};

typedef std::vector<CFileInfo> CFileList;


//��Ƶ����
struct CVideoData : public CDataBase
{
	CFileList vecFileInfo;
	CVideoData()
	{
		vecFileInfo.clear();
	}
};

//Flight Project data
struct CParameterData
{
	CParameterData() 
	{
		time = QDateTime::currentDateTime();
		dValue = 0;
	};
	CParameterData(const CParameterData& src) { *this = src; }
	CParameterData* Clone()
	{
		CParameterData* t_pNewObj = new CParameterData;
		*t_pNewObj = *this;
		return t_pNewObj;
	}
	/*CParameterData& operator =(const CParameterData& src)
	{
		timein = src.timein;
		timeout = src.timeout;
		dValue = src.dValue;
		return *this;
	}*/
	QDateTime time;
    double dValue;
};

typedef std::vector<CParameterData> ParameterDataVector;

struct CFlightItemData
{
	CFlightItemData() {};
	CFlightItemData(const CFlightItemData& src) { *this = src; }
	CFlightItemData* Clone()
	{
		CFlightItemData* t_pNewObj = new CFlightItemData;
		*t_pNewObj = *this;
		return t_pNewObj;
	}
	/*CFlightItemData& operator =(const CFlightItemData& src)
	{
		strLabel = src.strLabel;
		strCategory = src.strCategory;
		return *this;
	}*/
	QString strLabel;
	QString strCategory;
	ParameterDataVector vecParameterData;
};

typedef std::vector<CFlightItemData> FlightItemDataVector;
typedef std::map<QString, CFlightItemData> FlightItemDataMap;

//���߿ؼ�����
struct CFlightData : public CDataBase
{
	FlightItemDataVector vecFlightData;
};


typedef std::map<QUuid, std::shared_ptr<CDataBase>>			MapDataIDToFlightData;
typedef std::vector<std::shared_ptr<CDataBase>>				DataInfoList;
typedef std::vector<std::shared_ptr<CVideoData>>			VideoInfoList;
typedef std::vector<std::shared_ptr<CFlightData>>			FlightDataList;
typedef std::vector<std::shared_ptr<CDataFileInfo>>			DataFileInfoDataList;
typedef std::map<QDate, std::shared_ptr<CTaskInfoData>>		TaskInfoMap;
typedef std::shared_ptr<CTaskInfoList> TaskInfoList;



class CFlightDataChannel
{
public:
	MapDataIDToFlightData m_mapIdtoFlightData;
	EChannelType eType;
};

typedef std::map<EChannelType, std::shared_ptr<CFlightDataChannel>> MapFlightData;

//bind
struct CBindDataItem
{
	QString strLabel;
	uint        iIndex;
};

typedef std::vector<CBindDataItem>  BindDataVector;
typedef std::vector<uint> BindDataIndexMap;

