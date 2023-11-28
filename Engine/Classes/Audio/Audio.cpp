#include "Audio.h"
#include <iostream>
using namespace TEG;
/**
 * @brief Constructor for the Audio class.
 * @param filePath The path to the WAV file.
 */
Audio::Audio(const char* filePath) : paused(false) {
    // Convert narrow string to wide string
    int wideLength = MultiByteToWideChar(CP_UTF8, 0, filePath, -1, nullptr, 0);
    if (wideLength == 0) {
        std::cerr << "Error getting wide string length\n";
        return;
    }

    wchar_t* wideFilePath = new wchar_t[wideLength];
    if (MultiByteToWideChar(CP_UTF8, 0, filePath, -1, wideFilePath, wideLength) == 0) {
        std::cerr << "Error converting file path to wide string\n";
        delete[] wideFilePath;
        return;
    }

    // Use mmioOpenW instead of mmioOpen
    MMIOINFO mmioInfo;
    HMMIO hFile = mmioOpenW(wideFilePath, &mmioInfo, MMIO_READ);
    delete[] wideFilePath;

    if (!hFile) {
        std::cerr << "Error opening audio file\n";
        return;
    }

    parentChunk.fccType = mmioFOURCC('W', 'A', 'V', 'E');
    if (mmioDescend(hFile, &parentChunk, 0, MMIO_FINDRIFF) != 0) {
        std::cerr << "Error finding WAV RIFF chunk\n";
        mmioClose(hFile, 0);
        return;
    }

    childChunk.fccType = mmioFOURCC('f', 'm', 't', ' ');
    if (mmioDescend(hFile, &childChunk, &parentChunk, 0) != 0) {
        std::cerr << "Error finding WAV format chunk\n";
        mmioClose(hFile, 0);
        return;
    }

    if (mmioRead(hFile, reinterpret_cast<HPSTR>(&waveFormat), sizeof(WAVEFORMATEX)) != sizeof(WAVEFORMATEX)) {
        std::cerr << "Error reading WAV format\n";
        mmioClose(hFile, 0);
        return;
    }

    mmioAscend(hFile, &childChunk, 0);

    childChunk.ckid = mmioFOURCC('d', 'a', 't', 'a');
    if (mmioDescend(hFile, &childChunk, &parentChunk, MMIO_FINDCHUNK) != 0) {
        std::cerr << "Error finding WAV data chunk\n";
        mmioClose(hFile, 0);
        return;
    }

    mmioClose(hFile, 0);
}

/**
 * @brief Destructor for the Audio class.
 */
Audio::~Audio()
{
	waveOutClose(hWaveOut);
}

/**
 * @brief Starts or resumes audio playback.
 */
void Audio::play()
{
	if (paused)
	{
		waveOutRestart(hWaveOut);
		paused = false;
	}
	else
	{
		waveOutReset(hWaveOut);
		waveOutWrite(hWaveOut, reinterpret_cast<WAVEHDR *>(&childChunk), sizeof(MMCKINFO));
	}
}

/**
 * @brief Pauses audio playback.
 */
void Audio::pause()
{
	waveOutPause(hWaveOut);
	paused = true;
}

/**
 * @brief Resumes audio playback.
 */
void Audio::resume()
{
	waveOutRestart(hWaveOut);
	paused = false;
}

/**
 * @brief Sets the volume level.
 * @param volume The volume level (0 to 100).
 */
void Audio::setVolume(int volume)
{
	DWORD vol = (DWORD)((double)volume / 100.0 * 0xFFFF);
	waveOutSetVolume(hWaveOut, MAKELONG(vol, vol));
}

/**
 * @brief Checks if audio is currently playing.
 * @return True if audio is playing, false otherwise.
 */
bool Audio::isPlaying()
{
	return !paused;
}