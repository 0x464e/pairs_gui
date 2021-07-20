# Animals Memory Game

The final C++ project for my university's C++ programming course.

A simple command line version of this game was created as the very first project of C++ course.  
The command line version can be found [here](https://github.com/0x464e/pairs).

---

This program creates a memory game, where a desired amount of players compete against each other in a classic card flipping memory game. The cards have images of animals, find a pair to score a point.

The game starts off by asking the desired amount of playing field cards and player names. After that, the used cards and player order are randomized.  
The used rng is seeded by a true random number from std::random_device <sub><sup>(if supported)</sup></sub>.  
There can be any even number of cards between two and 40. The upper limit of 40 only comes from the amount of animal icons (20) the program has.  
The playing field is constructed so that the row and column count are as near to each other as possible.

Each round the player in turn turns two cards (by clicking on them).  
Everyone can see the cards, and should look at them trying to keep in mind where each card is.  
If the player got a matching card pair, the card pair is removed from the playing field, the player scores a point, and they get to continue their turn.  
Otherwise, the cards get turned backside up again and the turn goes over to the next player.  
The large textbox acts as a log which tells everything relevant to what's happening in the game.

Animal icons included in the game are as follows:  
bird, bunny, camel, cat, chicken, cow, dog, donkey, duck, elephant, flamingo,
horse, lizard, llama, monke, panda, pig, rooster, sheep, and squirrel

The games ends when the playing field is empty of cards.  
The program prints out the winner and their score (amount of card pairs collected), or in case of a tie, it prints out the names of the tied players and their score.

![image](https://i.imgur.com/0ZfdEgQ.gif)

## Notes about the program and its implementation

The main idea when creating the program was possible future expandability.  
I tried to make everything with the thought in mind that it'd be easy to expand upon it in the future. E.g the game will work with any amount of players even though as I'm writing this, I still don't know if I'm going to bother to implement the ability to select the player count.  
Update: I added it last minute, everything went smoothly as expected.

Using a custom signal for passing the icon in my CardButton class may seem redundant when I could just as well implement a `get_icon()` method to the class. But I wanted to try out emitting custom signals with arguments in Qt and it worked out quite well.  
Was a nice learning exercise.

Some design choices, such as deducing parameter types in generic lambdas, require C\+\+14 features.  
I would've wanted to use even more modern C++ features for some design choices, but wasn't sure if it was allowed in this project.

## Dependencies

The GUI is written with Qt, so Qt binaries are required for compiling/building.  
Qt is found at https://www.qt.io/.

## Building

### Building with Qt Creator
This is going to be the easiest alternative and I'd probably recommend this if you want everything to work easily.  
Qt creator is Qt's own IDE.
* Clone this repository  
`git clone https://github.com/0x464e/pairs_gui`
* Install Qt (and Qt Creator) from https://www.qt.io/
* Launch Qt Creator
* Open an existing project from the `.pro` file in this repository and configure with the defaults settings will suffice
    * Choose Build → Build Project "pairs_gui"
    * **Or** just run it directly with Qt Creator by hitting `Run` in the bottom left corner
* By default the build output will be found just outside your project's directory in a build folder
* Run `./pairs_gui` in that folder to run the program

### Build with Visual Studio
This is doable as well, but you still need to install Qt, of course.
* Clone this repository  
`git clone https://github.com/0x464e/pairs_gui`
* Install Qt from https://www.qt.io/
* Install Qt Visual Studio Tools from the [Visual Studio Marketplace](https://marketplace.visualstudio.com/items?itemName=TheQtCompany.QtVisualStudioTools-19123) and follow their setup instructions
* Launch Visual Studio and open the `.pro` in this repository file by choosing  
Qt VS Tools → Open Qt Project File (.pro)...
* Build a release or just run it straight with Visual studio
* The resulting Windows binary is found in your release/ folder and can be ran standalone as long as your Qt binaries are found in your PATH  
To be able to run it without depending on having Qt installed, see [Deployment](#deployment)

### Building in the command line
A valid option as long as your build environment is set up correctly.  
But still, Qt of course needs to be installed
* Clone this repository  
`git clone https://github.com/0x464e/pairs_gui`
* Install Qt from https://www.qt.io/
* Ensure that your Qt binaries are found in your PATH  
<sub><sup>(So add your Qt's `bin/` folder to path, if it isn't there already.)</sup></sub>
* Add the following line to the `.pro` file found in this repository:  
`INCLUDEPATH += .`
* Run  
    ```
    qmake -makefile
    make
    ```
* Run the resulting binary  
`./pairs_gui`


## Deployment

Deployment instructions are found from the Qt documentation  
https://doc.qt.io/qt-5/deployment.html
