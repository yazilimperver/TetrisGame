#include <GameScreen.h>
#include <GameScreenType.h>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <TetrisDefinitions.h>
#include <GameDifficulty.h>
#include <GameOptionsData.h>
#include <RandomNumberGenerator.h>

#include <iostream>

GameScreen::GameScreen(const GameOptionsData& val)
	: mOptions{val}
{

}


GameScreenType GameScreen::GetGameScreenType()
{
    return GameScreenType::eGAME_SCREEN_TYPE_GAME;
}

bool GameScreen::Initialize()
{
    bool initializationStatus = false;

    if (nullptr != mWindow)
    {
        initializationStatus = true;

        // Tetris tahtasi ile ilgili ilklendirmeler
        initializationStatus = mTetrisTable.Initialize();

        if (false == initializationStatus)
        {
            std::cout << "Tetris tahtasinin ilklendirmesinde hata!" << std::endl;
        }
        else
        {
            mTetrisTable.InitializeTable(GameDifficulty::eGAME_DIFFICULT_MEDIUM);
        }

        // Tetris figuru ile ilgili ilklendirmeler
        if (true == initializationStatus)
        {
            initializationStatus = mCurrentTetrisFigure.Initialize();

            if (false == initializationStatus)
            {
                std::cout << "Tetris figurunun ilklendirilmesinde hata!" << std::endl;
            }
            else
            {
                // Burada ilgili tetris figurunu tahta cizimi icin gecirelim
                mTetrisTable.SetTileSprite(mCurrentTetrisFigure.GetTileSprite());
            }
        }

		// Gerekli font referansi atanmis mi
		if (nullptr != mFont)
		{
			mGameScore.SetFont(mFont);
			mGameDuration.SetFont(mFont);
			mGameLevel.SetFont(mFont);
		}
		else
		{
			initializationStatus = true;
		}

        // Oyun puan ve sure nesnelerinin ilklendirilmesi
        if (true == initializationStatus)
        {
            mGameScore.Initialize();
            mGameDuration.Initialize();
			mGameLevel.Initialize();
        }

        // Oyun bitis mesaji ve sure metin ilklendirmeleri
        if (true == initializationStatus)
        {
            /// Oyun bitis mesaji
            mGameOverText.setPosition({ gWindowWidth / 2, gWindowHeight / 2 });
            mGameOverText.setFont(*mFont);
            mGameOverText.setCharacterSize(20);
            mGameOverText.setFillColor(sf::Color::Green);
            mGameOverText.setString("                         Oyun Bitti!\nDevam etmek icin Space Bar'a basiniz");

            // Metini merkezlemek icin
            mGameOverTextRect = mGameOverText.getLocalBounds();
            mGameOverText.setOrigin(mGameOverTextRect.left + mGameOverTextRect.width / 2.0f,
                mGameOverTextRect.top + mGameOverTextRect.height / 2.0f);

            // Metin arka plani
            mTextBackgroundRect = sf::RectangleShape{ sf::Vector2f{ mGameOverTextRect.width + 10, mGameOverTextRect.height + 10 } };
            mTextBackgroundRect.setFillColor(sf::Color(0, 0, 0, 200));
            mTextBackgroundRect.setPosition({ gWindowWidth / 2, gWindowHeight / 2 });
            mTextBackgroundRect.setOrigin(mGameOverTextRect.left + mGameOverTextRect.width / 2.0f,
                mGameOverTextRect.top + mGameOverTextRect.height / 2.0f);
        }


        // Yeni tetris tasini olusturelim
        if (true == initializationStatus)
        {
            mCurrentTetrisFigure.SetFigureType( static_cast<FigureType>(RandomNumberGenerator::GenerateRandom(0, gTetrisFigureCount-1)));
        }
		
		if (true == initializationStatus)
		{
			if (!mGameMusic.openFromFile(mGameMusicPath))
			{
				std::cout << "Muzik yuklenmesinde hata. Ses dosya ismi:" << mGameMusicPath << std::endl;
			}
			else
			{
				mGameMusic.setLoop(true);
			}
			
			mGameOverSound.Initialize();
			mFigureRotateSound.Initialize();
			mFigureBlockHitSound.Initialize();
			mFigureSingleLineRemovalSound.Initialize();
			mFigureMultiLineRemovalSound.Initialize();
		}
    }

    return initializationStatus;
}

void GameScreen::SetWindow(sf::RenderWindow* window)
{
    mWindow = window;
}

