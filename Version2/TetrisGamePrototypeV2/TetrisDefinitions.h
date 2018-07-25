/**
 * \file    TetrisDefinitions.h
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
#include <string>
#include <SFML/System/Vector2.hpp>

// Uygulamaya iliskin sabitler
constexpr uint32_t gWindowWidth = 480;
constexpr uint32_t gWindowHeight = 640;
const sf::Vector2f gTableInitialOffset{ 158.0F, 109.0F };
const std::string gWindowTitle = "Tetris Oyunu v2.0";

constexpr int32_t gMediumDifficultyTableRowCount = 26U;
constexpr int32_t gMediumDifficultyTableColCount = 16U;

constexpr float    gTetrisFigureSizeF = 17.0F;
constexpr uint32_t gTetrisFigureSize = 17U;

// Bizim tetrisimizde olan tas sayisi
constexpr uint32_t gTetrisFigureCount = 8U;

// Her bir tasin inmesi icin beklenecek olan sure
constexpr float gDelay = 0.8F;

// Tetris taslarini asagidaki gibi bir gride yerlestiriyoruz. x pozisyonu icin % y icin ise /2 kullanilabilir
// 0-1
// 2-3
// 4-5
// 6-7
constexpr int32_t gTetrisFigures[gTetrisFigureCount][5] =
{
    // Ilk sayi ilgili figurdeki tas sayisi, ikincisi ise taslarin dizilimi
	4, 1, 3, 5, 7, // I
	4, 2, 3, 4, 5, // O
    4, 2, 4, 5, 7, // Z
    4, 3, 5, 4, 6, // S
    4, 3, 5, 4, 7, // T
    4, 2, 3, 5, 7, // L
    4, 3, 5, 7, 6, // J
    3, 4, 6, 7     // Corner
};