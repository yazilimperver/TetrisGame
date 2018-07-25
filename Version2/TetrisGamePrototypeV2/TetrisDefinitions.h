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