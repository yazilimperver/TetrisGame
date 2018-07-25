#include <HighScoresScreen.h>
#include <GameScreenType.h>

#include <TetrisDefinitions.h>

#include <iostream>
using namespace std;

bool HighScoresScreen::Initialize()
{
	bool initializationStatus = false;

	if (nullptr != mWindow
		&&
		nullptr != mFont)
	{	
		if (!mBackGroundTexture.loadFromFile(mBackGroundImagePath.c_str()))
		{
			cout << "Texture yuklenmesinde hata. Texture ismi:" << mBackGroundImagePath << endl;
		}
		else
		{
			// Arka plani ilklendirme
			auto sizeOfTexture = mBackGroundTexture.getSize();

			mBackGroundSprite.setTexture(mBackGroundTexture);
			mBackGroundSprite.setPosition({ 0, 0 });

			// metni ilklendirme
			mHighScoreTextList.setPosition({ gWindowWidth / 2 - 50, 140});
			mHighScoreTextList.setFont(*mFont);
			mHighScoreTextList.setCharacterSize(16);
			mHighScoreTextList.setFillColor(sf::Color::Green);
			mHighScoreTextList.setString("KAYITLI SKOR YOK");

			// Metini merkezlemek icin
			mHighScoreTextRect = mHighScoreTextList.getLocalBounds();
			mHighScoreTextList.setOrigin(mHighScoreTextRect.left + mHighScoreTextRect.width / 2.0f,
				mHighScoreTextRect.top + mHighScoreTextRect.height / 2.0f);

			initializationStatus = true;
		}
	}

	return true;
}

void HighScoresScreen::PreFrame()
{
}

void HighScoresScreen::Input()
{
	// Handle events
	// Pencere olayi nesnesi
	sf::Event event;

	while (mWindow->pollEvent(event))
	{
		// Space key tusuna 
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.type == sf::Event::KeyPressed)
			{
				mScreenCallbackFunction(this->GetGameScreenType(), TetrisEvents::eTETRIS_EVENT_GAME_RETURN_MENU);

				break;
			}
		}
	}
}

void HighScoresScreen::Update(float timeSinceLastTick)
{
}

std::string HighScoresScreen::GetName()
{
	return "YUKSEK SKOR EKRANI";
}

void HighScoresScreen::SetFont(const sf::Font* val)
{
	mFont = val;
}

void HighScoresScreen::BindCallback(std::function<void(GameScreenType, TetrisEvents)> fn)
{
	mScreenCallbackFunction = std::bind(fn, std::placeholders::_1, std::placeholders::_2);
}

void HighScoresScreen::PostInitialize()
{
	std::string scoreText = "KAYITLI SKOR YOK";
	if (mHighScoreTable.size() > 0)
	{
		scoreText = "";

		auto itr = mHighScoreTable.rbegin();
		int index = 1;
		while (itr != mHighScoreTable.rend())
		{
			scoreText += (std::to_string(index++) + ") ");
			scoreText += itr->second.mText;
			scoreText += " : ";
			scoreText += std::to_string(itr->first);
			scoreText += "\n";
			itr++;
		}
	}

	mHighScoreTextList.setString(scoreText);
}

HighScoresScreen::HighScoresScreen(const std::multimap<int32_t, HighScoreData>& val)
	: mHighScoreTable(val)
{

}

void HighScoresScreen::Display()
{
	// Pencereyi siyaha temizle
	mWindow->clear(sf::Color::Black);

	mWindow->draw(mBackGroundSprite);

	mWindow->draw(mHighScoreTextList);

	// Her seyi cizelim
	mWindow->display();
}

GameScreenType HighScoresScreen::GetGameScreenType()
{
	return GameScreenType::eGAME_SCREEN_TYPE_HIGH_SCORES;
}

void HighScoresScreen::SetWindow(sf::RenderWindow* window)
{
	mWindow = window;
}
