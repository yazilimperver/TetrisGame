/**
 * \file    TetrisFigure.h
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

#include <cstdint>
#include <memory>

#include <TetrisTable.h>
#include <FigureType.h>

#include <SFML/Graphics.hpp>

/// Bu sinif tetriste bulunan her bir tasi temsil eder onnun ile ilgili butun islevler bunun uzerinde
class TetrisFigure
{
public:
    // Gerekli olusturma calismalari
    bool Initialize();

    // Gorsellestirme metodu
    void Draw(sf::RenderWindow& window);

    // Figur tipini donelim
    FigureType GetFigureType() const;
    
    // Figur tipini atayalim
    void SetFigureType(FigureType val);

    // Yeni tas olusturma metodu
    void NewFigure(uint32_t range = gTetrisFigureCount);

    // Bu metot saat yonunde tetris tasinin dondurulmasini saglar
    // Referans noktasi olarak her zaman ikinci tasin yeri baz alinir
    // ref: https://www.siggraph.org/education/materials/HyperGraph/modeling/mod_tran/2drota.htm
    // ref: http://danceswithcode.net/engineeringnotes/rotations_in_2d/rotations_in_2d.html
    void RotateClockwise();

    // Tetrisi tasini hareket ettirme
    void MoveFigure(int32_t dx, int32_t dy = 0);

    // Ilgili figurun parcasini don
    int32_t GetTilePartCount() const;
    sf::Vector2i GetTilePart(size_t index) const;

    sf::Sprite* GetTileSprite();
protected:
    //! Kullanilan figur tipi (rengini ayrica tutmak yerine bu bilgi kullanilabilir
    FigureType mFigureType;

    //! Tetris parcalarinin dagilimi (x, y) cinsinden ifade edilmektedir
    std::vector<sf::Vector2i> mTileArrangement;

    //! Tetris taslari icin kullanacagimiz resme referans
    std::string mTexturePath = "Data/tiles.png";
    sf::Texture mTileTexture;
    sf::Sprite mTileSprite;
};