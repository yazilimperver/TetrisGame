#include <TetrisGame.h>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <TetrisDefinitions.h>
#include <GameDifficulty.h>

#include <SplashScreen.h>
#include <GameScreen.h>

#include <RandomNumberGenerator.h>

#include <chrono>  // chrono::system_clock
#include <ctime>   // localtime
#include <sstream> // stringstream
#include <iomanip> // put_time
#include <fstream>

#include <algorithm>
#include <iostream>
#include <sstream>
using namespace std;

TetrisGame::TetrisGame() 
{
}

void TetrisGame::InitializeCommonEntities()
{
	// Uygulamaya ilişkin pencereyi oluşturalım
	mWindow.create(sf::VideoMode(gWindowWidth, gWindowHeight, 32), gWindowTitle.c_str(), sf::Style::Titlebar | sf::Style::Close);

	if (false == mWindow.isOpen())
	{
		cout << "Pencerenin acilmasinda hata!" << endl;
	}
	else
	{
		mInitializationStatus = true;
	}

	// Fontu yukleyelim
	if (true == mInitializationStatus)
	{
		// Metinler icin kullanacagimiz font
		if (!mFont.loadFromFile(mFontPath.c_str()))
		{
			cout << "Font yuklenmesinde hata!" << endl;
			mInitializationStatus = false;
		}
	}

	if (true == mInitializationStatus)
	{
		// Metinler icin kullanacagimiz font
		if (!mGameFont.loadFromFile(mGameFontPath.c_str()))
		{
			cout << "Oyun fontu yuklenmesinde hata!" << endl;
			mInitializationStatus = false;
		}
	}

	// Yuksek skor dosyasini oku
	RestoreScores();
}

void ReturnCurrentDateTimeString(HighScoreData& highScoreData)
{
	auto now = std::chrono::system_clock::now();
	auto in_time_t = std::chrono::system_clock::to_time_t(now);

	stringstream ss;
	tm buf;
	localtime_s(&buf, &in_time_t);
	ss << put_time(&buf, "Saat: %H:%M, Puan");

	highScoreData.mHour = buf.tm_hour;
	highScoreData.mMinute = buf.tm_min;
	highScoreData.mText = ss.str();
}

