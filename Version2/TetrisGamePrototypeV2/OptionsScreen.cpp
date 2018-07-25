#include <OptionsScreen.h>
#include <GameScreenType.h>

#include <TetrisDefinitions.h>

#include <iostream>
using namespace std;

bool OptionsScreen::Initialize()
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
			
			if (!mArrowTexture.loadFromFile(mTexturePath.c_str()))
			{
				std::cout << "Texture yuklenmesinde hata. Texture ismi:" << mTexturePath << std::endl;
				return false;
			}
			else
			{
				mArrowSprite.setTexture(mArrowTexture);

				initializationStatus = true;
			}

			// Muzik imlec ilklendirme
			if (!mCursorTexture.loadFromFile(mCursorTexturePath.c_str()))
			{
				initializationStatus = false;
				std::cout << "Texture yuklenmesinde hata. Texture ismi:" << mCursorTexturePath << std::endl;
				return false;
			}
			else
			{
				mCursorSprite.setTexture(mCursorTexture);
				mCursorSprite.setPosition(mCursorReferencePosition);

				initializationStatus = true;
			}

			// Ses efekt resmi ilklendirme
			if (!mCheckTexture.loadFromFile(mCheckTexturePath.c_str()))
			{
				initializationStatus = false;
				std::cout << "Texture yuklenmesinde hata. Texture ismi:" << mCheckTexturePath << std::endl;
				return false;
			}
			else
			{
				mCheckSprite.setTexture(mCheckTexture);
				mCheckSprite.setPosition(mSFXReferencePosition);

				initializationStatus = true;
			}
		}
	}

	return true;
}

void OptionsScreen::PreFrame()
{
}

void OptionsScreen::Input()
{
	// Handle events
	// Pencere olayi nesnesi
	sf::Event event;

	while (mWindow->pollEvent(event))
	{
		// Space key tusuna 
		if (event.type == sf::Event::KeyPressed)
		{
			if ((event.type == sf::Event::Closed)
				||
				(event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
			{
				mScreenCallbackFunction(this->GetGameScreenType(), TetrisEvents::eTETRIS_EVENT_GAME_RETURN_MENU);

				break;
			}

			if (event.key.code == sf::Keyboard::Up)
			{
				mCurrentSettingsIndex--;

				if (mCurrentSettingsIndex < 0)
				{
					mCurrentSettingsIndex = 3;
				}

				this->UpdateSelection();
			}
			else if (event.key.code == sf::Keyboard::Down)
			{
				mCurrentSettingsIndex++;

				if (mCurrentSettingsIndex > 3)
				{
					mCurrentSettingsIndex = 0;
				}

				this->UpdateSelection();
			}

			// Sadece muzikte kullanacagiz
			if (0 == mCurrentSettingsIndex)
			{
				if (event.key.code == sf::Keyboard::Right)
				{
					mOptionsData.mMusicLevel += 5;
				}
				else if (event.key.code == sf::Keyboard::Left)
				{
					mOptionsData.mMusicLevel -= 5;
				}

				this->UpdateMusicLevel();
			}
			else if (1 == mCurrentSettingsIndex)
			{
				if ((event.key.code == sf::Keyboard::Space)
					||
					(event.key.code == sf::Keyboard::Return))
				{
					mOptionsData.mSoundFxEnabled = !mOptionsData.mSoundFxEnabled;
				}
			}
			else if (2 == mCurrentSettingsIndex)
			{
				if ((event.key.code == sf::Keyboard::Space)
					||
					(event.key.code == sf::Keyboard::Return))
				{
					// Cocuk modunu aktiflestirelim
					mOptionsData.mChildModeEnabled = !mOptionsData.mChildModeEnabled;
				}
			}
			else if (3 == mCurrentSettingsIndex)
			{
				if ((event.key.code == sf::Keyboard::Space)
					||
					(event.key.code == sf::Keyboard::Return))
				{
					// Puanlari sifirlama olayi gonderelim
					mScreenCallbackFunction(this->GetGameScreenType(), TetrisEvents::eTETRIS_EVENT_RESET_SCORES);
				}
			}
		}
	}
}

void OptionsScreen::Update(float timeSinceLastTick)
{
}

std::string OptionsScreen::GetName()
{
	return "AYARLAR EKRANI";
}

void OptionsScreen::SetFont(const sf::Font* val)
{
	mFont = val;
}

void OptionsScreen::BindCallback(std::function<void(GameScreenType, TetrisEvents)> fn)
{
	mScreenCallbackFunction = std::bind(fn, std::placeholders::_1, std::placeholders::_2);
}

void OptionsScreen::PostInitialize()
{
	// Isaretci oku ilk ayara tasiyalim
	mCurrentSettingsIndex = 0;
	this->UpdateSelection();

	// Muzik seviyesini guncelleyelim
	this->UpdateMusicLevel();
}

void OptionsScreen::UpdateSelection()
{
	mArrowSprite.setPosition(mArrowPositionList[mCurrentSettingsIndex]);
	auto spriteRect = mArrowSprite.getLocalBounds();
	mArrowSprite.setOrigin(spriteRect.left + spriteRect.width / 2.0f,
		spriteRect.top + spriteRect.height / 2.0f);
}

void OptionsScreen::UpdateMusicLevel()
{
	if (mOptionsData.mMusicLevel > 100)
	{
		mOptionsData.mMusicLevel = 100;
	}
	else if (mOptionsData.mMusicLevel < 0)
	{
		mOptionsData.mMusicLevel = 0;
	}
	cout << "Muzik seviyesi : " << mOptionsData.mMusicLevel << endl;
	
	// Muzik degerine gore imleci ayarlayalim
	mCursorValue = (mOptionsData.mMusicLevel / 5) * mCursorRangeIncrement;

	mCursorSprite.setPosition(mCursorReferencePosition 
		+ sf::Vector2f{ mCursorValue, 0 });
}

OptionsScreen::OptionsScreen(GameOptionsData& val)
	: mOptionsData(val)
{

}

void OptionsScreen::Display()
{
	// Pencereyi siyaha temizle
	mWindow->clear(sf::Color::Black);

	mWindow->draw(mBackGroundSprite);

	mWindow->draw(mArrowSprite);
	mWindow->draw(mCursorSprite);

	if (true == mOptionsData.mSoundFxEnabled)
	{
		mCheckSprite.setPosition(mSFXReferencePosition);
		mWindow->draw(mCheckSprite);
	}

	if (true == mOptionsData.mChildModeEnabled)
	{
		mCheckSprite.setPosition(mChildModeReferencePosition);
		mWindow->draw(mCheckSprite);
	}

	// Her seyi cizelim
	mWindow->display();
}

GameScreenType OptionsScreen::GetGameScreenType()
{
	return GameScreenType::eGAME_SCREEN_TYPE_OPTIONS;
}

void OptionsScreen::SetWindow(sf::RenderWindow* window)
{
	mWindow = window;
}
