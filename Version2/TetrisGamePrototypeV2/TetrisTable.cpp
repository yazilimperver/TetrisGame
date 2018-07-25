#include <TetrisTable.h>
#include <iostream>

#include <TetrisFigure.h>

#include <GameDifficulty.h>

bool TetrisTable::Initialize()
{
    if (!mTableTexture.loadFromFile(mTexturePath.c_str()))
    {
        std::cout << "Texture yuklenmesinde hata. Texture ismi:" << mTexturePath << std::endl;
        return false;
    }
    else
    {
        mTableSprite.setTexture(mTableTexture);
        return true;
    }    
}

void TetrisTable::Clear()
{
    for (int i = 0; i < mGridRowCount; i++)
    {
        for (int j = 0; j < mGridColCount; j++)
        {
            mField[i][j] = 0;
        }
    }
}

void TetrisTable::Draw(sf::RenderWindow& window)
{
    if (nullptr != mTileSprite)
    {
        // Display things on screen
        window.draw(mTableSprite);

        // Daha once tahtaya inen taslar
        for (int i = 0; i < mGridRowCount; i++)
        {
            for (int j = 0; j < mGridColCount; j++)
            {
                if (mField[i][j] == 0)
                    continue;

                mTileSprite->setTextureRect(sf::IntRect(mField[i][j] * gTetrisFigureSize, 0, gTetrisFigureSize, gTetrisFigureSize));
                mTileSprite->setPosition(j * gTetrisFigureSizeF, i * gTetrisFigureSizeF);

                // offset
                mTileSprite->move(gTableInitialOffset);
                window.draw(*mTileSprite);
            }
        }
    }
}

void TetrisTable::InitializeTable(GameDifficulty difficulty)
{
    // Verilen zorluk seviyesine gore masayi allocate et
    switch (difficulty)
    {
    case GameDifficulty::eGAME_DIFFICULT_EASY:
        break;
    case GameDifficulty::eGAME_DIFFICULT_HARD:
        break;
    case GameDifficulty::eGAME_DIFFICULT_MEDIUM:
    default:
    {
        mGridRowCount = gMediumDifficultyTableRowCount;
        mGridColCount = gMediumDifficultyTableColCount;

        // matrix initialization
        mField = std::vector <std::vector<int32_t> >{ static_cast<uint32_t>(gMediumDifficultyTableRowCount),
            std::vector<int32_t>(static_cast<uint32_t>(gMediumDifficultyTableColCount), 0) };
    }
        break;
    }
}

bool TetrisTable::CheckIfOk(const TetrisFigure& figure)
{
    sf::Vector2i tilePart;
    int32_t partCount = figure.GetTilePartCount();

    for (int32_t i = 0; i < partCount; ++i)
    {
        tilePart = figure.GetTilePart(i);

        if (tilePart.x < 0
            ||
            tilePart.x >= mGridColCount
            ||
            tilePart.y >= mGridRowCount)
        {
            return false;
        }
        else if (mField[tilePart.y][tilePart.x])
        {
            return false;
        }
    }

    return true;
}

uint32_t TetrisTable::CheckLines()
{
    int32_t k = mGridRowCount - 1;
    int32_t count = 0;
    uint32_t removedLineCount = 0;

    for (int32_t i = mGridRowCount - 1; i > 0; i--)
    {
        count = 0;

        // Herhangi bir satir doldu mu kontrolü
        for (int32_t j = 0; j < mGridColCount; j++)
        {
            if (mField[i][j])
                count++;

            mField[k][j] = mField[i][j];
        }

        // Hala boslar var
        if (count < mGridColCount)
            k--;
        else
        {
            // Satir getti, puani ekle
            ++removedLineCount;
        }
    }

    return removedLineCount;
}

void TetrisTable::AddTetrisFigure(const TetrisFigure& figure)
{
    int32_t colorNum = 1 + static_cast<int32_t>(figure.GetFigureType());
    int32_t partCount = figure.GetTilePartCount();
    sf::Vector2i tilePart;

    for (int32_t i = 0; i < partCount; i++)
    {
        tilePart = figure.GetTilePart(i);
        mField[tilePart.y][tilePart.x] = colorNum;
    }
}

void TetrisTable::SetTileSprite(sf::Sprite* val)
{
    mTileSprite = val;
}

bool TetrisTable::IsGameOver()
{
    bool isGameOver = false;

    for (int i = 0; i < mGridColCount; i++)
    {
        if (mField[0][i] || mField[1][i])
        {
            isGameOver = true;
            break;
        }
    }

    return isGameOver;
}
