# Copyright 2022 splitkb.com <support@splitkb.com>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

SRC += funcs/isInArr.c
SRC += funcs/preInit.c
SRC += funcs/rgbOffset.c
SRC += funcs/rgbOperations.c
SRC += funcs/keypressOperations.c
SRC += funcs/m2sSync.c
SRC += funcs/limitTo8Bit.c

OLED_ENABLE = yes
SPLIT_KEYBOARD = yes
RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = WS2812
RGBLIGHT_ENABLE = no


