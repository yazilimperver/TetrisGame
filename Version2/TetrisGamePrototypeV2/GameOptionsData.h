#pragma once

#include <cstdint>

struct GameOptionsData 
{
	// Muzik seviyesi
	int32_t mMusicLevel = 50;

	// Ses efektleri aciklik durumu
	bool mSoundFxEnabled = true;

	// Cocuk modu acik mi
	bool mChildModeEnabled = false;
};
