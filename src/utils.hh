#ifndef UTILS_HH
#define UTILS_HH

#include <qicon.h>

namespace utils
{
    /**
     * Returns an icon based off the input icon number.
     *
     * \param icon Int number corresponding to the desired icon
     * \return QIcon object of the desired icon
     */
    QIcon get_icon(int icon);

    /**
     * Calculates factors for the desired value so that the factors are as near to
     * each other as possible.
     *
     * \param value Int Input value to calulate factor of
     * \param smaller_factor UInt byref specified for the smaller factor
     * \param larger_factor UInt byref specified for the larger factor
     * \return bool true for success, false for failure
     */
    bool calculate_factors(int value, unsigned& smaller_factor, 
        unsigned& larger_factor);

    const QString ICON_SUFFIX = ":/icons/";
    const QString ICON_FILE_TYPE = ".png";
    const int MAX_CARD_COUNT = 30;

    //enum to easily to refer to different icons
    enum icons
    {
        none,
        back,
        bird,
        bunny,
        camel,
        cat,
        chicken,
        cow,
        dog,
        donkey,
        duck,
        elephant,
        flamingo,
        horse,
        lizard,
        llama,
        monke,
        panda,
        pig,
        rooster,
        sheep,
        squirrel
    };

    //file names of all the icons. names are in same order as the enum above
    static const std::vector<QString> file_names = { 
        "", "card_back", "bird", "bunny", "camel", "cat", "chicken", "cow",
        "dog", "donkey", "duck", "elephant", "flamingo", "horse", "lizard",
        "llama", "monke", "panda", "pig", "rooster", "sheep", "squirrel" };
};

#endif // UTILS_HH
