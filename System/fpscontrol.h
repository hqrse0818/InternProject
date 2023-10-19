#include	<thread>
#include	<iostream>
#include	<windows.h>
#include	<timeapi.h>
#include "../Debug.h"

class FPS {
public:
	FPS() = delete;
	FPS(uint64_t f) {
		mMicrosecondsPerFrame = static_cast<uint64_t>((1000.0f * 1000.0f) / f);
	}
	~FPS() {}

	uint64_t  CalcDelta() {
		mCurrentTime = timeGetTime();					// ���ݎ����擾
		mDeltaTime = mCurrentTime - mLastTime;	// �O����s������Ɍo�ߎ��Ԃ��擾
		mLastTime = mCurrentTime;
		return mDeltaTime;
	}

	void Wait() {
		int64_t sleep_time = mMicrosecondsPerFrame - mDeltaTime;
		if (sleep_time > 0) {
			float tt = sleep_time / 1000.0f;

			#if defined(DEBUG) || defined(_DEBUG)
				//DEBUG_LOG("sleep time(ms):" << tt);
			#endif

			std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(tt)));
			//�w�肵�����Ύ��Ԃ������X���b�h���u���b�N���� (function template)
		}
	}

private:
	uint64_t mMicrosecondsPerFrame = 0;				// micro second
	uint64_t mCurrentTime = 0;
	uint64_t mLastTime = 0;
	uint64_t mDeltaTime = 0;
};