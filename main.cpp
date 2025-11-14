#include <stdio.h>
#include <stdlib.h>

#include <windows.h>

LONG change_monitor_settings(int width, int height, int refresh_rate)
{
    DEVMODE dm = { 0 };
    dm.dmSize = sizeof(dm);
    if (!EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &dm)) {
        return DISP_CHANGE_FAILED;
    }
    if (dm.dmPelsWidth == width && dm.dmPelsHeight == height && dm.dmDisplayFrequency == refresh_rate) {
        return DISP_CHANGE_SUCCESSFUL; // 已经是目标设置
    }
    dm.dmPelsWidth = width;
    dm.dmPelsHeight = height;
    dm.dmDisplayFrequency = refresh_rate;
    dm.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY;
    return ChangeDisplaySettings(&dm, CDS_UPDATEREGISTRY);
}

void print_help()
{
    printf(
        "rlsw.exe [width] [height] [refresh_rate]\neg: rlsw.exe 1920 1080 60\n");
}

int main(int argc, char** argv)
{
    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help")) {
            print_help();
            return 0;
        }
    }
    if (argc != 4) {
        print_help();
        return 1;
    }
    auto width = atoi(argv[1]);
    auto height = atoi(argv[2]);
    auto refresh_rate = atoi(argv[3]);
    return change_monitor_settings(width, height, refresh_rate);
}