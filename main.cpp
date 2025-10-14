#include <iostream>
#include <string>
#include <windows.h>

LONG change_monitor_settings(int width, int height, int refresh_rate) {
  DEVMODE dm = {0};
  dm.dmSize = sizeof(dm);
  if (!EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &dm)) {
    return DISP_CHANGE_FAILED;
  }
  if (dm.dmPelsWidth == width && dm.dmPelsHeight == height &&
      dm.dmDisplayFrequency == refresh_rate) {
    return DISP_CHANGE_SUCCESSFUL; // 已经是目标设置
  }
  dm.dmPelsWidth = width;
  dm.dmPelsHeight = height;
  dm.dmDisplayFrequency = refresh_rate;
  dm.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY;
  return ChangeDisplaySettings(&dm, CDS_UPDATEREGISTRY);
}

void print_help() {
  std::cout << "rlsw.exe [width] [height] [refresh_rate]" << std::endl;
  std::cout << "eg: rlsw.exe 1920 1080 60" << std::endl;
}

int main(int argc, char **argv) {
  for (int i = 0; i < argc; i++) {
    if (argv[i] == "-h" || argv[i] == "--help") {
      print_help();
      return 0;
    }
  }
  if (argc != 4) {
    print_help();
    return 1;
  }
  auto width = std::stoi(argv[1]);
  auto height = std::stoi(argv[2]);
  auto refresh_rate = std::stoi(argv[3]);
  return change_monitor_settings(width, height, refresh_rate);
}