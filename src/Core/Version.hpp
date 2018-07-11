#pragma once

#include <string>

struct Version
{
    static const Version& GetVersion();

    int Major, Minor, Patch;
    char Revision[13];
    char Codename[64];

    std::string ToString() const
    {
        return "v" + std::to_string(Major) + "." + std::to_string(Minor) + "." + std::to_string(Patch) + " (" + std::string(Revision) + ") " + std::string(Codename);
    }
};
