#pragma once

#include <string>

/// Enum tipi icin on tanimlama
enum class GameScreenType;

namespace sf
{
    class RenderWindow;
	class Font;
}

/// Temel ekran sinifi. Bu sinif oyun ekranlarina iliskin temel mantiklari tanimlar
class BaseScreen
{
public:
    // Oyun ekran tipini don
    virtual GameScreenType GetGameScreenType() = 0;

    // Ilklendirmeler
    // Basarili ise TRUE basariz ise FALSE don
    virtual bool Initialize() = 0;

    // Her bir dongunun basinda yapilmasini bekledigimiz isler
    virtual void PreFrame() = 0;

    // Girdileri isleyecegimi metot
    virtual void Input() = 0;

    // Oyun mantigini gercekleyecegimiz metot.
	// Saniye cinsinden gecen zaman
    virtual void Update(float timeSinceLastTick) = 0;

    // Gorsellestirmeleri gerceklestirecegimi metot
    virtual void Display() = 0;

    // Cizim icin kullanilacak olan pencere sinifini gecirir
    virtual void SetWindow(sf::RenderWindow* window) = 0;

	// Ilgili ekranin metin tabanli ismi (log ve benzeri isler icin kullanabiliriz)
	virtual std::string GetName() = 0;

	// Font nesnesine bir referansi gecirelim
	virtual	void SetFont(const sf::Font* font) = 0;

	// Ekran ilk calistirilmadan once cagrilacak metot
	virtual void PostInitialize() = 0;
};