void GameScreen::PreFrame()
{
    // Her dongu icin kullanilacak olan degiskenleri sifirlayalim
    this->ResetTickParameters();
}

std::string GameScreen::GetName()
{
	return "OYUN EKRANI";
}

void GameScreen::SetFont(const sf::Font* val)
{
	mFont = val;
}

void GameScreen::BindCallback(std::function<void(GameScreenType, TetrisEvents)> fn)
{
	mScreenCallbackFunction = std::bind(fn, std::placeholders::_1, std::placeholders::_2);
}

void GameScreen::PostInitialize()
{
	// kullanilabilecek olan tas sayisini ayarlayalim
	if (true == mOptions.mChildModeEnabled)
	{
		mFigureCount = 2;
	}
	else
	{
		mFigureCount = gTetrisFigureCount;
	}

	// Ilk tasi uret
	mCurrentTetrisFigure.NewFigure(mFigureCount);

	// Muzigi cal
	mGameMusic.setVolume(static_cast<float>(mOptions.mMusicLevel));
	mGameMusic.play();

	mGameDuration.Reset();

	// Seviye ayarlamalari
	mCurrentDelay = gDelay;
	mTimeSinceStart = 0;
	mGameLevel.Reset();
}

int32_t GameScreen::ObtainLastScore()
{
	return mGameScore.GetScore();
}

void GameScreen::Input()
{
    // Handle events
    // Pencere olayi nesnesi
    sf::Event event;

	bool resetGameState = false;
    while (mWindow->pollEvent(event))
    {
        // Window closed or escape key pressed: exit
        // Pencere kapandi ya da esc ye basildi
		if ((event.type == sf::Event::Closed))
		{
			mScreenCallbackFunction(this->GetGameScreenType(), TetrisEvents::eTETRIS_EVENT_SAVE_SCORES);

			mWindow->close();
			
			// Muzigi durdur
			mGameMusic.stop();

			break;
		}

        if((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
		{
			if (true != mIsGameOver)
			{
				resetGameState = true;

				mIsGameOver = false;

				// Muzigi durdur
				mGameMusic.stop();

				mScreenCallbackFunction(this->GetGameScreenType(), TetrisEvents::eTETRIS_EVENT_SAVE_SCORES);
				mScreenCallbackFunction(this->GetGameScreenType(), TetrisEvents::eTETRIS_EVENT_GAME_RETURN_MENU);
			}

            break;
        }

        // Space key tusuna 
        if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Space))
        {
            if (true == mIsGameOver)
			{
				resetGameState = true;
				std::cout << "Space Bar'a basildi" << std::endl;

				mScreenCallbackFunction(this->GetGameScreenType(), TetrisEvents::eTETRIS_EVENT_GAME_RETURN_MENU);
				mIsGameOver = false;
            }
        }

        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Up)
            {
                mRotationInitiated = true;
            }
            else if (event.key.code == sf::Keyboard::Left)
            {
                mDX = -1;
            }
            else if (event.key.code == sf::Keyboard::Right)
            {
                mDX = 1;
            }
        }
    }

	if (true == resetGameState)
	{
		// Tahtayi temizleyelim
		mTetrisTable.Clear();

		// Yeni tetris tasini olustur
		mCurrentTetrisFigure.NewFigure(mFigureCount);

		// Zamani sifirla
		mGameDuration.Reset();

		// Puani sifirla
		mGameScore.Reset();
	}

    // Oyun bitmedi ise oyun mantigini kosturmaya devam edelim
    if (false == mIsGameOver)
    {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			mMoveTimeInSecond = 0.05f;
		}
    }
}

