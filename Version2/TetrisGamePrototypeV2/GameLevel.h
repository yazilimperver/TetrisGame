#pragma once

#include <SFML/Graphics.hpp>

class GameLevel
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
			mLevelText.setPosition({ 65, 315 });
			mLevelText.setFont(*mFont);
			mLevelText.setCharacterSize(18);
			mLevelText.setStyle(sf::Text::Bold);
			mLevelText.setFillColor(sf::Color::White);
			mLevelText.setString("1");

			// Metini merkezlemek icin
			mLevelTextRect = mLevelText.getLocalBounds();
			mLevelText.setOrigin(mLevelTextRect.left + mLevelTextRect.width / 2.0f,
				mLevelTextRect.top + mLevelTextRect.height / 2.0f);
		}
	}

	// Seviye arttir guncelleme
	void IncrementLevel()
	{
		mLevel++;
		mLevelText.setString(std::to_string(mLevel));
	}

	// Bu metot seviyeyi sifirlar
	void Reset()
	{
		// seviye sifirla
		mLevel = 1;
	}

	// Oyun zamanini gosterir
	void Draw(sf::RenderWindow& window)
	{
		window.draw(mLevelText);
	}

	uint32_t GetLevel()
	{
		return mLevel;
	}
protected:
	// Reference to font
	const sf::Font* mFont = nullptr;

	// Oyun seviyesi
	uint32_t mLevel = 1;
	sf::Text mLevelText;
	sf::FloatRect mLevelTextRect;
};
