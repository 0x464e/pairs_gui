#ifndef UTILS_HH
#define UTILS_HH

#include <qicon.h>
#include <vector>
#include <algorithm>

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
     * Calculates factors for the desired value so that the factors
     * are as near to each other as possible.
     *
     * \param value Int Input value to calulate factor of
     * \param smaller_factor UInt byref specified for the smaller factor
     * \param larger_factor UInt byref specified for the larger factor
     * \return bool true for success, false for failure
     */
    bool calculate_factors(int value, unsigned& smaller_factor, 
        unsigned& larger_factor);

    /**
     * Gets the specified amount of random card icon pairs.
     *
     * \param card_count int count of cards in the playing field
     * \return int vector of card icons
     */
    std::vector<int> get_random_card_icons(int card_count);

    /**
     * Converts a seconds to a min:sec format string.
     *
     * \param seconds uint second amount
     * \return QString time format
     */
    QString seconds_to_time_string(unsigned seconds);

    QString icon_name_to_plural(int icon);

    const QString ICON_SUFFIX = ":/icons/";
    const QString ICON_FILE_TYPE = ".png";
    const int MAX_CARD_COUNT = 30;
    const int ANIMAL_ICON_COUNT = 20;

    //enum to easily refer to different icons
    //first element has to be none, and second has to be the cards' backside
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
