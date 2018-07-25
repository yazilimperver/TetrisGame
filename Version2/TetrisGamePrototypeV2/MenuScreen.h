#pragma once

#include <cstdint>
#include <memory>
#include <functional>
#include <SFML/Graphics.hpp>

#include <AudioFx.h>
#include <TetrisEvents.h>
#include <BaseScreen.h>

class MenuScreen
	: public BaseScreen
{
public:
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

	// Baslangicataki animasyon icin kullanilacak olan sure
	// Bu sure icerisinde logo gorunur olacak ve nihayetinde dugmeye basin uyarisi gelecek
	float mLogoAppearTime = 3.0F;
	float mElapsedTime = 0.0F;

	// Uygulama fontu
	const sf::Font* mFont = nullptr;

	// Menu referans noktasi
	sf::Vector2f mMenuReferencePoint;
	
	// Menu ekrani arka plan resmi
	std::string mBackGroundImagePath = "Data/MenuBackground.png";
	sf::Texture mBackGroundTexture;
	sf::Sprite  mBackGroundSprite;
	
	// Menu resimleri
	std::string mMenuImagePath = "Data/MenuButtons.png";
	sf::Texture mMenuTexture;
	sf::Sprite  mMenuSprite;
	
	// Secili menu kalemi
	int mMenuIndex = 0;

	// Menu secim cercevesi
	sf::Sprite  mMenuSelectionSprite;

	// Transparanlik icin kullanilacak olan renk
	sf::Color mSpriteColor;

	// Menu de kullanilacak olan seslere iliskin degiskenler
	AudioFx mMenuTraverseAudio{ "Data/Audio/whoosh.wav" };
	AudioFx mMenuSelectionAudio{ "Data/Audio/select.wav" };

	// SFML window
	sf::RenderWindow* mWindow;
};