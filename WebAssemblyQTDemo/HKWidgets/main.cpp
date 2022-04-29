
#include "CXChartViewWnd.h"
#include "XFlightData.h"
//#include "HKExportInterface.h"
#include <QApplication>


#include <iostream>
#include <emscripten/bind.h>

using namespace std;
using namespace emscripten;



CXChartViewWnd* g_chartViewWnd;






#if 1

ChartPropertyVec generateChartProerty()
{
    CChartViewProperty chartProHeight("height", 2, QColor(Qt::darkYellow));
    CChartViewProperty chartProSpeed("speed", 2, QColor(Qt::darkMagenta));
    CChartViewProperty chartProLongitude("longitude", 2, QColor(Qt::darkCyan));
    ChartPropertyVec chartProVec;
    chartProVec.push_back(chartProHeight);
    chartProVec.push_back(chartProSpeed);
    chartProVec.push_back(chartProLongitude);

    return chartProVec;
}


FlightItemDataVector generateData()
{
    FlightItemDataVector data;

#if 1

    int numSample = 100 * 1;

    //test flightdata
    std::shared_ptr<CFlightData> pFlightData(new CFlightData);
    //height
    CFlightItemData stuItemdata1;
    stuItemdata1.strLabel = QStringLiteral("height");
    QDateTime curTime = QDateTime::currentDateTime();
    for (size_t i = 0; i < numSample; i++)
    {
        CParameterData stuItem;
        int nRandom = qrand() % (100 - 1);
        nRandom = 1 + nRandom;
        stuItem.dValue = nRandom;
        stuItem.time = curTime.addSecs(i);
        //stuItem.timein = 0;
        //stuItem.timeout = 1000;
        stuItemdata1.vecParameterData.push_back(stuItem);
    }
    //speed
    CFlightItemData stuItemdata2;
    stuItemdata2.strLabel = QStringLiteral("speed");
    for (size_t i = 0; i < numSample; i++)
    {
        CParameterData stuItem;
        int nRandom = qrand() % (100 - 1);
        nRandom = 1 + nRandom;
        stuItem.dValue = nRandom;
        stuItem.time = curTime.addSecs(i);
        //stuItem.timein = 0;
        //stuItem.timeout = 1000;
        stuItemdata2.vecParameterData.push_back(stuItem);
    }
    //precision
    CFlightItemData stuItemdata3;
    stuItemdata3.strLabel = QStringLiteral("precision");
    for (size_t i = 0; i < numSample; i++)
    {
        CParameterData stuItem;
        int nRandom = qrand() % (100 - 1);
        nRandom = 1 + nRandom;
        stuItem.dValue = nRandom;
        stuItem.time = curTime.addSecs(i);
        //stuItem.timein = 0;
        //stuItem.timeout = 1000;
        stuItemdata3.vecParameterData.push_back(stuItem);
    }

    data.push_back(stuItemdata1);
    data.push_back(stuItemdata2);
    data.push_back(stuItemdata3);

#endif // 0


    return data;
}

#endif


//test hello
void setData()
{
    std::cout<<"hello, I am test"<<endl;
    //update data
    FlightItemDataVector data;
    data = generateData();
    g_chartViewWnd->setFileList(data);
    std::cout<<"update data finish"<<endl;

}

EMSCRIPTEN_BINDINGS(module7) {
    emscripten::function("setData", &setData);

}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

#if 0

    Widget w;
    w.show();

#else

    CXChartViewWnd chartViewWnd;
    g_chartViewWnd = &chartViewWnd;
    FlightItemDataVector data;
    data = generateData();
    chartViewWnd.setFileList(data);
    chartViewWnd.show();
    chartViewWnd.showMaximized();


#endif




    return a.exec();
}
