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
