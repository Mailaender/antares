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

#ifndef ANTARES_IMAGE_DRIVER_HPP_
#define ANTARES_IMAGE_DRIVER_HPP_

#include "sfz/ReadSource.hpp"
#include "sfz/WriteTarget.hpp"

namespace antares {

class ArrayPixMap;
class PixMap;

class ImageDriver {
  public:
    virtual ~ImageDriver();

    virtual void read(sfz::ReadSource in, ArrayPixMap* pix) = 0;
    virtual void write(sfz::WriteTarget out, const PixMap& pix) = 0;

    static ImageDriver* driver();
    static void set_driver(ImageDriver* driver);
};

}  // namespace antares

#endif  // ANTARES_IMAGE_DRIVER_HPP_
