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
