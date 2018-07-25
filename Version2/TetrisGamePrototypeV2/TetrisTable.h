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