#pragma once

#include <cstdint>
#include <memory>
#include <functional>
#include <SFML/Graphics.hpp>

#include <TetrisEvents.h>
#include <BaseScreen.h>
#include <GameOptionsData.h>

class OptionsScreen
	: public BaseScreen
{
public:
	OptionsScreen(GameOptionsData& val);

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

	// Ayar secimini guncelle
	void UpdateSelection();

	// Muzik ses seviyesini guncelle
	void UpdateMusicLevel();

	// Ekranlardan gelecek olan `event` lerden haberdar olmak icin
	std::function<void(GameScreenType, TetrisEvents)> mScreenCallbackFunction;

	// Uygulama fontu
	const sf::Font* mFont = nullptr;

	// Arka plan resmi
	std::string mBackGroundImagePath = "Data/TetrisOptionsScreen.png";
	sf::Texture mBackGroundTexture;
	sf::Sprite  mBackGroundSprite;

	// Oyun ayarlari
	GameOptionsData& mOptionsData;

	// Mevcut ayar (0 => muzik seviyesi, 1 => ses efektleri, 2 => skorlari sifirla)
	// Ok icin kullanacagimiz resim
	std::string mTexturePath = "Data/Arrow.png";
	sf::Texture mArrowTexture;
	sf::Sprite mArrowSprite;

	int32_t mCurrentSettingsIndex = 0;
	std::vector<sf::Vector2f> mArrowPositionList{ { 116, 186 },{ 120, 297}, {110, 365}, { 115, 442} };

	// Muzik imleci icin kullanacagimiz resim
	std::string mCursorTexturePath = "Data/MusicScrollItem.png";
	sf::Texture mCursorTexture;
	sf::Sprite mCursorSprite;
	sf::Vector2f mCursorReferencePosition{ 137, 211 };

	// Burada muzik sesi icin kullanacagimiz imlecin mevcut konumu ve izin verilen miktar
	float mCursorValue = 0.0F;

	// 20 kademeli bir ses ayari olacak
	float mCursorRangeIncrement = 8.5F;
	float mCursorRange = 170.0F;

	// Ses efektleri icin kullanacagimiz resim
	std::string mCheckTexturePath = "Data/BTN_CHECKBOX_IN.png";
	sf::Texture mCheckTexture;
	sf::Sprite mCheckSprite;
	sf::Vector2f mSFXReferencePosition{ 324, 276 };
	sf::Vector2f mChildModeReferencePosition{ 324, 344 };

	// SFML window
	sf::RenderWindow* mWindow;
};
