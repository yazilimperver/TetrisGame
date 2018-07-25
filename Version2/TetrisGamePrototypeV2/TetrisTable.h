/**
 * \file    TetrisTable.h
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
#include <vector>

#include <TetrisDefinitions.h>

#include <SFML/Graphics.hpp>

class TetrisFigure;

enum class GameDifficulty;

class TetrisTable
{
public:

    // Uygulama ilklendirme isleri
    bool Initialize();

    // Tabloyu sifirla
    void Clear();

    // Cizim islemleri
    void Draw(sf::RenderWindow& window);

    // Verilen zorluk seviyesine gore oyunuun masasini olustur
    void InitializeTable(GameDifficulty difficulty);

    // Bu metot ile ilgili tetris tasinin;
    // - Masanin sinirlari icinde mi?
    // - Herhangi bir tas ile cakisiyor mu?
    // olup olmadigi kontrol edilir?
    bool CheckIfOk(const TetrisFigure& figure);

    // Bu metot ile mevcut taslari kontrol edip tamamen dolan satirlari silecegiz
    // Kac tane doldu ise o donulur ve bu skora yansitilir
    uint32_t CheckLines();

    // Saglanan tetris tasini tahtaya ekle
    void AddTetrisFigure(const TetrisFigure& figure);
    void SetTileSprite(sf::Sprite* val);

    // Oyun bitti mi
    bool IsGameOver();
protected:

    //! Mevcut tahta icin kullanilan satir ve sutun sayilari
    int32_t mGridRowCount = gMediumDifficultyTableRowCount;
    int32_t mGridColCount = gMediumDifficultyTableColCount;

    //! Tetris alaninda her bir paftaya karsilik gelen kisimlara iliskin renk indeksleri
    //! 0 ise bos farkli bir deger is renklidir.
    std::vector< std::vector<int32_t>> mField;

    //! Tahtaya iliskin arkaplan doku ve resmi
    std::string mTexturePath = "Data/TetrisBackground2.png";
    sf::Texture mTableTexture;
    sf::Sprite mTableSprite;

    //! Reference to tile sprite
    sf::Sprite* mTileSprite = nullptr;
};