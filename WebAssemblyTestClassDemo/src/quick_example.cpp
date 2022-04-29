// quick_example.cpp
#include <iostream>
#include <emscripten/bind.h>

using namespace std;
using namespace emscripten;


typedef std::vector<double> DoubleVec;

DoubleVec getVectorData () {
  DoubleVec v;
  int num = 10;
  double dValue = 0.5;
  for(int i=0;i<num;++i)
  {
    dValue = dValue + i;
    v.push_back(dValue);
  }
  return v;
}

bool setVectorData(DoubleVec& doubleVec)
{
  bool bRet = true;
  DoubleVec::iterator itor = doubleVec.begin();
  for(; itor!=doubleVec.end();++itor)
  {
    std::cout << (*itor) << std::endl;
  }

  return bRet;
}

std::map<int, std::string> returnMapData () {
  std::map<int, std::string> m;
  m.insert(std::pair<int, std::string>(10, "This is a string."));
  return m;
}


EMSCRIPTEN_BINDINGS(module1) {
    emscripten::function("getVectorData", &getVectorData);
    emscripten::function("setVectorData", &setVectorData);
    emscripten::function("returnMapData", &returnMapData);

    register_vector<double>("DoubleVec");
    register_map<int, std::string>("map<int, string>");
}


//2. export class

class CChartViewProperty
{
public:
	CChartViewProperty()
	{
		
	}

	CChartViewProperty(std::string _strTitle, double _dWidth, int _color)
    :strTitle(_strTitle),dWidth(_dWidth),color(_color)
	{
		
	}

  //Get Set函数
  std::string getValueTitle() const{
    return strTitle;
  }
  void setValueTitle(std::string val){
    strTitle=val;
  }
  int getValuecolor() const{
    return color;
  }
  void setValuecolor(int _color){
    color=_color;
  }

  double getValueWidth() const{
    return dWidth;
  }
  void setValueWidth(double _dWidth){
    dWidth=_dWidth;
  }

	std::string strTitle;//标题
	double  dWidth;//线宽
	int  color; //颜色
};

typedef std::vector<CChartViewProperty> ChartViewPropertyVec;
typedef std::vector<CChartViewProperty>::iterator ChartViewPropertyVecItor;

//export calss
//使用EMSCRIPTEN_BINDINGS宏参数进行函数绑定
//把c++的函数绑定到js环境中 
EMSCRIPTEN_BINDINGS(module3){
    //绑定类 
    class_<CChartViewProperty>("CChartViewProperty")
    //绑定构造函数 
    .constructor<std::string, double, int>()
    //绑定私有成员变量的setter和getter方法
    .property("strTitle",&CChartViewProperty::getValueTitle,&CChartViewProperty::setValueTitle)
    .property("dWidth",&CChartViewProperty::getValueWidth,&CChartViewProperty::setValueWidth)
    .property("color",&CChartViewProperty::getValuecolor,&CChartViewProperty::setValuecolor); 

    register_vector<CChartViewProperty>("ChartViewPropertyVec");
}


//Flight Project data
struct CParameterData
{
	CParameterData(int _time = 0,double _dVaule = 0) 
	{
		time = _time;
		dValue = _dVaule;
	};

  int getTime() const{
    return time;
  }
  void setTime(int _time){
    time=_time;
  }

  double getValue() const{
    return dValue;
  }
  void setValue(double _dValue){
    dValue=_dValue;
  }

	int time;
	double dValue;
};

typedef std::vector<CParameterData> ParameterDataVector;

EMSCRIPTEN_BINDINGS(module4){
    //绑定类 
    class_<CParameterData>("CParameterData")
    //绑定构造函数 
    .constructor<int, double>()
    //绑定私有成员变量的setter和getter方法
    .property("time",&CParameterData::getTime,&CParameterData::setTime)
    .property("dValue",&CParameterData::getValue,&CParameterData::setValue);
    register_vector<CParameterData>("ParameterDataVector");
}


struct CFlightItemData
{
	CFlightItemData() {}
	CFlightItemData(const CFlightItemData& src) { *this = src; }
	CFlightItemData* Clone()
	{
		CFlightItemData* t_pNewObj = new CFlightItemData;
		*t_pNewObj = *this;
		return t_pNewObj;
	}

	std::string strLabel;
	std::string strCategory;
	ParameterDataVector vecParameterData;
};

typedef std::vector<CFlightItemData> FlightItemDataVector;
typedef std::vector<CFlightItemData>::iterator FlightItemDataItor;
typedef std::map<std::string, CFlightItemData> FlightItemDataMap;

EMSCRIPTEN_BINDINGS(module5){
    //绑定类 
    class_<CFlightItemData>("CFlightItemData")
    //绑定构造函数 
    .constructor<>();
    //绑定私有成员变量的setter和getter方法
    register_vector<CFlightItemData>("FlightItemDataVector");
    register_map<std::string, CFlightItemData>("FlightItemDataMap");
}

//global variable
ChartViewPropertyVec g_PropertyVec;
FlightItemDataVector g_FlightDataVector;

bool setChartData(ChartViewPropertyVec& property, FlightItemDataVector& flightDataVec)
{
  bool bRet = true;
  ChartViewPropertyVecItor propertyItor = property.begin();
  for(;propertyItor!=property.end();++propertyItor)
  {
    std::cout<<propertyItor->strTitle<<std::endl;
    std::cout<<propertyItor->dWidth<<std::endl;
    std::cout<<propertyItor->color<<std::endl;
  }

  FlightItemDataItor flightItemItor = flightDataVec.begin();
  for(;flightItemItor!=flightDataVec.end();++flightItemItor)
  {
    std::cout<<flightItemItor->strLabel<<std::endl;
    std::cout<<flightItemItor->strCategory<<std::endl;
  }


  return bRet;
}

EMSCRIPTEN_BINDINGS(module6) {
    emscripten::function("setChartData", &setChartData);

}