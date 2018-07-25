/**
 * \file    TetrisEvents.h
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

enum class TetrisEvents
{
	eTETRIS_EVENT_SPLASH_KEY_PRESSED,
	eTETRIS_EVENT_MENU_START_GAME,
	eTETRIS_EVENT_MENU_SETTINGS,
	eTETRIS_EVENT_MENU_SCORES,
	eTETRIS_EVENT_MENU_QUIT_GAME,
	eTETRIS_EVENT_SAVE_SCORES,
	eTETRIS_EVENT_RESET_SCORES,
	eTETRIS_EVENT_GAME_RETURN_MENU,
	eTETRIS_EVENT_GAME_RECORD_SCORE,
};