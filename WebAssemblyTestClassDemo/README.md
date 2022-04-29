#### WebAssembly 开发介绍

- `安装emcc编译器开发环境`
```
emcc
```

- `编译`
```
运行脚本
emcc --bind -o .\build\quick_example.js .\src\quick_example.cpp
```

- `运行`
```
进入build文件夹目录内, 用vscode打开quick_example.html
点击右下角的Go to live server在浏览器中打开
F12查看控制台输出
```