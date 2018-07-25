#include <GameScore.h>

void GameScore::SetFont(const sf::Font* font)
{
	mFont = font;
}

void GameScore::Initialize()
{
	mScore = 0;

	if (nullptr != mFont)
	{
		// Puan
		mScoreText.setPosition({ 35, 155 });
		mScoreText.setFont(*mFont);
		mScoreText.setCharacterSize(18);
		mScoreText.setStyle(sf::Text::Bold);
		mScoreText.setFillColor(sf::Color::White);
		mScoreText.setString("0");

		// Metini merkezlemek icin
		mScoreTextRect = mScoreText.getLocalBounds();
		mScoreText.setOrigin(mScoreTextRect.left + mScoreTextRect.width / 2.0f,
			mScoreTextRect.top + mScoreTextRect.height / 2.0f);
	}
}

void GameScore::AddScore(uint32_t score)
{
    mScore += score;
    mScoreText.setString(std::to_string(mScore));
}

uint32_t GameScore::GetScore()
{
	return mScore;
}

void GameScore::Reset()
{
    mScore = 0;
    mScoreText.setString(std::to_string(mScore));
}

void GameScore::Draw(sf::RenderWindow& window)
{
    window.draw(mScoreText);
}
