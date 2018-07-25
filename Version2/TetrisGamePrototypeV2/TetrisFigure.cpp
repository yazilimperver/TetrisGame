#include <TetrisFigure.h>
#include <iostream>
#include <RandomNumberGenerator.h>

bool TetrisFigure::Initialize() 
{
    if (!mTileTexture.loadFromFile(mTexturePath.c_str()))
    {
        std::cout << "Texture yuklenmesinde hata. Texture ismi:" << mTexturePath << std::endl;
        return false;
    }
    else
    {
        mTileSprite.setTexture(mTileTexture);

        return true;
    }

}

void TetrisFigure::Draw(sf::RenderWindow& window)
{
    int32_t partCount = mTileArrangement.size();
    int32_t colorNum = 1 + static_cast<int32_t>(mFigureType);
    sf::Vector2i tilePart;

    for (int i = 0; i < partCount; i++)
    {
        mTileSprite.setTextureRect(sf::IntRect(colorNum * gTetrisFigureSize, 0, gTetrisFigureSize, gTetrisFigureSize));
        mTileSprite.setPosition(mTileArrangement[i].x * gTetrisFigureSizeF, mTileArrangement[i].y * gTetrisFigureSizeF);

        //offset
        mTileSprite.move(gTableInitialOffset);
        window.draw(mTileSprite);
    }
}

FigureType TetrisFigure::GetFigureType() const
{

    return mFigureType;
}

void TetrisFigure::SetFigureType(FigureType val)
{
    mFigureType = val;

    // Ilgili tas tipini diziden ilgili indeksi bulmak icin kullaniyoruz
    uint32_t figureIndex = static_cast<uint32_t>(mFigureType);

    // On tas dizilimini silelim
    mTileArrangement.clear();

    // Ilk eleman her zaman adeti tutacak
    mTileArrangement.resize(gTetrisFigures[figureIndex][0]);

    // Taslari yerlestirelim
    for (int32_t i = 1; i <= gTetrisFigures[figureIndex][0]; i++)
    {
        mTileArrangement[i - 1].x = gTetrisFigures[figureIndex][i] % 2 + gMediumDifficultyTableColCount / 2 - 1;
        mTileArrangement[i - 1].y = gTetrisFigures[figureIndex][i] / 2;
    }
}

void TetrisFigure::NewFigure(uint32_t range)
{
    this->SetFigureType(static_cast<FigureType>(RandomNumberGenerator::GenerateRandom(0, range - 1)));
}

void TetrisFigure::RotateClockwise()
{
    // bu tarz taslar icin dondurme yapmayacagiz
    if (mFigureType != FigureType::eFIGURE_TYPE_O)
    {
        // Dondurme referans noktasi
        sf::Vector2i refPoint = mTileArrangement[1];

        // Dondurme
        for (size_t i = 0; i < mTileArrangement.size(); ++i)
        {
            int32_t x = mTileArrangement[i].y - refPoint.y;
            int32_t y = mTileArrangement[i].x - refPoint.x;

            mTileArrangement[i].x = refPoint.x - x;
            mTileArrangement[i].y = refPoint.y + y;
        }
    }
}

void TetrisFigure::MoveFigure(int32_t dx, int32_t dy /*= 0*/)
{
    for (size_t i = 0; i < mTileArrangement.size(); ++i)
    {
        mTileArrangement[i].x += dx;
        mTileArrangement[i].y += dy;
    }
}

int32_t TetrisFigure::GetTilePartCount() const
{
    return mTileArrangement.size();
}

sf::Vector2i TetrisFigure::GetTilePart(size_t index) const
{
    if (index < mTileArrangement.size())
    {
        return mTileArrangement[index];
    }
    else
    {
        return sf::Vector2i{ 0, 0 };
    }
}

sf::Sprite* TetrisFigure::GetTileSprite()
{
    return &mTileSprite;
}
