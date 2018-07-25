#include <SplashScreen.h>
#include <GameScreenType.h>

#include <TetrisDefinitions.h>

#include <iostream>
using namespace std;

bool SplashScreen::Initialize()
{
	bool initializationStatus = false;

	if (nullptr != mWindow
		&&
		nullptr != mFont)
	{
		if (!mCLogoTexture.loadFromFile(mCLogoPath.c_str()))
		{
			cout << "Texture yuklenmesinde hata. Texture ismi:" << mCLogoPath << endl;
		}
		else
		{
			// Logo ilklendirme
			auto sizeOfTexture = mCLogoTexture.getSize();

			mCLogoSprite.setTexture(mCLogoTexture);
			mCLogoSprite.setPosition({ gWindowWidth / 2 , gWindowHeight / 2 });
			
			auto spriteRect = mCLogoSprite.getLocalBounds();
			mCLogoSprite.setOrigin(spriteRect.left + spriteRect.width / 2.0f,
				spriteRect.top + spriteRect.height / 2.0f);

			mSpriteColor = sf::Color::White;
			mSpriteColor.a = 0;
			mCLogoSprite.setColor(mSpriteColor);

			// Tusa basim metni ilklendirme
			mPressKeyText.setPosition({ gWindowWidth / 2, gWindowHeight / 2 + spriteRect.height});
			mPressKeyText.setFont(*mFont);
			mPressKeyText.setCharacterSize(20);
			mPressKeyText.setFillColor(sf::Color::Green);
			mPressKeyText.setString("     DEVAM ETMEK ICIN\nLUTFEN BIR TUSA BASINIZ");

			// Metini merkezlemek icin
			mPressKeyTextRect = mPressKeyText.getLocalBounds();
			mPressKeyText.setOrigin(mPressKeyTextRect.left + mPressKeyTextRect.width / 2.0f,
				mPressKeyTextRect.top + mPressKeyTextRect.height / 2.0f);
			mPressKeyText.setFillColor(sf::Color{ 2, 143, 0 });

			initializationStatus = true;
		}
	}

	return true;
}

void SplashScreen::PreFrame()
{
}

void SplashScreen::Input()
{
	// Handle events
	// Pencere olayi nesnesi
	sf::Event event;

	while (mWindow->pollEvent(event))
	{
		// Space key tusuna 
		if ((event.type == sf::Event::KeyPressed)
			&&
			(mElapsedTime >= mLogoAppearTime))
		{
			mScreenCallbackFunction(this->GetGameScreenType(), TetrisEvents::eTETRIS_EVENT_SPLASH_KEY_PRESSED);
		}
	}
}

void SplashScreen::Update(float timeSinceLastTick)
{
	if (mElapsedTime < mLogoAppearTime)
	{
		mSpriteColor.a = static_cast<sf::Uint8>(mElapsedTime * (256 / mLogoAppearTime));
		mElapsedTime += timeSinceLastTick;
		mCLogoSprite.setColor(mSpriteColor);
	}
}

std::string SplashScreen::GetName()
{
	return "ACILIS EKRANI";
}

void SplashScreen::SetFont(const sf::Font* val)
{
	mFont = val;
}

void SplashScreen::BindCallback(std::function<void(GameScreenType, TetrisEvents)> fn)
{
	mScreenCallbackFunction = std::bind(fn, std::placeholders::_1, std::placeholders::_2);
}

void SplashScreen::PostInitialize()
{
}

void SplashScreen::Display()
{
	// Pencereyi siyaha temizle
	mWindow->clear(sf::Color::Black);
	
	// Display things on screen
	mWindow->draw(mCLogoSprite);

	if (mElapsedTime >= mLogoAppearTime)
	{
		mWindow->draw(mPressKeyText);
	}

	// Her seyi cizelim
	mWindow->display();
}

GameScreenType SplashScreen::GetGameScreenType()
{
	return GameScreenType::eGAME_SCREEN_TYPE_SPLASH;
}

void SplashScreen::SetWindow(sf::RenderWindow* window)
{
	mWindow = window;
}
