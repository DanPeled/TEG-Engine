#ifndef AUDIO_H
#define AUDIO_H

#include <windows.h>
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib")
namespace TEG
{
	/**
	 * @brief The Audio class for playing WAV files using winmm.
	 */
	class Audio
	{
	public:
		/**
		 * @brief Constructor for the Audio class.
		 * @param filePath The path to the WAV file.
		 */
		Audio(const char *filePath);

		/**
		 * @brief Destructor for the Audio class.
		 */
		~Audio();

		/**
		 * @brief Starts or resumes audio playback.
		 */
		void play();

		/**
		 * @brief Pauses audio playback.
		 */
		void pause();

		/**
		 * @brief Resumes audio playback.
		 */
		void resume();

		/**
		 * @brief Sets the volume level.
		 * @param volume The volume level (0 to 100).
		 */
		void setVolume(int volume);

		/**
		 * @brief Checks if audio is currently playing.
		 * @return True if audio is playing, false otherwise.
		 */
		bool isPlaying();

	private:
		HWAVEOUT hWaveOut;
		WAVEFORMATEX waveFormat;
		MMCKINFO parentChunk;
		MMCKINFO childChunk;
		bool paused;
	};
}
#endif
