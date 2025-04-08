#include <SDL.h>
#include <iostream>
#include <vector>
#include <cmath>

// 定义音符频率（Hz）
const double C4 = 261.63;  // 中音Do
const double D4 = 293.66;  // 中音Re
const double E4 = 329.63;  // 中音Mi
const double F4 = 349.23;  // 中音Fa
const double G4 = 392.00;  // 中音Sol
const double A4 = 440.00;  // 中音La
const double B4 = 493.88;  // 中音Si

// 定义音符结构
struct Note {
    double frequency;
    int duration;  // 毫秒
};

// 小星星的乐谱
const std::vector<Note> twinkleStar = {
    {C4, 500}, {C4, 500}, {G4, 500}, {G4, 500},
    {A4, 500}, {A4, 500}, {G4, 1000},
    {F4, 500}, {F4, 500}, {E4, 500}, {E4, 500},
    {D4, 500}, {D4, 500}, {C4, 1000},
    {G4, 500}, {G4, 500}, {F4, 500}, {F4, 500},
    {E4, 500}, {E4, 500}, {D4, 1000},
    {G4, 500}, {G4, 500}, {F4, 500}, {F4, 500},
    {E4, 500}, {E4, 500}, {D4, 1000},
    {C4, 500}, {C4, 500}, {G4, 500}, {G4, 500},
    {A4, 500}, {A4, 500}, {G4, 1000},
    {F4, 500}, {F4, 500}, {E4, 500}, {E4, 500},
    {D4, 500}, {D4, 500}, {C4, 1000}
};

// 生成正弦波
void generateSineWave(SDL_AudioDeviceID device, double frequency, int duration) {
    const int sampleRate = 44100;
    const int samples = (duration * sampleRate) / 1000;
    std::vector<Uint8> buffer(samples * 2);  // 16位音频，所以每个样本2字节

    for (int i = 0; i < samples; i++) {
        double t = static_cast<double>(i) / sampleRate;
        double amplitude = 32767.0 * 0.5;  // 16位音频的最大值的一半
        Sint16 sample = static_cast<Sint16>(amplitude * sin(2.0 * M_PI * frequency * t));
        
        // 写入左右声道
        buffer[i * 2] = sample & 0xFF;
        buffer[i * 2 + 1] = (sample >> 8) & 0xFF;
    }

    SDL_QueueAudio(device, buffer.data(), buffer.size());
}

int main() {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        std::cerr << "SDL初始化失败: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_AudioSpec want, have;
    SDL_zero(want);
    want.freq = 44100;  // 采样率
    want.format = AUDIO_S16;  // 16位音频
    want.channels = 2;  // 立体声
    want.samples = 4096;  // 缓冲区大小
    want.callback = nullptr;  // 使用队列方式

    SDL_AudioDeviceID device = SDL_OpenAudioDevice(nullptr, 0, &want, &have, 0);
    if (device == 0) {
        std::cerr << "无法打开音频设备: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_PauseAudioDevice(device, 0);  // 开始播放

    // 播放小星星
    for (const auto& note : twinkleStar) {
        generateSineWave(device, note.frequency, note.duration);
        SDL_Delay(note.duration);  // 等待音符播放完成
    }

    // 等待最后一段音频播放完成
    SDL_Delay(1000);

    SDL_CloseAudioDevice(device);
    SDL_Quit();

    return 0;
}
