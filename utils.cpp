#include <random>
#include "utils.hh"

QIcon utils::get_icon(const int icon)
{
    //The requested icon is guaranteed to be found when this function is
    //only passed arguments via the icons enum.
    return QIcon(ICON_SUFFIX + icon_names.at(icon) + ICON_FILE_TYPE);
}

void utils::calculate_factors(const int value, unsigned& smaller_factor,
                              unsigned& larger_factor)
{
    for (auto i = 1; i * i <= value; ++i)
    {
        if (value % i == 0)
        {
            smaller_factor = i;
        }
    }
    larger_factor = value / smaller_factor;
}

std::vector<int> utils::get_random_card_icons(const int card_count)
{
    //generate numbers 2 ... ANIMAL_ICON_COUNT + 1 to an int vector
    //(these values correspond to valid card icons in the icon enum)
    std::vector<int> icons(ANIMAL_ICON_COUNT);
    auto i = 1;
    std::generate(icons.begin(), icons.end(), [&] { return ++i; });

    //random shuffle elements with a mersenne twister engine seeded with 
    //a true random number from std::random_device (if supported)
    std::shuffle(icons.begin(), icons.end(),
                 std::mt19937(std::random_device()()));

    //remove elements from the vector so that only card_count / 2 elements exist
    icons.erase(icons.begin(),
                icons.begin() + (ANIMAL_ICON_COUNT - card_count / 2));

    //duplicate the vector with itself to get one pair of each
    const auto old_size = icons.size();
    icons.reserve(2 * old_size);
    std::copy_n(icons.begin(), old_size, std::back_inserter(icons));

    //shuffle one last time
    std::shuffle(icons.begin(), icons.end(),
                 std::mt19937(std::random_device()()));

    return icons;
}

QString utils::seconds_to_time_string(const unsigned seconds)
{
    //if time is over 999 mins 59 secs, just return 999:99 
    if (seconds >= 60000)
    {
        return "999:99";
    }

    //divide with precision loss to automatically floor
    const auto mins = QString::number(seconds / 60);
    //modulo to get remainder
    const auto secs = QString::number(seconds % 60);

    //add a zero if minute or second is a 1 digit number
    return QString((mins.length() == 1 ? "0" + mins : mins) + ":" 
        + (secs.length() == 1 ? "0" + secs : secs));
}

QString utils::icon_name_to_plural(const int icon)
{
    switch(icon)
    {
        //can be converted to plural just by adding an 's'
        case bird:
        case camel:
        case cat:
        case chicken:
        case cow:
        case dog:
        case donkey:
        case duck:
        case elephant:
        case flamingo:
        case horse:
        case lizard:
        case llama:
        case panda:
        case pig:
        case rooster:
        case squirrel:
        {
            //convert the first character to upper case
            //check for empty just so [0] access is safe, even though
            //it shouldn't be possible to be empty
            auto name = icon_names.at(icon);
            if (!name.isEmpty())
            {
                name[0] = name[0].toUpper();
            }
            return name + "s";
        }
        //unusual plural forms
        case bunny:
            return "Bunnies";
        case monke:
            return "Monke";
        case sheep:
            return "Sheep";
        default:
            return "";
    }
}

QString utils::player_vector_to_names(const std::vector<Player*>& players)
{
    const auto size = players.size();
    QString name_string = "";

    //size is one-based
    auto i = 1u;

    for (const auto player : players)
    {
        name_string += player->get_name();
        //if not the last element
        if (i != size)
        {
            //ternary, if next element is the last element
            name_string += ++i == size ? " and " : ", ";
        } 
    }

    return name_string;
}


std::vector<QString> utils::split(const QString& text, const char separator,
                               const bool include_empty)
{
    if (text.isEmpty())
    {
        return std::vector<QString> {""};
    }

    //vector to hold the separated parts
    std::vector<QString> parts{};
    //temp variable to hold the current part
    QString part = "";

    //loop through each character looking for occurrences of
    //the separator character
    for (const auto c : text)
    {
        //ignore carriage returns
        if (c == '\r')
        {
            continue;
        }

        if (c == separator)
        {
            //include empty parts only if asked for
            if (!part.isEmpty() || include_empty)
            {
                parts.push_back(part);
            }
            part = "";
            continue;
        }
        part += c;
    }

    //also add in whatever was after the last separator
    if (!part.isEmpty() || include_empty)
    {
        parts.push_back(part);
    }
    return parts;
}
