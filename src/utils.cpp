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

    for (auto i = 1u; i * i <= value; ++i)
    {
        if (value % i == 0)
        {
            smaller_factor = i;
        }
    }
    larger_factor = value / smaller_factor;
    
    return true;
}