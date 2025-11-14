# rlsw - Windows Resolution Switcher
A lightweight Windows command-line tool for quickly switching display resolution and refresh rate.

[README](README.md) | [中文文档](README.zh-CN.md)

## Features
- 🚀 Quick display settings switching
- 💻 Custom resolution and refresh rate support
- 🔧 Simple command-line interface
- 📝 Persistent settings (registry update)

## Usage
### Basic Syntax
```cmd
rlsw.exe [width] [height] [refresh_rate]
```

### Parameters

| Parameter | Description | Example |
| ------- | --------------------- | ---- |
| width | Horizontal pixel count | 1920 |
| height | Vertical pixel count | 1080 |
| refresh_rate | Refresh rate in Hz | 60 |


### Example
Set display to 1920x1080 resolution with 60Hz refresh rate:

```cmd
rlsw.exe 1920 1080 60
```

### Return Codes
| Code | Description |
| ---- | ----------- | 
| 0 | Successfully changed settings |
| 1 | Already at target settings |
| Other | Change failed |


## Building
### Requirements
- Windows OS
- C compiler (GCC, MSVC, etc.)
- Windows SDK

### Build Commands
#### Using GCC (MinGW):

```cmd
gcc -o rlsw.exe main.c -luser32
```

#### Using MSVC:

```cmd
cl main.c user32.lib
```


## Technical Details
This tool uses the following Windows API functions:
- EnumDisplaySettings - Get current display settings
- ChangeDisplaySettings - Change display settings
- CDS_UPDATEREGISTRY - Flag to ensure persistent settings

## Notes
- Administrator privileges may be required to change display settings
- Some resolution/refresh rate combinations may not be supported by your monitor
- Ensure your hardware supports the target configuration before changing settings