/**
 * \file    BaseScreen.h
 * \author  yazilimperver
 * \brief   This source code is developed for Tetris Game Prototype
 * Tetris V2

Copyright © 2018, Yazilimperver, www.yazilimperver.com

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
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