void TetrisGame::ScreenEvent(GameScreenType originatedScreen, TetrisEvents eventArg)
{
	if (mRegisteredScreens.find(originatedScreen) != mRegisteredScreens.end())
	{
		cout << "\"" << mRegisteredScreens[originatedScreen]->GetName() << "\" ekranindan " << static_cast<int>(eventArg) << " nolu olay alindi!" << endl;

		switch (eventArg)
		{
			case TetrisEvents::eTETRIS_EVENT_SPLASH_KEY_PRESSED:
			{
				if (originatedScreen != GameScreenType::eGAME_SCREEN_TYPE_SPLASH)
				{
					cout << "Alinan olay icin beklenmedik kaynak ekran. Ekran kod: " << static_cast<int>(originatedScreen) << " Olay No:" << static_cast<int>(eventArg) << endl;
				}
				else
				{
					// Menu ekranina gecelim
					mCurrentScreen = mRegisteredScreens[GameScreenType::eGAME_SCREEN_TYPE_MENU].get();
					mCurrentScreen->PostInitialize();
				}
			}
			break;

			case TetrisEvents::eTETRIS_EVENT_MENU_START_GAME:
			{
				if (originatedScreen != GameScreenType::eGAME_SCREEN_TYPE_MENU)
				{
					cout << "Alinan olay icin beklenmedik kaynak ekran. Ekran kod: " << static_cast<int>(originatedScreen) << " Olay No:" << static_cast<int>(eventArg) << endl;
				}
				else
				{
					// Menu ekranina gecelim
					mCurrentScreen = mRegisteredScreens[GameScreenType::eGAME_SCREEN_TYPE_GAME].get();
					mCurrentScreen->PostInitialize();
				}
			}
			break;

			case TetrisEvents::eTETRIS_EVENT_MENU_SCORES:
			{
				if (originatedScreen != GameScreenType::eGAME_SCREEN_TYPE_MENU)
				{
					cout << "Alinan olay icin beklenmedik kaynak ekran. Ekran kod: " << static_cast<int>(originatedScreen) << " Olay No:" << static_cast<int>(eventArg) << endl;
				}
				else
				{
					// Skor ekranina gecelim
					mCurrentScreen = mRegisteredScreens[GameScreenType::eGAME_SCREEN_TYPE_HIGH_SCORES].get();
					mCurrentScreen->PostInitialize();
				}
			}
			break;

			case TetrisEvents::eTETRIS_EVENT_MENU_SETTINGS:
			{
				if (originatedScreen != GameScreenType::eGAME_SCREEN_TYPE_MENU)
				{
					cout << "Alinan olay icin beklenmedik kaynak ekran. Ekran kod: " << static_cast<int>(originatedScreen) << " Olay No:" << static_cast<int>(eventArg) << endl;
				}
				else
				{
					// Ayarlar ekranina gecelim
					mCurrentScreen = mRegisteredScreens[GameScreenType::eGAME_SCREEN_TYPE_OPTIONS].get();
					mCurrentScreen->PostInitialize();
				}
			}
			break;

			case TetrisEvents::eTETRIS_EVENT_MENU_QUIT_GAME:
			{
				if (originatedScreen != GameScreenType::eGAME_SCREEN_TYPE_MENU)
				{
					cout << "Alinan olay icin beklenmedik kaynak ekran. Ekran kod: " << static_cast<int>(originatedScreen) << " Olay No:" << static_cast<int>(eventArg) << endl;
				}
				else
				{
					// bu olay olustugun skorlari kaydet
					this->SaveScores();

					mWindow.close();
				}
			}
			break;

			case TetrisEvents::eTETRIS_EVENT_RESET_SCORES:
			{
				if (originatedScreen != GameScreenType::eGAME_SCREEN_TYPE_OPTIONS)
				{
					cout << "Alinan olay icin beklenmedik kaynak ekran. Ekran kod: " << static_cast<int>(originatedScreen) << " Olay No:" << static_cast<int>(eventArg) << endl;
				}
				else
				{
					cout << "Yuksek skor tablosu sifirlandi!" << endl;
					mHighScoreTable.clear();
				}
			}
			break;

			case TetrisEvents::eTETRIS_EVENT_SAVE_SCORES:
			{
				// bu olay olustugun skorlari kaydet
				this->SaveScores();
			}
			break;

			case TetrisEvents::eTETRIS_EVENT_GAME_RETURN_MENU:
			{
				if (originatedScreen != GameScreenType::eGAME_SCREEN_TYPE_GAME
					&&
					originatedScreen != GameScreenType::eGAME_SCREEN_TYPE_HIGH_SCORES
					&&
					originatedScreen != GameScreenType::eGAME_SCREEN_TYPE_OPTIONS)
				{
					cout << "Alinan olay icin beklenmedik kaynak ekran. Ekran kod: " << static_cast<int>(originatedScreen) << " Olay No:" << static_cast<int>(eventArg) << endl;
				}
				else
				{
					mCurrentScreen = mRegisteredScreens[GameScreenType::eGAME_SCREEN_TYPE_MENU].get();

					if (originatedScreen == GameScreenType::eGAME_SCREEN_TYPE_GAME)
					{
						// Skorlari tarihlere gore ekleyelim
						int32_t score = dynamic_cast<GameScreen*>(mRegisteredScreens[GameScreenType::eGAME_SCREEN_TYPE_GAME].get())->ObtainLastScore();
						
						HighScoreData scoreData;
						ReturnCurrentDateTimeString(scoreData);

						if (20 == mHighScoreTable.size())
						{
							// Eger gelen skor mevcut en dusukten az ise son puani silelim yoksa hic bir sey yapma
							if ((mHighScoreTable.begin())->first < score)
							{
								mHighScoreTable.erase(mHighScoreTable.begin());
								mHighScoreTable.insert(pair<int32_t, HighScoreData>(score, scoreData));
							}
						}
						else
						{
							mHighScoreTable.insert(pair<int32_t, HighScoreData>(score, scoreData));
						}
					}
				}
			}
			break;
		}
	}
	else
	{
		cout << "Tanimlanmayan bir ekrandan olay iletildi. Ekran kod: " << static_cast<int>(originatedScreen) << endl;
	}
}

