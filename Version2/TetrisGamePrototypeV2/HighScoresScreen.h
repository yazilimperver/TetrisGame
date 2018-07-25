/**
 * \file    HighScoresScreen.h
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

#include <cstdint>
#include <memory>
#include <functional>
#include <SFML/Graphics.hpp>

#include <TetrisEvents.h>
#include <BaseScreen.h>
#include <HighScoreData.h>

class HighScoresScreen
	: public BaseScreen
{
public:

	HighScoresScreen(const std::multimap<int32_t, HighScoreData>& val);

	// Gorsellestirmeleri gerceklestirecegimi metot
	void Display();

	virtual GameScreenType GetGameScreenType() override;

	// Cizim icin kullanilacak olan pencere sinifini gecirir
	virtual void SetWindow(sf::RenderWindow* window) override;

	// Ana siniftan gelen metotlar
	virtual bool Initialize() override;
	virtual void PreFrame() override;
	virtual void Input() override;
	virtual void Update(float timeSinceLastTick) override;

	virtual std::string GetName() override;
	void SetFont(const sf::Font* val);
	void BindCallback(std::function<void(GameScreenType, TetrisEvents)> fn);

	virtual void PostInitialize() override;

protected:

	// Ekranlardan gelecek olan `event` lerden haberdar olmak icin
	std::function<void(GameScreenType, TetrisEvents)> mScreenCallbackFunction;

	// Uygulama fontu
	const sf::Font* mFont = nullptr;

	// Arka plan resmi
	std::string mBackGroundImagePath = "Data/TetrisHighScoresScreen.png";
	sf::Texture mBackGroundTexture;
	sf::Sprite  mBackGroundSprite;

	// Yuksek puanlara referans
	const std::multimap<int32_t, HighScoreData>& mHighScoreTable;

	// En yuksek skor listesi metni
	sf::Text mHighScoreTextList;
	sf::FloatRect mHighScoreTextRect;

	// Puan listesi referans noktasi
	sf::Vector2f mReferencePoint;
	
	// SFML window
	sf::RenderWindow* mWindow;
};
