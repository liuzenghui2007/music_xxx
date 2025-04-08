#include "windows.h"
#include <iostream>

int main() {
    // 初始化音频系统
    if (!InitAudio()) {
        std::cerr << "无法初始化音频系统" << std::endl;
        return 1;
    }

    // 小星星的音符频率（Hz）
    const int C4 = 262;  // 中音Do
    const int D4 = 294;  // 中音Re
    const int E4 = 330;  // 中音Mi
    const int F4 = 349;  // 中音Fa
    const int G4 = 392;  // 中音Sol
    const int A4 = 440;  // 中音La

    // 音符持续时间（毫秒）
    const int QUARTER_NOTE = 500;  // 四分音符
    const int HALF_NOTE = 1000;    // 二分音符

    // 播放小星星
    // 小星星 小星星 亮晶晶
    Beep(C4, QUARTER_NOTE); Beep(C4, QUARTER_NOTE);
    Beep(G4, QUARTER_NOTE); Beep(G4, QUARTER_NOTE);
    Beep(A4, QUARTER_NOTE); Beep(A4, QUARTER_NOTE);
    Beep(G4, HALF_NOTE);

    // 满天都是小星星
    Beep(F4, QUARTER_NOTE); Beep(F4, QUARTER_NOTE);
    Beep(E4, QUARTER_NOTE); Beep(E4, QUARTER_NOTE);
    Beep(D4, QUARTER_NOTE); Beep(D4, QUARTER_NOTE);
    Beep(C4, HALF_NOTE);

    // 清理音频系统
    CleanupAudio();
    return 0;
}
