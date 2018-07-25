#include <MenuScreen.h>
#include <GameScreenType.h>

#include <TetrisDefinitions.h>


#include <iostream>
using namespace std;

bool MenuScreen::Initialize()
{
	bool initializationStatus = false;

	if (nullptr != mWindow
		&&
		nullptr != mFont)
	{
		if (!mMenuTexture.loadFromFile(mMenuImagePath.c_str()))
		{
			cout << "Texture yuklenmesinde hata. Texture ismi:" << mMenuImagePath << endl;
		}
		else
		{
			// Menu sprite ilklendirme
			auto sizeOfTexture = mMenuTexture.getSize();
			
			mMenuReferencePoint.x = 220;
			mMenuReferencePoint.y = 64;

			mMenuSprite.setTexture(mMenuTexture);
			mMenuSprite.setPosition(mMenuReferencePoint);
			mMenuSprite.setScale(0.5, 0.5);

			sf::IntRect cropRect{ 0, 146, 565, 711 };
			mMenuSprite.setTextureRect(cropRect);

			// Menu secim cercevesi
			mMenuSelectionSprite.setTexture(mMenuTexture);
			
			sf::IntRect selectionCropRect{ 0, 0, 565, 138 };
			mMenuSelectionSprite.setTextureRect(selectionCropRect);
			mMenuSelectionSprite.setPosition(mMenuReferencePoint);
			mMenuSelectionSprite.setScale(0.5, 0.5);

			initializationStatus = true;
		}


		if (true == initializationStatus && !mBackGroundTexture.loadFromFile(mBackGroundImagePath.c_str()))
		{
			cout << "Texture yuklenmesinde hata. Texture ismi:" << mBackGroundImagePath << endl;
		}
		else
		{
			// Logo ilklendirme
			auto sizeOfTexture = mBackGroundTexture.getSize();

			mBackGroundSprite.setTexture(mBackGroundTexture);
			mBackGroundSprite.setPosition({0, 0});

			initializationStatus = true;
		}

		if (true == initializationStatus)
		{			
			mMenuTraverseAudio.Initialize();
			mMenuSelectionAudio.Initialize();
		}
	}

	return true;
}

void MenuScreen::PreFrame()
{
}

void MenuScreen::Input()
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
				mScreenCallbackFunction(this->GetGameScreenType(), TetrisEvents::eTETRIS_EVENT_SAVE_SCORES);
				mWindow->close();

				break;
			}

			if (event.key.code == sf::Keyboard::Up)
			{
				mMenuIndex--;

				if (mMenuIndex < 0)
				{
					mMenuIndex = 3;
				}

				mMenuTraverseAudio.Play();
				mMenuSelectionSprite.setPosition(mMenuReferencePoint + sf::Vector2f{ 0.0F, 94.0F * mMenuIndex });
			}
			else if (event.key.code == sf::Keyboard::Down)
			{
				mMenuIndex++;

				if (mMenuIndex > 3)
				{
					mMenuIndex = 0;
				}

				mMenuTraverseAudio.Play();
				mMenuSelectionSprite.setPosition(mMenuReferencePoint + sf::Vector2f{ 0.0F, 94.0F * mMenuIndex });
			}
			else if ((event.key.code == sf::Keyboard::Space)
				||
				(event.key.code == sf::Keyboard::Return))
			{
				// Menude secili elemani calistir
				if (0 == mMenuIndex)
				{
					mScreenCallbackFunction(this->GetGameScreenType(), TetrisEvents::eTETRIS_EVENT_MENU_START_GAME);
				}
				else if (1 == mMenuIndex)
				{
					mScreenCallbackFunction(this->GetGameScreenType(), TetrisEvents::eTETRIS_EVENT_MENU_SETTINGS);
				}
				else if (2 == mMenuIndex)
				{
					mScreenCallbackFunction(this->GetGameScreenType(), TetrisEvents::eTETRIS_EVENT_MENU_SCORES);
				}
				else if (3 == mMenuIndex)
				{
					mScreenCallbackFunction(this->GetGameScreenType(), TetrisEvents::eTETRIS_EVENT_MENU_QUIT_GAME);
				}

				mMenuSelectionAudio.Play();
			}
		}
	}
}

void MenuScreen::Update(float timeSinceLastTick)
{
}

std::string MenuScreen::GetName()
{
	return "MENU EKRANI";
}

void MenuScreen::SetFont(const sf::Font* val)
{
	mFont = val;
}

void MenuScreen::BindCallback(std::function<void(GameScreenType, TetrisEvents)> fn)
{
	mScreenCallbackFunction = std::bind(fn, std::placeholders::_1, std::placeholders::_2);
}

void MenuScreen::PostInitialize()
{
}

void MenuScreen::Display()
{
	// Pencereyi siyaha temizle
	mWindow->clear(sf::Color::Black);

	mWindow->draw(mBackGroundSprite);

	mWindow->draw(mMenuSprite);

	mWindow->draw(mMenuSelectionSprite);

	// Her seyi cizelim
	mWindow->display();
}

GameScreenType MenuScreen::GetGameScreenType()
{
	return GameScreenType::eGAME_SCREEN_TYPE_MENU;
}

void MenuScreen::SetWindow(sf::RenderWindow* window)
{
	mWindow = window;
}
