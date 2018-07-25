/**
 * \file    GameScreenType.h
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

/// Mevcut oyun icin kullanacagimiz ekranlari ifade etmek icin kullanacagiz
/// Toplamda bes farkli ekran planliyoruz. Bunlarin her birini basit bir state machine
/// state leri olarak dusunebilirsiniz.
enum class GameScreenType
{
   eGAME_SCREEN_TYPE_SPLASH,
   eGAME_SCREEN_TYPE_MENU,
   eGAME_SCREEN_TYPE_GAME,
   eGAME_SCREEN_TYPE_HIGH_SCORES,
   eGAME_SCREEN_TYPE_OPTIONS,
   eGAME_SCREEN_TYPE_PAUSE,
   eGAME_SCREEN_TYPE_GAME_OVER,
};
