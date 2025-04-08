#ifndef MUSIC_WINDOWS_H
#define MUSIC_WINDOWS_H

#include <SDL2/SDL.h>

// 模拟Windows API中的Beep函数
// dwFreq: 频率，范围从37到32767赫兹
// dwDuration: 持续时间，以毫秒为单位
bool Beep(unsigned int dwFreq, unsigned int dwDuration);

// 初始化音频系统
bool InitAudio();

// 清理音频系统
void CleanupAudio();

#endif //MUSIC_WINDOWS_H 