# rlsw - Windows 分辨率切换工具
一个轻量级的 Windows 命令行工具，用于快速切换显示器分辨率和刷新率。

## 功能特点
- 🚀 快速切换显示器设置
- 💻 支持自定义分辨率、刷新率
- 🔧 简单的命令行接口
- 📝 设置持久化（更新注册表）

## 使用方法
### 基本语法
```cmd
rlsw.exe [width] [height] [refresh_rate]
```

### 参数说明
|参数|	说明|	示例|
|---|---|---|
|width|	水平像素数|	1920|
|height|	垂直像素数|	1080|
|refresh_rate|	刷新率| (Hz)	60|

### 示例
将显示器设置为 1920x1080 分辨率，60Hz 刷新率：

```cmd
rlsw.exe 1920 1080 60
```

### 返回值
|返回值|	说明|
|---|---|
|0|	成功更改设置|
|1|	已经是目标设置|
|其他|	更改失败|

## 编译说明
### 环境要求
- Windows 操作系统
- C 编译器（如 GCC、MSVC）
- Windows SDK

### 编译命令
#### 使用 GCC（MinGW）编译：
```cmd
gcc -o rlsw.exe main.c -luser32
```
#### 使用 MSVC 编译：

```cmd
cl main.c user32.lib
```

## 技术细节
该工具使用 Windows API 中的以下函数：
- EnumDisplaySettings - 获取当前显示设置
- ChangeDisplaySettings - 更改显示设置
- CDS_UPDATEREGISTRY - 标志位，确保设置持久化

## 注意事项
- 需要管理员权限才能更改显示设置
- 某些分辨率/刷新率组合可能不被显示器支持
- 更改设置前请确保您的硬件支持目标配置