#include "Util.hpp"

#include <SFML/Graphics/Font.hpp>

#if defined(SFML_SYSTEM_LINUX)
#include <fontconfig/fontconfig.h>
#endif

using namespace Core;

bool findSystemFont(std::string* fontPath, const std::string& name, const std::string& style = "Regular");

extern sf::Font& Util::GetDefaultFont()
{
    static sf::Font s_defaultFont;
    static std::array<std::tuple<std::string, std::string>, 5> s_fontList {{
        std::make_tuple("Arial", "Regular"),
        std::make_tuple("DejaVu Sans", "Book"),
        std::make_tuple("Liberation Sans", "Regular"),
        std::make_tuple("Bitstream Vera Sans", "Roman"),
        std::make_tuple("Unifont", "Medium")
    }};

    std::string fontPath;
    if (findSystemFont(&fontPath, "Arial"))
        s_defaultFont.loadFromFile(fontPath);
    else
        s_defaultFont.loadFromFile("fallback.otf") || s_defaultFont.loadFromFile("fallback.ttf");

    return s_defaultFont;
}

#if defined(SFML_SYSTEM_LINUX)
typedef char wildchar;
struct FontConfigData_t
{
    FontConfigData_t()
    {
        config = FcInitLoadConfigAndFonts();
    }

    FcConfig* config;
} FontConfigData;
#elif defined(SFML_SYSTEM_WINDOWS)
typedef wchar_t wildchar;
#endif

bool wildcmp(const wildchar* wildcard, const wildchar* string)
{
    while ((*string) && (*wildcard) != '*')
    {
        if ((*wildcard != *string) && (*wildcard != '?'))
            return false;

        ++wildcard;
        ++string;
    }

    const wildchar *cp = nullptr, *mp = nullptr;

    while (*string)
    {
        if (*wildcard == '*')
        {
            if (!*++wildcard)
                return true;

            mp = wildcard;
            cp = string + 1;
        }
        else if ((*wildcard == *string) || (*wildcard == '?'))
        {
            ++wildcard;
            ++string;
        }
        else
        {
            wildcard = mp;
            string = cp++;
        }
    }

    while (*wildcard == '*')
        ++wildcard;

    return !*wildcard;
}

bool findSystemFont(std::string* p_fontPath, const std::string& fontName, const std::string& fontStyle)
{
    auto& fontPath = *p_fontPath;
#if defined(SFML_SYSTEM_LINUX)

    FcPattern* pat = FcPatternCreate();
    FcObjectSet* os = FcObjectSetBuild(FC_FAMILY, FC_STYLE, FC_FILE, (char*)nullptr);
    FcFontSet* fs = FcFontList(FontConfigData.config, pat, os);

    for (int i = 0; fs && i < fs->nfont; ++i)
    {
        FcPattern* font = fs->fonts[i];
        FcChar8 *file, *style, *family;
        if (FcPatternGetString(font, FC_FAMILY, 0, &family) == FcResultMatch &&
            FcPatternGetString(font, FC_STYLE, 0, &style) == FcResultMatch &&
            FcPatternGetString(font, FC_FILE, 0, &file) == FcResultMatch)
        {
            std::string tmp((char*)file);

            std::reverse(tmp.begin(), tmp.end());
            tmp = tmp.substr(0, 4);
            if (tmp != "ftt." && tmp != "fto.")
                continue;

            if (wildcmp(fontName.c_str(), (char*)family) &&
                wildcmp(fontStyle.c_str(), (char*)style))
                fontPath = std::string((char*)file);
        }
    }

    if (fs) FcFontSetDestroy(fs);
    if (os) FcObjectSetDestroy(os);
    if (pat) FcPatternDestroy(pat);

#elif defined(SFML_SYSTEM_WINDOWS)

#endif
    return false;
}
