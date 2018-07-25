/**
 * \file    GameScore.h
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

class GameScore
{
public:
    // Font nesnesine bir referansi gecirelim
	void SetFont(const sf::Font* font);

    // Oyun puanlamasi ile ilgili ilklendirmeleri gerceklestirir
    void Initialize();

    // Verilen puani mevcut puana ekler
    void AddScore(uint32_t score);
	uint32_t GetScore();

    // Bu metot puani sifirlar
    void Reset();

    // Oyun puanini gosterir
    void Draw(sf::RenderWindow& window);
protected:
	// Reference to font
	const sf::Font* mFont = nullptr;

    // Oyun puani
    uint32_t mScore = 0;

    // Oyun puanina iliskin metin nesnesi
    sf::Text mScoreText;

    // Oyun metninin gosterilecegi kutu
    sf::FloatRect mScoreTextRect;
};
