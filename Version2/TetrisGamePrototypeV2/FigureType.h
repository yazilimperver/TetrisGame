/**
 * \file    FigureType.h
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

/// Tetris oyunu icerisinde sunulan tetris tas tiplerini ifade eder
enum class FigureType
{
	eFIGURE_TYPE_I = 0,
	eFIGURE_TYPE_O = 1,
	eFIGURE_TYPE_Z = 2,
	eFIGURE_TYPE_S = 3,
	eFIGURE_TYPE_T = 4,
	eFIGURE_TYPE_L = 5,
	eFIGURE_TYPE_J = 6,
    eFIGURE_TYPE_CORNER = 7
};