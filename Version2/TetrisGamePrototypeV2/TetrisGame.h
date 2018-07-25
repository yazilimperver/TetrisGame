/**
 * \file    TetrisGame.h
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
#include <GameScreenType.h>
#include <BaseScreen.h>
#include <MenuScreen.h>
#include <HighScoresScreen.h>
#include <HighScoreData.h>

#include <OptionsScreen.h>
#include <GameOptionsData.h>

#include <SFML/Graphics.hpp>

#include <functional>
#include <memory>
#include <string>
#include <map>

#include <TetrisEvents.h>

/// Asil sihrin gerceklestigi temel oyun sinifimiz karsinizda
/// Bu sinif ile temelde oyun girdilerini okuyarak, durumu guncelleme ve benzeri isler icin kullanacagiz
class TetrisGame
{
public:
    // Oyun sinifi yapicisi
    TetrisGame();

	// Ilklendirmeler
    // Basarili ise TRUE basariz ise FALSE don
    bool Initialize();

    // Oyunun ana dongusunu icerisinde barindiran metot
    void Run();
protected:

	// Bu metot butun ekranlar tarafundan kullanilacak olan SDL penceresini olusturacak
	void InitializeCommonEntities();

	// Screen eventleri
	void ScreenEvent(GameScreenType originatedScreen, TetrisEvents eventArg);

	// Mevcut oyun yuksek skorlarini kaydet
	void SaveScores();

	// En son oyun yuksek skorlarini geri yukle
	void RestoreScores();

	// Ilklendirme durumu
	bool mInitializationStatus = false;

	// Uygulamada kullanilacak olan font
	std::string mGameFontPath = "Data/LithosProRegular.ttf";
	sf::Font mGameFont;

	// Uygulamada kullanilacak olan diger font
	std::string mFontPath = "Data/sansation.ttf";
	sf::Font mFont;

    // Mevcut oyun ekrani. Buna gore gosterilecek ve isletilecek oyun mantiklari belirlenecek
    BaseScreen* mCurrentScreen = nullptr;

    // Oyun icin kullanilacak olan ekranlar
	// Her bir ekran bizim icin oyunun bir parcasi olarak. Baslangic ekrani, oyun ekrani veya menu ekrani olarak dusunebiliriz
    std::map<GameScreenType, std::unique_ptr<BaseScreen>> mRegisteredScreens;

    // SFML window
    sf::RenderWindow mWindow;

    // Oyun zamani icin kullanacagimiz saat
    sf::Clock mClock;

	// En yuksek skorlar diskte tutulacak ve bunlar uygulama her acildiginda okunacaklar
	// Map verileri sirali tuttugu icin elimizde her zaman sirali puanlar olacak
	// Multi map kullanmamizin sebebi de birden fazla ayni puan olabilecegi
	std::multimap<int32_t, HighScoreData> mHighScoreTable;

	// Puanlarin saklanmasi icin kullanilacak olan dosya ismi
	std::string mScoreFile = "Data/Score.bin";

	// Oyun ayarlari
	GameOptionsData mGameOptions;
};