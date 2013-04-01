// Copyright (C) 1997, 1999-2001, 2008 Nathan Lamont
// Copyright (C) 2008-2012 The Antares Authors
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
// License along with Antares.  If not, see http://www.gnu.org/licenses/

#ifndef ANTARES_UI_INTERFACE_HANDLING_HPP_
#define ANTARES_UI_INTERFACE_HANDLING_HPP_

#include <vector>
#include <sfz/sfz.hpp>

#include "data/interface.hpp"
#include "drawing/interface.hpp"

namespace antares {

struct Scenario;

enum PlayAgainResult {
    PLAY_AGAIN_QUIT,
    PLAY_AGAIN_RESTART,
    PLAY_AGAIN_RESUME,
    PLAY_AGAIN_SKIP,
};

bool BothCommandAndQ( void);
void update_mission_brief_point(
        LabeledRect *dataItem, int32_t whichBriefPoint, const Scenario* scenario,
        coordPointType *corner, int32_t scale, Rect *bounds, std::vector<inlinePictType>& inlinePict,
        Rect& highlight_rect, std::vector<std::pair<Point, Point>>& lines, sfz::String& text);
void CreateObjectDataText(sfz::String* text, short id);
void Replace_KeyCode_Strings_With_Actual_Key_Names(sfz::String* text, short resID, size_t padTo);

}  // namespace antares

#endif // ANTARES_UI_INTERFACE_HANDLING_HPP_
