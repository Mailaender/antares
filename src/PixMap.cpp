// Ares, a tactical space combat game.
// Copyright (C) 1997, 1999-2001, 2008 Nathan Lamont
// 
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

#include "PixMap.hpp"

#include <algorithm>
#include <Quickdraw.h>
#include "ColorTable.hpp"

namespace antares {

PixMap::PixMap(int width, int height)
        : _bounds(0, 0, width, height),
          _colors(new ColorTable(256)),
          _bytes(new unsigned char[width * height]) { }

PixMap::~PixMap() {
    delete[] _bytes;
}

const Rect& PixMap::bounds() const {
    return _bounds;
}

const ColorTable& PixMap::colors() const {
    return *_colors;
}

int PixMap::row_bytes() const {
    return _bounds.right;
}

const uint8_t* PixMap::bytes() const {
    return _bytes;
}

uint8_t* PixMap::mutable_bytes() {
    return _bytes;
}

ColorTable* PixMap::mutable_colors() {
    return _colors;
}

void PixMap::resize(const Rect& new_bounds) {
    PixMap new_pix_map(new_bounds.width(), new_bounds.height());
    Rect transfer = _bounds;
    transfer.clip_to(new_bounds);
    CopyBits(this, &new_pix_map, transfer, transfer);
    _bounds = new_bounds;
    std::swap(_bytes, new_pix_map._bytes);
}

void PixMap::set(int x, int y, uint8_t color) {
    _bytes[y * _bounds.right + x] = color;
}

uint8_t PixMap::get(int x, int y) const {
    return _bytes[y * _bounds.right + x];
}

}  // namespace antares