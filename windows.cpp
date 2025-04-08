#include "windows.h"
#include <cmath>
#include <vector>

static SDL_AudioDeviceID audioDevice = 0;
static SDL_AudioSpec audioSpec;

bool InitAudio() {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        return false;
    }

    SDL_AudioSpec want;
    SDL_zero(want);
    want.freq = 44100;  // 采样率
    want.format = AUDIO_S16;  // 16位音频
    want.channels = 1;  // 单声道
    want.samples = 4096;  // 缓冲区大小
    want.callback = nullptr;  // 使用队列方式

    audioDevice = SDL_OpenAudioDevice(nullptr, 0, &want, &audioSpec, 0);
    if (audioDevice == 0) {
        SDL_Quit();
        return false;
    }

    SDL_PauseAudioDevice(audioDevice, 0);  // 开始播放
    return true;
}

void CleanupAudio() {
    if (audioDevice != 0) {
        SDL_CloseAudioDevice(audioDevice);
        audioDevice = 0;
    }
    SDL_Quit();
}

bool Beep(unsigned int dwFreq, unsigned int dwDuration) {
    if (audioDevice == 0) {
        return false;
    }

    // 确保频率在有效范围内
    if (dwFreq < 37 || dwFreq > 32767) {
        return false;
    }

    const int sampleRate = audioSpec.freq;
    const int samples = (dwDuration * sampleRate) / 1000;
    std::vector<Uint8> buffer(samples * 2);  // 16位音频，每个样本2字节

    // 生成正弦波
    for (int i = 0; i < samples; i++) {
        double t = static_cast<double>(i) / sampleRate;
        double amplitude = 32767.0 * 0.5;  // 16位音频的最大值的一半
        Sint16 sample = static_cast<Sint16>(amplitude * sin(2.0 * M_PI * dwFreq * t));
        
        // 写入音频数据
        buffer[i * 2] = sample & 0xFF;
        buffer[i * 2 + 1] = (sample >> 8) & 0xFF;
    }

    // 清空之前的音频队列
    SDL_ClearQueuedAudio(audioDevice);
    
    // 添加新的音频数据到队列
    if (SDL_QueueAudio(audioDevice, buffer.data(), buffer.size()) != 0) {
        return false;
    }

    // 等待音频播放完成
    SDL_Delay(dwDuration);
    return true;
} 