void TetrisGame::SaveScores()
{
	ofstream highScoreFile(mScoreFile, std::ofstream::binary);

	if (true == highScoreFile.is_open())
	{
		// Once muzik seviyesini yazalim
		highScoreFile.write(reinterpret_cast<char*>(&mGameOptions.mMusicLevel), sizeof(int32_t));

		// Sonra ses efekt durumlarini
		int32_t sfxEnabled = mGameOptions.mSoundFxEnabled;
		highScoreFile.write(reinterpret_cast<char*>(&sfxEnabled), sizeof(int32_t));

		// Sonra cocuk modu durumlari
		int32_t childModeEnabled = mGameOptions.mChildModeEnabled;
		highScoreFile.write(reinterpret_cast<char*>(&childModeEnabled), sizeof(int32_t));

		// Once kac skor oldugunu yazalim
		int32_t scoreTableSize = mHighScoreTable.size();
		highScoreFile.write(reinterpret_cast<char*>(&scoreTableSize), sizeof(int32_t));

		// sonra sira ile skorlari yazalim
		int32_t hour = 0;
		int32_t minute = 0;
		int32_t scoreItem = 0;
		
		for (auto& score : mHighScoreTable)
		{
			scoreItem = score.first;
			hour = score.second.mHour;
			minute = score.second.mMinute;

			// skor, saat, dakika
			highScoreFile.write(reinterpret_cast<char*>(&scoreItem), sizeof(int32_t));
			highScoreFile.write(reinterpret_cast<char*>(&hour), sizeof(int32_t));
			highScoreFile.write(reinterpret_cast<char*>(&minute), sizeof(int32_t));
		}

		highScoreFile.flush();
		highScoreFile.close();

		cout << "Skor dosyasina " << scoreTableSize << " skor yazildi!" << endl;
	}
	else
	{
		cout << "Skor dosyasinin " << mScoreFile << " yazilmasinda hata olustu!" << endl;
	}
}

void TetrisGame::RestoreScores()
{
	ifstream highScoreFile(mScoreFile, std::ifstream::binary);

	if (true == highScoreFile.is_open())
	{
		// basa git
		highScoreFile.seekg(0);

		// Once muzik seviyesini okuyalim
		highScoreFile.read(reinterpret_cast<char*>(&mGameOptions.mMusicLevel), sizeof(int32_t));

		// Sonra ses efekt durumlarini
		int32_t sfxEnabled = 0;
		highScoreFile.read(reinterpret_cast<char*>(&sfxEnabled), sizeof(int32_t));

		mGameOptions.mSoundFxEnabled = (sfxEnabled == 1);

		// Sonra cocuk mod durumlarini
		int32_t childModeEnabled = 0;
		highScoreFile.read(reinterpret_cast<char*>(&childModeEnabled), sizeof(int32_t));
		
		mGameOptions.mChildModeEnabled = (childModeEnabled == 1);

		// Once kac skor oldugunu ogrenelim
		int32_t scoreTableSize = 0;
		highScoreFile.read(reinterpret_cast<char*>(&scoreTableSize), sizeof(int32_t));

		// sonra sira ile skorlari okuyalim
		int32_t readScore = 0;
		HighScoreData highScoreData;

		for (int32_t i = 0; i < scoreTableSize; ++i)
		{
			// skor, saat, dakika
			highScoreFile.read(reinterpret_cast<char*>(&readScore), sizeof(int32_t));
			highScoreFile.read(reinterpret_cast<char*>(&highScoreData.mHour), sizeof(int32_t));
			highScoreFile.read(reinterpret_cast<char*>(&highScoreData.mMinute), sizeof(int32_t));

			highScoreData.mText = "Saat " + std::to_string(highScoreData.mHour) + ":" + std::to_string(highScoreData.mMinute) + ", Puan";

			mHighScoreTable.insert(pair<int32_t, HighScoreData>(readScore, highScoreData));
		}

		highScoreFile.close();

		cout << "Skor dosyasindan " << scoreTableSize << " skor okundu!" << endl;
	}
	else
	{
		cout << "Skor dosyasinin " << mScoreFile << " acilmasinda hata olustu!" << endl;
	}
}

