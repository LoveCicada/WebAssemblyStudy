### HK
HK web widgets

1. configure QT environment
```
advice：install QT, emsdk, create project,output project at same path.
eg: C:/
```

2. QT QDialog exec can not use
```
change modal and show dialog
```

3. emsdk dev path
```
add path to environment path
```

```
C:\Qt\Qt5.15.1\5.15.1\emsdknm\emsdk;
C:\Qt\Qt5.15.1\5.15.1\emsdknm\emsdk\upstream;
C:\Qt\Qt5.15.1\5.15.1\emsdknm\emsdk\upstream\bin;
C:\Qt\Qt5.15.1\5.15.1\emsdknm\emsdk\upstream\include;
C:\Qt\Qt5.15.1\5.15.1\emsdknm\emsdk\upstream\emscripten;
C:\Qt\Qt5.15.1\5.15.1\emsdknm\emsdk\upstream\emscripten\system;
C:\Qt\Qt5.15.1\5.15.1\emsdknm\emsdk\upstream\emscripten\system\bin;
C:\Qt\Qt5.15.1\5.15.1\emsdknm\emsdk\upstream\emscripten\system\include;
C:\Qt\Qt5.15.1\5.15.1\emsdknm\emsdk\upstream\emscripten\system\lib;
```
### use emskd
```
#include <emscripten/bind.h>
using namespace emscripten;

emscripten::function("func", &func);
```

- `运行`
```
进入build-HKWidgets-Qt_5_15_1_WebAssembly-Debug文件夹内
用vscode打开HKWidgets.html文件, 选中右下角的Go to live server选项
在浏览器中打开, 会显示一个QT的曲线窗口
```