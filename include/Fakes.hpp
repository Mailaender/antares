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

#ifndef ANTARES_FAKES_HPP_
#define ANTARES_FAKES_HPP_

#include "AresGlobalType.hpp"

template <typename T>
#define DISALLOW_COPY_AND_ASSIGN(CLASS) \
  private: \
    CLASS(const CLASS&); \
    CLASS& operator=(const CLASS&);

class scoped_ptr {
  public:
    scoped_ptr() : _t(NULL) { }
    explicit scoped_ptr(T* t) : _t(t) { }

    ~scoped_ptr() { if (_t) delete _t; }

    T* operator->() { return _t; }
    T& operator*() { return _t; }

    void reset() { if (_t) { delete _t; _t = NULL; } }
    T* release() { T* t = _t; _t = NULL; return t; }

  private:
    T* _t;

    DISALLOW_COPY_AND_ASSIGN(scoped_ptr);
};

extern aresGlobalType* gAresGlobal;

#endif  // ANTARES_FAKES_HPP_
