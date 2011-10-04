// Copyright (C) 1997, 1999-2001, 2008 Nathan Lamont
// Copyright (C) 2008-2011 Ares Central
//
// This file is part of Antares, a tactical space combat game.
//
// Antares is free software: you can redistribute it and/or modify it
// under the terms of the Lesser GNU General Public License as published
// by the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Antares is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this program.  If not, see
// <http://www.gnu.org/licenses/>.

#ifndef ANTARES_UI_SCREENS_HELP_HPP_
#define ANTARES_UI_SCREENS_HELP_HPP_

#include <sfz/sfz.hpp>

#include "ui/interface-screen.hpp"

namespace antares {

class Sprite;

class HelpScreen : public InterfaceScreen {
  public:
    HelpScreen();
    ~HelpScreen();

    virtual void draw() const;

  protected:
    virtual void handle_button(int button);

  private:
    enum Item {
        DONE = 0,

        BOX = 1,
    };

    Rect _bounds;
    sfz::scoped_ptr<Sprite> _sprite;

    DISALLOW_COPY_AND_ASSIGN(HelpScreen);
};

}  // namespace antares

#endif  // ANTARES_UI_SCREENS_HELP_HPP_
