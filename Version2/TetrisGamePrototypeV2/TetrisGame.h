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