bool TetrisGame::Initialize()
{	
	this->InitializeCommonEntities();

	if (true == mInitializationStatus)
	{
		// Butun ekranlara iliskin ilklendirmeleri gerceklestirelim
		auto splashScreen = make_unique<SplashScreen>();
		auto menuScreen = make_unique<MenuScreen>();
		auto gameScreen = make_unique<GameScreen>(mGameOptions);
		auto highScoresScreen = make_unique<HighScoresScreen>(mHighScoreTable);
		auto optionsScreen = make_unique<OptionsScreen>(mGameOptions);

		// uye metotlarin gecirilmesi icin kullandigimiz yontem bu
		splashScreen->BindCallback(bind(&TetrisGame::ScreenEvent, this, placeholders::_1, placeholders::_2));
		menuScreen->BindCallback(bind(&TetrisGame::ScreenEvent, this, placeholders::_1, placeholders::_2));
		gameScreen->BindCallback(bind(&TetrisGame::ScreenEvent, this, placeholders::_1, placeholders::_2));
		highScoresScreen->BindCallback(bind(&TetrisGame::ScreenEvent, this, placeholders::_1, placeholders::_2));
		optionsScreen->BindCallback(bind(&TetrisGame::ScreenEvent, this, placeholders::_1, placeholders::_2));

		mRegisteredScreens[GameScreenType::eGAME_SCREEN_TYPE_SPLASH] = move(splashScreen);
		mRegisteredScreens[GameScreenType::eGAME_SCREEN_TYPE_MENU] = move(menuScreen);
		mRegisteredScreens[GameScreenType::eGAME_SCREEN_TYPE_GAME] = move(gameScreen);
		mRegisteredScreens[GameScreenType::eGAME_SCREEN_TYPE_HIGH_SCORES] = move(highScoresScreen);
		mRegisteredScreens[GameScreenType::eGAME_SCREEN_TYPE_OPTIONS] = move(optionsScreen);

		// Ekranlari ilkendirelim
		auto itr = mRegisteredScreens.begin();

		while (itr != mRegisteredScreens.end() && true == mInitializationStatus)
		{
			itr->second->SetWindow(&mWindow);
			itr->second->SetFont(&mGameFont);

			mInitializationStatus = itr->second->Initialize();

			if (false == mInitializationStatus)
			{
				cout << "\"" << itr->second->GetName() << "\" ekraninin ilkendirilmesinde hata olustu!" << endl;
			}
			else
			{
				cout << "\"" << itr->second->GetName() << "\" ekrani basarili sekilde ilklendirildi!" << endl;
			}
			itr++;
		}

		if (true == mInitializationStatus)
		{
			// Ilk ekrani atayalim
			mCurrentScreen = mRegisteredScreens[GameScreenType::eGAME_SCREEN_TYPE_SPLASH].get();
		}
	}

    return mInitializationStatus;
}

void TetrisGame::Run()
{
    while (mWindow.isOpen())
    {
        // Bir onceki dongu kosumundan bu yana gecen zamani al
        float elapsedTimeSinceLastTick = mClock.getElapsedTime().asSeconds();

        if (nullptr != mCurrentScreen)
        {
            // Zamani bastan baslat
            mClock.restart();

            // Tick baslangici
            mCurrentScreen->PreFrame();

            // Girdileri oku
            mCurrentScreen->Input();

            // Oyun mantigini kosturalim
            mCurrentScreen->Update(elapsedTimeSinceLastTick);

            // Cizim islerini gerceklestir
            mCurrentScreen->Display();
        }
    }
}
