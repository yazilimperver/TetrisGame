/**
 * \file    AudioFx.h
 * \author  yazilimperver
 * \brief   This source code is developed for Tetris Game Prototype
 * Tetris V2

Copyright © 2018, Yazilimperver, www.yazilimperver.com

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#pragma once

#include <string.h>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

class AudioFx
{
public:
	AudioFx(const std::string& path);

	std::string GetPath() const;
	void SetPath(std::string val);
	bool Initialize();
	void Play();
	sf::Sound& GetSoundRef();
protected:
	std::string mPath = "";
	sf::SoundBuffer mBuffer;
	sf::Sound mSound;
	bool mIsInitialized = false;
};
