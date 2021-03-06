// Copyright (C) 1997, 1999-2001, 2008 Nathan Lamont
// Copyright (C) 2015 The Antares Authors
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

#include <GLFW/glfw3.h>

#include <sfz/sfz.hpp>
#include <time.h>

#include "config/file-prefs-driver.hpp"
#include "config/preferences.hpp"
#include "config/ledger.hpp"
#include "data/scenario-list.hpp"
#include "game/sys.hpp"
#include "glfw/video-driver.hpp"
#include "sound/openal-driver.hpp"
#include "ui/flows/master.hpp"

using sfz::String;
using sfz::args::store;
using sfz::args::store_const;
using sfz::range;

namespace args = sfz::args;
namespace io = sfz::io;

namespace antares {

String application_path() {
    return String("./data");
}

void main(int argc, const char* argv[]) {
    args::Parser parser(argv[0], "Runs Antares");

    parser.add_argument("--help", help(parser, 0))
        .help("display this help screen");

    String error;
    if (!parser.parse_args(argc - 1, argv + 1, error)) {
        print(io::err, format("{0}: {1}\n", parser.name(), error));
        exit(1);
    }

    FilePrefsDriver prefs;

    const auto& scenario = sys.prefs->scenario_identifier();
    bool have_scenario = false;
    ScenarioList l;
    for (auto i: range(l.size())) {
        const auto& entry = l.at(i);
        if (entry.identifier == scenario) {
            if (entry.installed) {
                have_scenario = true;
                break;
            } else {
                print(io::err, format("{0}: factory scenario not installed\n\n", parser.name()));
                print(io::err, format("Please run antares-install-data\n", parser.name()));
                exit(1);
            }
        }
    }
    if (!have_scenario) {
        print(io::err, format("{0}: {1}: scenario not installed\n", parser.name(), scenario));
        exit(1);
    }

    DirectoryLedger ledger;
    OpenAlSoundDriver sound;
    GLFWVideoDriver video;
    video.loop(new Master(time(NULL)));
}

}  // namespace antares

int main(int argc, const char* argv[]) {
    antares::main(argc, argv);
    return 0;
}