void GameScreen::Update(float timeSinceLastTick)
{
    // Gecen zamana ekle
    mTimeSinceLastMove += timeSinceLastTick;
	mTimeSinceStart += timeSinceLastTick;

    // Oyun bitmedi ise oyun mantigini kosturmaya devam edelim
    if (false == mIsGameOver)
    {
		if ((mTimeSinceStart >= mLevelUpTime) && mGameLevel.GetLevel() < 17)
		{
			mGameLevel.IncrementLevel();
			if (true == mOptions.mChildModeEnabled)
			{
				mCurrentDelay -= 0.025F;
			}
			else
			{
				mCurrentDelay -= 0.05F;
			}

			mTimeSinceStart = 0.0F;
		}

        TetrisFigure oldFigure = mCurrentTetrisFigure;

        // Sag sol hareket var mi?
        if (mDX != 0)
        {
			mCurrentTetrisFigure.MoveFigure(mDX);

			// Hareket sonrasi sinirlara dayandiysak eski haline getir
			if (false == mTetrisTable.CheckIfOk(mCurrentTetrisFigure))
			{
				mCurrentTetrisFigure = oldFigure;
			}
        }

        // Tetris figuru cevirme hareket
        if (true == mRotationInitiated)
        {
			mCurrentTetrisFigure.RotateClockwise();

			// Dondurme sonrasi sinirlara dayandiysak eski haline getir
			if (false == mTetrisTable.CheckIfOk(mCurrentTetrisFigure))
			{
				mCurrentTetrisFigure = oldFigure;
			}
			else
			{
				if (true == mOptions.mSoundFxEnabled)
					mFigureRotateSound.Play();
			}
        }

        // Hizli indirmeye basildi mi?
        if (mTimeSinceLastMove >= mMoveTimeInSecond)
        {
            int32_t dy = 1;
            TetrisFigure oldFigure = mCurrentTetrisFigure;
            mCurrentTetrisFigure.MoveFigure(0, dy);

			// Her bir satir icin bir puan
			mLastRowCount++;

			if (mLastRowCount == mRowCountPerScore)
			{
				mGameScore.AddScore(1);
				mLastRowCount = 0;
			}

            // Artik bu tas durdu mu?
            if (false == mTetrisTable.CheckIfOk(mCurrentTetrisFigure))
            {
				if (true == mOptions.mSoundFxEnabled)
					mFigureBlockHitSound.Play();

                // Durdu ise bunu tabloya ekle
                // Bir onceki tasi ekliyoruz conku bir asagi inis mumkun degil
                mTetrisTable.AddTetrisFigure(oldFigure);

                // Yeni tetris tasini olusturelim
                mCurrentTetrisFigure.NewFigure(mFigureCount);
            }

            mTimeSinceLastMove = 0;
        }

        // Silecegimiz tetris satiri var mi?
        uint32_t removedLineCount = mTetrisTable.CheckLines();

        if (0 != removedLineCount)
        {
			if (removedLineCount == 4)
			{
				mGameScore.AddScore(40 + 5 * mGameLevel.GetLevel());
				if (true == mOptions.mSoundFxEnabled)
					mFigureMultiLineRemovalSound.Play();
			}
			else if (removedLineCount == 3)
			{
				mGameScore.AddScore(20 + 3 * mGameLevel.GetLevel());
				if (true == mOptions.mSoundFxEnabled)
					mFigureSingleLineRemovalSound.Play();
			}
			else if (removedLineCount == 2)
			{
				mGameScore.AddScore(10 + 2 * mGameLevel.GetLevel());
				if (true == mOptions.mSoundFxEnabled)
					mFigureSingleLineRemovalSound.Play();
			}
			else
			{
				mGameScore.AddScore(5 + mGameLevel.GetLevel());				
				if (true == mOptions.mSoundFxEnabled)
					mFigureSingleLineRemovalSound.Play();
			}
        }

        // Oyun bitti mi kontrolu
        mIsGameOver = mTetrisTable.IsGameOver();

		if (true == mIsGameOver)
		{
			// Muzigi durdur
			mGameMusic.stop();

			// Oyun bitis muzigi
			mGameOverSound.Play();
		}

        // Oyun zaman kontrolu
        mGameDuration.Update();
    }
}

void GameScreen::Display()
{
    // Pencereyi temizle
    mWindow->clear(sf::Color::White);

    // Tetris tablosunu cizelim
    mTetrisTable.Draw(*mWindow);

    // Tetris tasini cizelim
    mCurrentTetrisFigure.Draw(*mWindow);

    // Oyun bitti yazisi
    if (true == mIsGameOver)
    {
        mWindow->draw(mTextBackgroundRect);
        mWindow->draw(mGameOverText);
    }

    // Oyun puan gosterimi
    mGameScore.Draw(*mWindow);

    // Zaman gosterimi
    // Oyun bitince zaman ilerlemesin
    if (false == mIsGameOver)
    {
        mGameDuration.Draw(*mWindow);
    }

	// Oyun seviyesi
	mGameLevel.Draw(*mWindow);

    // Her seyi cizelim
    mWindow->display();
}

void GameScreen::ResetTickParameters()
{
    // Bunu da sifirliyoruz cunku adam hizli indirmesi icin bunun uzerinden bekleme suresi degistiriliyor
    mMoveTimeInSecond = mCurrentDelay;
    mRotationInitiated = false;
    mDX = 0;
}

