/**
 * \file    GameScreen.h
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
/**
* \file    GameScreen.h
* \author  yazilimperver
* \brief   This source code is developed for Tetris Game Prototype

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
#include <BaseScreen.h>

#include <TetrisTable.h>
#include <TetrisFigure.h>
#include <GameScore.h>
#include <GameLevel.h>
#include <GameDuration.h>
#include <GameScreenType.h>
#include <TetrisEvents.h>
#include <functional>

#include <AudioFx.h>

#include <SFML/Graphics.hpp>
#include <SFML/Audio/Music.hpp>

struct GameOptionsData;

// Bu sinif oyunun oynandigi ekran ile ilgili mantiklarin gerceklenmesinden sorum olan sinif
class GameScreen
    : public BaseScreen
{
public:
    GameScreen(const GameOptionsData& val);

    // Oyun mantigini gercekleyecegimiz metot
    void Update(float timeSinceLastTick);

    // Gorsellestirmeleri gerceklestirecegimi metot
    void Display();

    // Girdileri isleyecegimi metot
    void Input();

    virtual GameScreenType GetGameScreenType() override;
    virtual bool Initialize() override;

    // Cizim icin kullanilacak olan pencere sinifini gecirir
    virtual void SetWindow(sf::RenderWindow* window) override;

    virtual void PreFrame() override;

	virtual std::string GetName() override;
	void SetFont(const sf::Font* val);
	
	void BindCallback(std::function<void(GameScreenType, TetrisEvents)> fn);
	virtual void PostInitialize() override;

	int32_t ObtainLastScore();
protected:

    // Her dongu icin kullanilacak degiskenleri sifirla
    void ResetTickParameters();

	// Ekranlardan gelecek olan `event` lerden haberdar olmak icin
	std::function<void(GameScreenType, TetrisEvents)> mScreenCallbackFunction;

    // Mevcut oyun ekrani. Buna gore gosterilecek ve isletilecek oyun mantiklari belirlenecek
    GameScreenType mCurrentScreen;

    // En son girdi sonucu sag/sol hareket miktari
    int32_t mDX;

    // Dondurme girdisi verildi mi
    bool mRotationInitiated;

    // Tetris tahtasi
    TetrisTable mTetrisTable;

    // Su an hareket ettirilen tetris tasi
    TetrisFigure mCurrentTetrisFigure;

    // SFML window
    sf::RenderWindow* mWindow;

	// Kullanilabilecek figur adeti (cocuk modunda 2, diger durumda 8)
	uint32_t mFigureCount = gTetrisFigureCount;

    // En son hareketten bu yana gecen zaman
    float mTimeSinceLastMove = 0.0f;

    // Tetris figurunun bir sonraki satira gecmesi icin beklenen zaman (saniye cinsinden)
	float mMoveTimeInSecond = 0.3f;

	// Ayrica her N yeni satir icin bir puan ekleyecegiz
	int32_t mRowCountPerScore = 3;
	int32_t mLastRowCount = 0;

	// Mevcut tas hizi (her bes dkkda bir artacak) sure 0.09 sn duscek
	float mCurrentDelay = gDelay;

	// Seviye gecme suresi 3dk (180 sn)
	float mLevelUpTime = 180.0F;
	float mTimeSinceStart = 0.0F;

	// Uygulama fontu
	const sf::Font* mFont = nullptr;
    
	// Oyun zamanini gostermek icin kullanacagim saat
    GameDuration mGameDuration;

	// Oyun seviyesi ile ilgili mantiklarin bulundugu sinif
	GameLevel mGameLevel;
	
	// Ayarlar
	const GameOptionsData& mOptions;

	// Oyun muzigi
	std::string mGameMusicPath = "Data/Audio/music.ogg";
	sf::Music mGameMusic;

	// Oyun icerisinde kullanilacak olan sesler
	AudioFx mGameOverSound{ "Data/Audio/gameover.wav" };
	AudioFx mFigureRotateSound{ "Data/Audio/block-rotate.wav" };
	AudioFx mFigureBlockHitSound{ "Data/Audio/blockHit.wav" };
	AudioFx mFigureSingleLineRemovalSound{ "Data/Audio/line-remove.wav" };
	AudioFx mFigureMultiLineRemovalSound{ "Data/Audio/line-removal4.wav" };

    // Oyun puanina iliskin sinif
    GameScore mGameScore;

    // Oyun bitti mi kontrolü
    bool mIsGameOver = false;

    // Oyun bitis metni
    sf::Text mGameOverText;
    sf::RectangleShape mTextBackgroundRect;
    sf::FloatRect mGameOverTextRect;
};
