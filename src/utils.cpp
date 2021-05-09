#include <random>
#include "utils.hh"

QIcon utils::get_icon(const int icon)
{
    //The requested icon is guaranteed to be found when this function is
    //only passed arguments via the icons enum.
    return QIcon(ICON_SUFFIX + file_names.at(icon) + ICON_FILE_TYPE);
}

bool utils::calculate_factors(const int value, unsigned& smaller_factor, 
    unsigned& larger_factor)
{
    //Card number has to be even and between [2, 30]
    if(value < 2 || value > MAX_CARD_COUNT || value % 2 != 0)
    {
        return false;
    }

    for (auto i = 1; i * i <= value; ++i)
    {
        if (value % i == 0)
        {
            smaller_factor = i;
        }
    }
    larger_factor = value / smaller_factor;
    return true;
}

std::vector<int> utils::get_random_card_icons(const int card_count)
{
    //generate numbers 2 ... ANIMAL_ICON_COUNT + 1 to an int vector
    //(these values correspond to valid card icons in the icon enum)
    std::vector<int> icons(ANIMAL_ICON_COUNT);
    auto i = 1;
    std::generate(icons.begin(), icons.end(), [&] { return ++i; });

    //shuffle elements with a mersenne twister engine seeded with 
    //a true random number number from std::random_device (if supported)
    std::shuffle(icons.begin(), icons.end(), std::mt19937(69));
    //std::shuffle(icons.begin(), icons.end(), std::mt19937(std::random_device()()));

    //remove elements from the vector so that only card_count / 2 elements exist
    icons.erase(icons.begin(), icons.begin() + (ANIMAL_ICON_COUNT - card_count / 2));

    //duplicate the vector with itself to get one pair of each
    const auto old_size = icons.size();
    icons.reserve(2 * old_size);
    std::copy_n(icons.begin(), old_size, std::back_inserter(icons));

    //shuffle one last time
    std::shuffle(icons.begin(), icons.end(), std::mt19937(69));
    //std::shuffle(icons.begin(), icons.end(), std::mt19937(std::random_device()()));

    return icons;
}
