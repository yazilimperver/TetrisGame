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
