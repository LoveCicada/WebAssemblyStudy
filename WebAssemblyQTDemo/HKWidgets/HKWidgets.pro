QT       += core gui printsupport widgets

include(HKChartView.pri)

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


TRANSLATIONS += \
    HKWidgets_zh_CN.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    HKChartRes.qrc


INCLUDEPATH +=  C:/Qt/Qt5.15.1/5.15.1/emsdknm/emsdk  \
                C:/Qt/Qt5.15.1/5.15.1/emsdknm/emsdk/upstream    \
                C:/Qt/Qt5.15.1/5.15.1/emsdknm/emsdk/upstream/bin    \
                C:/Qt/Qt5.15.1/5.15.1/emsdknm/emsdk/upstream/include    \
                C:/Qt/Qt5.15.1/5.15.1/emsdknm/emsdk/upstream/emscripten \
                C:/Qt/Qt5.15.1/5.15.1/emsdknm/emsdk/upstream/emscripten/system  \
                C:/Qt/Qt5.15.1/5.15.1/emsdknm/emsdk/upstream/emscripten/system/bin  \
                C:/Qt/Qt5.15.1/5.15.1/emsdknm/emsdk/upstream/emscripten/system/include

