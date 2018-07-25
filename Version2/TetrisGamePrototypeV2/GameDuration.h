/**
 * \file    GameDuration.h
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

#include <SFML/Graphics.hpp>

class GameDuration
{
public:
    void SetFont(const sf::Font* font)
	{
		mFont = font;
	}

    // Oyun zamanlamasi ile ilgili ilklendirmeleri gerceklestirir
    void Initialize()
    {
		if (nullptr != mFont)
		{
			/// Oyun suresi
			mDurationText.setPosition({ 65, 235 });
			mDurationText.setFont(*mFont);
			mDurationText.setCharacterSize(18);
			mDurationText.setStyle(sf::Text::Bold);
			mDurationText.setFillColor(sf::Color::White);
			mDurationText.setString("0");

			// Metini merkezlemek icin
			mDurationTextRect = mDurationText.getLocalBounds();
			mDurationText.setOrigin(mDurationTextRect.left + mDurationTextRect.width / 2.0f,
				mDurationTextRect.top + mDurationTextRect.height / 2.0f);
		}
    }

    // Zamani guncelleme
    void Update()
    {
        mLastDuration = static_cast<uint32_t>(mGameDurationClock.getElapsedTime().asSeconds());
        mDurationText.setString(std::to_string(mLastDuration));
    }

    // Bu metot zamani sifirlar
    void Reset()
    {
        // Zamani sifirla
        mGameDurationClock.restart();
    }

    // Oyun zamanini gosterir
    void Draw(sf::RenderWindow& window)
    {
        window.draw(mDurationText);
    }
protected:
	// Reference to font
	const sf::Font* mFont = nullptr;

    // Oyun zamanini gostermek icin kullanacagim saat
    sf::Clock mGameDurationClock;

    // Oyun suresi
    uint32_t mLastDuration = 0;
    sf::Text mDurationText;
    sf::FloatRect mDurationTextRect;
};
