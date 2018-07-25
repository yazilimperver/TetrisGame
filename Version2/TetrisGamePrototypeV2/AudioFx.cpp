#include <AudioFx.h>
#include <iostream>
using namespace std;

AudioFx::AudioFx(const std::string& path)
	: mPath{ path }
{

}

std::string AudioFx::GetPath() const
{
	return mPath;
}

void AudioFx::SetPath(std::string val)
{
	mPath = val;
}

bool AudioFx::Initialize()
{
	if (mBuffer.loadFromFile(mPath))
	{
		mSound.setBuffer(mBuffer);
		mIsInitialized = true;
	}
	else
	{
		cout << "Ses yuklenmesinde hata. Ses dosya ismi:" << mPath << endl;
	}

	return mIsInitialized;
}

void AudioFx::Play()
{
	if (true == mIsInitialized)
	{
		mSound.play();
	}
}

sf::Sound& AudioFx::GetSoundRef()
{
	return mSound;
}
