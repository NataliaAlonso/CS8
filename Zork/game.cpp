/*
Title: Zork!
Author: Natalia Alonso
Class: CS8, Spring 2012
*/

#include "game.h"

game::game()
{
    currentLevel = 0;                   // Current level = 0
    currentRoom = 0;                    // Current room = 0
    initializeRoomScripts();            // Initialize rooms
    initializeTables();                 // Initialize tables
    health = 3;                         // Player health = 3
    lantern = false;                    // Lantern is off by default
}

game::~game()
{                                       // Delete arrays
    delete [] below;
    delete [] above;
    delete [] maze;
    delete [] raboveRooms;
    delete [] rbelowRooms;
    delete [] rmazeRooms;
}

void game::initializeTables()           // Initialize all adjacency tables
{
    initializeAboveTables();            // Initialize above adjacency table
    initializeBelowTables();            // Initialize below adjacency table
    initializeMazeTables();             // Initialize maze adjacency table
}

void game::initializeBelowTables()      // Initialize below tables
{
    for(int i = 0; i < 35; i++)
    {
        for(int j = 0; j < 35; j++)
        {
            below[i][j] = NULL;
        }
    }

    below[0][1] = 'N';
    below[0][3] = 'S';
    //below[0][33] = 'U';               // Activate this when cyclops is killed
    //below[1][0] = 'S';                // Activate this when troll is killed
    //below[1][1] = 'S';
    //below[1][2] = 'W';                // Activate this when troll is killed
    //below[1][6] = 'E';                // Activate this when troll is killed
    below[2][1] = 'E';
    below[3][0] = 'N';
    below[3][3] = 'D';
    below[3][34] = 'E';
    below[5][4] = 'U';
    below[5][34] = 'S';
    below[6][1] = 'W';
    below[6][7] = 'D';
    below[6][16] = 'E';
    below[7][6] = 'U';
    below[7][8] = 'S';
    below[7][9] = 'E';
    below[8][7] = 'N';
    below[8][10] = 'E';
    below[8][16] = 'S';
    below[9][7] = 'W';
    below[9][10] = 'S';
    below[9][11] = 'E';
    below[9][15] = 'N';
    below[10][8] = 'W';
    below[10][9] = 'N';
    below[10][11] = 'E';
    below[10][17] = 'D';
    below[11][9] = 'W';
    below[11][10] = 'S';
    below[11][12] = 'N';
    below[11][14] = 'D';
    below[12][11] = 'S';
    below[12][13] = 'N';
    below[13][12] = 'S';
    below[14][11] = 'U';
    below[15][9] = 'E';
    below[15][15] = 'W';
    below[16][6] = 'W';
    below[16][8] = 'N';
    below[16][17] = 'E';
    below[16][21] = 'S';
    below[17][10] = 'U';
    below[17][16] = 'W';
    below[17][18] = 'E';
    below[17][27] = 'S';
    below[18][17] = 'W';
    below[18][19] = 'E';
    below[19][18] = 'W';
    below[19][20] = 'S';
    below[20][19] = 'N';
    below[21][16] = 'N';
    below[21][22] = 'S';
    below[22][21] = 'N';
    below[22][23] = 'W';
    below[22][24] = 'E';
    below[23][22] = 'N';
    below[23][24] = 'E';
    below[24][22] = 'N';
    below[24][23] = 'W';
    below[24][25] = 'D';
    below[25][24] = 'U';
    //below[25][26] = 'S';              // Activate after hades instance
    below[26][25] = 'N';
    below[27][17] = 'N';
    below[27][28] = 'E';
    below[28][27] = 'W';
    //below[28][29] = 'D';              // Activate when rope is tied to railing
    below[29][30] = 'D';
    below[30][29] = 'U';
    below[30][31] = 'D';
    below[30][32] = 'S';
    below[31][30] = 'U';
    below[32][24] = 'D';
    below[32][30] = 'N';
    below[33][0] = 'D';
    below[34][3] = 'W';
    below[34][5] = 'N';
}

void game::initializeAboveTables()      // Initialize above adjacency table
{
    for(int i = 0; i < 21; i++)
    {
        for(int j = 0; j < 21; j++)
        {
            above[i][j] = NULL;
        }
    }

    above[0][1] = 'N';
    above[0][9] = 'W';
    above[0][10] = 'S';
    above[1][0] = 'S';
    above[1][2] = 'N';
    above[1][4] = 'E';
    above[2][1] = 'S';
    above[2][3] = 'U';
    above[2][8] = 'N';
    above[2][9] = 'W';
    above[2][13] = 'E';
    above[3][2] = 'D';
    above[4][1] = 'N';
    //above[4][5] = 'W';                // Activate this when window is opened
    above[4][10] = 'S';
    above[4][12] = 'E';
    above[5][4] = 'E';
    above[5][6] = 'W';
    above[5][7] = 'U';
    above[6][5] = 'E';
    //above[6][19] = 'D';               // Activate this when trap door is opened
    above[7][5] = 'D';
    above[8][2] = 'S';
    above[8][8] = 'N';
    above[8][9] = 'W';
    above[8][13] = 'E';
    above[9][2] = 'E';
    above[9][8] = 'N';
    above[9][9] = 'W';
    above[9][11] = 'S';
    above[10][0] = 'W';
    above[10][4] = 'E';
    above[10][11] = 'S';
    above[11][9] = 'W';
    above[11][10] = 'N';
    above[11][11] = 'S';
    above[11][12] = 'E';
    above[12][4] = 'W';
    above[12][11] = 'S';
    above[12][13] = 'N';
    above[12][15] = 'E';
    above[13][2] = 'W';
    above[13][12] = 'S';
    above[13][14] = 'E';
    above[14][13] = 'W';
    above[14][14] = 'E';
    above[15][11] = 'S';
    above[15][12] = 'W';
    above[15][16] = 'D';
    above[16][15] = 'U';
    above[16][17] = 'D';
    above[17][16] = 'U';
    above[17][18] = 'N';
    above[18][17] = 'S';
    above[20][5] = 'U';
}

void game::initializeMazeTables()       // Initialize maze adjacency table
{
    for(int i = 0; i < 24; i++)
    {
        for(int j = 0; j < 24; j++)
        {
            maze[i][j] = NULL;
        }
    }

    maze[0][1] = 'W';
    maze[1][0] = 'E';
    maze[1][1] = 'N';
    maze[1][2] = 'W';
    maze[1][4] = 'S';
    maze[2][1] = 'N';
    maze[2][3] = 'W';
    maze[2][5] = 'E';
    maze[3][2] = 'N';
    maze[3][4] = 'W';
    maze[3][6] = 'U';
    maze[4][1] = 'S';
    maze[4][2] = 'D';
    maze[4][3] = 'E';
    maze[5][2] = 'S';
    maze[6][3] = 'N';
    maze[6][7] = 'E';
    maze[6][8] = 'W';
    maze[7][6] = 'W';
    maze[8][6] = 'D';
    maze[8][8] = 'W';
    maze[8][9] = 'E';
    maze[8][14] = 'U';
    maze[9][5] = 'D';
    maze[9][8] = 'W';
    maze[9][10] = 'E';
    maze[9][12] = 'U';
    maze[9][13] = 'S';
    maze[10][9] = 'N';
    maze[10][10] = 'W';
    maze[10][11] = 'S';
    maze[11][10] = 'N';
    maze[12][9] = 'S';
    maze[12][12] = 'N';
    maze[12][13] = 'W';
    maze[13][9] = 'S';
    maze[13][12] = 'W';
    maze[13][20] = 'E';
    maze[14][8] = 'N';
    maze[14][15] = 'D';
    maze[14][16] = 'E';
    maze[14][17] = 'S';
    maze[14][18] = 'W';
    maze[15][16] = 'D';
    maze[15][17] = 'N';
    maze[15][18] = 'S';
    maze[16][14] = 'E';
    maze[16][15] = 'U';
    maze[16][17] = 'W';
    maze[17][14] = 'E';
    maze[17][15] = 'W';
    maze[17][16] = 'S';
    maze[17][18] = 'D';
    maze[18][6] = 'D';
    maze[18][14] = 'U';
    maze[18][15] = 'S';
    maze[18][17] = 'E';
    maze[18][19] = 'N';
    maze[19][18] = 'S';
    maze[20][13] = 'W';
    //maze[20][21] = 'U';               // Activate this when cyclops is killed
    //maze[20][22] = 'E';               // Activate this when cyclops is killed
    maze[21][20] = 'D';
    maze[22][20] = 'W';
    maze[22][23] = 'E';
    maze[23][22] = 'W';
}

bool game::searchArray(int &i, char c)  // Search adjacency tables
{
    if(currentLevel == 0)               // If current level is above (0)
    {
        for(int j = 0; j < 21; j++)
        {
            if(above[i][j] == c)        // If value c exists in adjacency table for room i
            {
                i = j;                  // Return destination room number j
                return true;
            }
        }
        return false;                   // Otherwise, return false for connection not found
    }

    if(currentLevel == 1)               // If current level is below (1)
    {
        for(int j = 0; j < 35; j++)
        {
            if(below[i][j] == c)        // If value c exists in adjacency table for room i
            {
                i = j;                  // Return destination room number j
                return true;
            }
        }
        return false;                   // Otherwise, return false for connection not found
    }

    if(currentLevel == 2)               // If current level is maze (2)
    {
        for(int j = 0; j < 24; j++)
        {
            if(maze[i][j] == c)         // If value c exists in adjacency table for room i
            {
                i = j;                  // Return destination room number j
                return true;
            }
        }
        return false;                   // Otherwise, return false for connection not found
    }
    return false;                       // Return false just in case
}

string game::getInput()                 // Get use input
{
    string input;
    cout << ">";
    getline(cin,input);
    return input;
}

void game::getRoomInfo(int i)           // Display room info
{
    if(currentLevel == 0)
        cout << raboveRooms[i] << endl;
    if(currentLevel == 1)
        cout << rbelowRooms[i] << endl;
    if(currentLevel == 2)
        cout << rmazeRooms[i] << endl;
}

void game::initializeRoomScripts()
{
    // <--------> Above Ground Rooms <-------->

    room westOfHouse("West of House",
                    "You are standing in an open field west of white house, with a boarded front \ndoor. There is a small mailbox here with a leaflet in it.");

        westOfHouse.setHiddenItem("leaflet");

    room northOfHouse("North of House",
                    "You are facing the north side of a white house. There is no door here, and \nall the windows are boarded up. To the north a narrow path winds through the \ntrees.");

    room forestPath("Forest Path",
                    "This is a path winding through a dimly lit forest. The path heads north-south \nhere. One particularly large tree with some low branches stands at the edge\nof the path.");

    room upATree("Up a Tree",
                    "You are about 10 feet above ground nestled among some large branches.\nThe nearest branch above you is above your reach.\nBeside you on the branch is a small bird's nest.\nIn the bird's nest is a large egg encrusted with precious jewels, apparently \nscavenged by a childless songbird. The egg is covered with fine gold inlay, \nand ornamented in lapis lazuli and mother-of-pearl.\nUnlike most eggs, this one is hinged and closed with a delicate looking clasp. \nThe egg appears extremely fragile.");

        upATree.setHiddenItem("egg");

    room behindHouse("Behind House",
                    "You are behind the white house. A path leads into the forest to the east. In \none corner of the house there is a small window which is closed.");

    room kitchen("Kitchen",
                    "You are in the kitchen of the white house. A table seems to have been used \nrecently for the preparation of food. A passage leads to the west and a dark \nstaircase can be seen leading upward.\nA dark chimney leads down and to the east is small window which is open.\nOn the table is an elongated brown sack, smelling of hot peppers.\nA bottle is sitting on the table.\nThe glass bottle contains:\n\tA quantity of water.");

        kitchen.setHiddenItem("bottle");
        kitchen.setHiddenItem("sack");

    room livingRoom("Living Room",
                    "You are in the living room. There is a doorway to the east, a wooden door with \nstrange gothic lettering to the west, which appears to be nailed shut, a trophy case, and a large oriental rug in the center of the room. Above the trophy case hangs an elvish sword of great antiquity.\nA battery-powered brass lantern is on the trophy case.");

        livingRoom.setHiddenItem("sword");
        livingRoom.setHiddenItem("lantern");

    room attic("Attic",
                    "This is the attic. The only exit is a stairway leading down. Several coils of \nrope are lying in the corner. On the table are some nasty-looking knives.");

        attic.setHiddenItem("rope");
        attic.setHiddenItem("knife");

    room clearing8("Clearing",
                    "You are in a clearing, with a forest surrounding you on all sides.\nA path leads south. On the ground is a pile of leaves.");

    room forest9("Forest",
                    "This is a forest, with trees in all directions.\nTo the east, there appears to be sunlight.");

    room southOfHouse("South of House",
                    "You are facing the south side of a white house. There is no door here, and all \nthe windows are boarded.");

    room forest11("Forest",
                    "This is a dimly lit forest, with large trees all around.");

    room clearing12("Clearing",
                    "You are in a small clearing in a well marked forest path \nthat extends to the east and west.");

    room forest13("Forest",
                    "This is a dimly lit forest, with large trees all around.");

    room forest14("Forest",
                    "The forest thins out, revealing impassable mountains.");

    room canyonView("Canyon View",
                    "You are at the top of the Great Canyon on its west wall. From here there is a \nmarvelous view of the canyon and parts of the Frigid River upstream. Across the canyon, the walls of the White Cliffs join the mjighty ramparts of the Flathead Mountains to the east. Following the Canyon upstream to the north, Aragain falls\nmay be seen, complete with rainbow. To the west and south can be seen an \nimmense forest, stretching for miles around. A path leads northwest. It is \npossible to climb dwon into the canyon from here.");

    room rockyLedge("Rocky Ledge",
                    "You are on a ledge about halfway up the wall of the river canyon. You can see \nform here that the main flow from Aragain Falls twists along a passage which it is impossible for you to enter. Below you is the canyon bottom. Above you is \nmore cliff, which appears climbable.");

    room canyonBottom("Canyon Bottom",
                    "You are beneath the walls of the river canyon which may be climbable here. The \nlesser part of the runoff of Aragain Falls flows by below. \nTo the north is a narrow path.");

    room endOfRainbow("End of Rainbow",
                    "You are on a small, rock beach on the continuation of the Frigid River past \nthe Falls. The beach is narrow due to the presence of the White Cliffs. The river canyon opens here and sunlight shines in from above. A rainbow crosses over \nthe falls to the east and a narrow path continues to the southwest.");

    room cellar("Cellar",
                    "You are in a dark and damp cellar with a narrow passageway leading north, and\na crawlway to the south. On the west is the bottom of a steep metal ramp which\nis unclimbable.The trap door crashes shut, and you hear someone barring it.");

    room studio("Studio",
                "This appears to have been an artist's studio. The walls and floors are \nsplattered with paints of 69 different colors. Strangely enough, \nnothing of value is hanging here. At the south end of \nthe room is an open door (also covered with paint).\n A dark and narrow chimney leads up from a fireplace; \nalthough you might be able to get up it, it seems unlikely \nyou could get back down.\nLoosely attached to a wall is are small pieces of paper.");
                       // If user is above ground
        studio.setHiddenItem("paper");

    raboveRooms[0] = westOfHouse;
    raboveRooms[1] = northOfHouse;
    raboveRooms[2] = forestPath;
    raboveRooms[3] = upATree;
    raboveRooms[4] = behindHouse;
    raboveRooms[5] = kitchen;
    raboveRooms[6] = livingRoom;
    raboveRooms[7] = attic;
    raboveRooms[8] = clearing8;
    raboveRooms[9] = forest9;
    raboveRooms[10] = southOfHouse;
    raboveRooms[11] = forest11;
    raboveRooms[12] = clearing12;
    raboveRooms[13] = forest13;
    raboveRooms[14] = forest14;
    raboveRooms[15] = canyonView;
    raboveRooms[16] = rockyLedge;
    raboveRooms[17] = canyonBottom;
    raboveRooms[18] = endOfRainbow;
    //raboveRooms[19] = cellar; //To Cellar
    //raboveRooms[20] = studio;

    // <--------> Maze Rooms <-------->

    room trollRoom("Troll Room","This is a small room with passages to the east and south and \na forbidding hole leading west. \nBloodstains and deep scratches (perhaps made by an axe) mar the walls. \nA nasty-looking troll, branding a bloody axe, blocks all passages \nout of the room. \nYour sword has begun to glow very brightly.");

    room maze1("Maze Room","This is part of a maze of twisty little passages, all alike.");

    room maze2("Maze Room","This is part of a maze of twisty little passages, all alike.");

    room maze3("Maze Room","This is part of a maze of twisty little passages, all alike.");

    room maze4("Maze Room","This is part of a maze of twisty little passages, all alike.");

    room maze5("Maze Room","This is part of a maze of twisty little passages, all alike.");

    room maze6("Maze Room","This is part of a maze of twisty little passages, all alike.\nA skeleton, probably the remains of a luckless adventurer, lies here.\nBeside the skeleton are rusty knives.\nThe deceased adventurer's useless lanterns are here.\nThere are skeleton keys here.\nAn old leather bag, bulging with coins, is here.");

        maze6.setHiddenItem("coins");
        maze6.setHiddenItem("rusty knife");
        maze6.setHiddenItem("skeleton key");
        maze6.setHiddenItem("useless lantern");

    room maze7("Maze Room","This is part of a maze of twisty little passages, all alike.");

    room maze8("Maze Room","This is part of a maze of twisty little passages, all alike.");

    room maze9("Maze Room","This is part of a maze of twisty little passages, all alike.");

    room maze10("Maze Room","This is part of a maze of twisty little passages, all alike.");

    room maze11("Maze Room","This is part of a maze of twisty little passages, all alike.");

    room maze12("Maze Room","This is part of a maze of twisty little passages, all alike.");

    room maze13("Maze Room","This is part of a maze of twisty little passages, all alike. \nYour sword is glowing with a faint blue glow.");

    room maze14("Maze Room","This is part of a maze of twisty little passages, all alike.");

    room maze15("Maze Room","This is part of a maze of twisty little passages, all alike.");

    room maze16("Maze Room","This is part of a maze of twisty little passages, all alike.");

    room maze17("Maze Room","This is part of a maze of twisty little passages, all alike.");

    room maze18("Maze Room","This is part of a maze of twisty little passages, all alike.");

    room maze19("Maze Room","This is part of a maze of twisty little passages, all alike.");

    room cyclopsRoom("Cyclops Room","This room has an exit on the northwest, and a staircase leading up.\nA cyclops(similar script to troll), who looks prepared to eat horses (much less mere adventurers), blocks the staircase.\nFrom his state of health, and the bloodstains on the walls, you gather that he is not very friendly, though he likes people.\nYour sword has begun to glow very brightly.");

    room treasureRoom("Treasure Room","This is a large room, whose east wall is solid granite. \nA number of discarded bags, which crumble at your touch, \nare scattered about on the floor. There is an exit down a staircase.\nThere is a suspicious-looking individual, holding a large bag,\n leaning against one wall. He is armed with\n a deadly stiletto.\nThere is a silver chaliec, intricately engraved, here.\nYour sword has begun to glow very brightly.");

    room strangePassage("Strange Passage","This is a long passage. To the west is one entrance. \nOn the east there is an old wooden door, \nwith a large opening in it (about cyclops size).");

    //rmazeRooms[0] = trollRoom;
    rmazeRooms[1] = maze1;
    rmazeRooms[2] = maze2;
    rmazeRooms[3] = maze3;
    rmazeRooms[4] = maze4;
    rmazeRooms[5] = maze5;
    rmazeRooms[6] = maze6;
    rmazeRooms[7] = maze7;
    rmazeRooms[8] = maze8;
    rmazeRooms[9] = maze9;
    rmazeRooms[10] = maze10;
    rmazeRooms[11] = maze11;
    rmazeRooms[12] = maze12;
    rmazeRooms[13] = maze13;
    rmazeRooms[14] = maze14;
    rmazeRooms[15] = maze15;
    rmazeRooms[16] = maze16;
    rmazeRooms[17] = maze17;
    rmazeRooms[18] = maze18;
    rmazeRooms[19] = maze19;
    rmazeRooms[20] = cyclopsRoom;
    rmazeRooms[21] = treasureRoom;
    rmazeRooms[22] = strangePassage;
    //rmazeRooms[23] = livingRoom;

    // <--------> Below Ground Rooms <-------->

    room eastOfChasm("East of Chasm",
                "You are on the east edge of a chasm, the bottom of which cannot be seen.\nA narrow pssage goes borth, and the path you are on continues to the east.");

    room eastWestPassage("East-West Passage",
                "This is a narrow east-west passageway. \nThere is a narrow stairway leading down at the north end of the room.");

    room chasm("Chasm",
                "A chasm runs southwest to northeast and the path follows it. \nYou are on the south side of the chasm, \nwhere a crack opens into a passage.");

    room northSouthPassage("North-South Passage",
                "This is a high north-south passage, which forks to the northeast.");

    room reservoirSouth("Reservoir South",
                "You are in a long room on the south shore of a large lake, \nfar too deep and wide for crossing. There is a patch\nalong the stream to the east or west, a steep pathway climbing \nsouthwest along the edge of a chasm ,\nand a path leading into a canyon to the southeast.");

    room deepCanyon("Deep Canyon",
                "You are on the south edge of a deep canyon. \nPassages lead off to the east, northwest, and southwest.\nA stairway leads down. You can hear the sound of flowing water \nfrom below.");

    room dam("Dam",
                "You are standing on the top of the Flood Control Dam # 3, \nwhich was quite a tourist attraction in times far distant. \nThere are paths to the north, south, and west, and a scramble down.\nThe sluice gate on the dam are closed. Behind the dam,\nthere can be seen a wide reservoir. \nWater is pouring over the top of the now abandoned dam. \nThere is a control panel here, on which a large \nmetal bolt is mounted. \nDirectly above the bolt is a small green plastic bubble.");

    room damLobby("Dam Lobby",
                "This rooms appears to have been the waiting room for \ngroups touring the dam. There are open doorways here \nto the borth and east marked 'Private', and there is a path\nleading south over the top of the dam. \nSome guidebooks entitled 'Flood Control Dam # 3' \nare on the reception desk.\nThere are matchbooks whose covers say 'Visit Beautiful FCD#3' here.");

        damLobby.setHiddenItem("matchbook");

    room maintenanceRoom("Maintenance Room",
                "This is what appears to have been the maintenance room \nfor Flood Control Dam # 3. Apparently, this room has been \nransacked recently, for most of the valuable equipment is gone. \nOn the wall in fron of you is a group of buttons \ncolored blue, yellow, brown and red. \nThere are doorways or the west and south. \nThere is group of tool chests here.\nThere is a wrench here.\nThere is an object which looks like a tube of toothpaste here.\nThere is a screwdriver here.");

    room damBase("Dam Base",
                "You are the base of Flood Control Dam # 3, which looms above you \nand to the north. The river Frigid \nis flowing by here. Along the river are the \nWhite Cliffs which seem to form giant walls \nstretching from north to south along the shores \nof the river as it winds its way downstream. \nThere is a folded pile of plastic here which \nhas a small valve attached.");

    room streamView("Stream View",
                "You are standing on a path beside a gently flowing stream.\nThe path follows the stream which flows from \nwest to east.");

    room roundRoom("Round Room",
                "This is a circular stone room with passages in all directions.\nSeveral of them have unfortunately been blocked \nby cave-ins.");

    room loudRoom("Loud Room",
                "This is a large room with a ceiling which cannot be detected \nfrom the ground. There is anrrow passage from east to west \nand a stone stairway leading upward. The room is deafeningly loud \nwith an undetermined rushing sound. The sound seems to \nreverberate from all of the walls, making it difficult even to think. \nOn the ground is a large platinum bar.");

    room dampCave("Damp Cave",
                "This cave has exits to the west and east, and narrows to a \ncrack toward the south. The earth is particularly damp here.");

    room whiteCliffs("White Cliffs Beach",
                "You are on a narrow strip of beach which runs along the base of \nthe White Cliffs. There is narrow path heading south along the Cliffs \nand a tight passage leading west into the cliffs themselves.");

    room whiteCliffsBeach("White Cliffs Beach",
                "You are on a rocky, narrow strip of beach beside the Cliffs. \nA narrow path leads north along the shore.");

    room narrowPassage("Narrow Passage",
                "This is a long and narrow corridor where a long north-south passageway \nbriefly narrows even further.");

    room mirrorRoom("Mirror Room",
                "You are in a large square room with tall ceilings. On the \nsouth wall is an enormous mirror which fills the entire wall. \nThere are exits on the three other sides of the room.");

    room windingPassage("Winding Passage",
                "This is a winding passage. It seems that there are only exits on the east \nand north.");

    room cave("Cave",
                "This is a tiny cave with entrances west and north, and a dark, \nforbidding staircase leading down.");

    room entranceToHades("Entrance to Hades",
                "You are outside a large gateway, on which is inscribed:\n\tAbandon every hope all ye who enter here!\nThe gate is open; through it you can see desolation, \nwith a pile of mangled bodies in one corner. \nThousands of voices, lamenting some hideous fate, can be heard.\nThe way throught he gate is barred by evil spirits, \nwho jeer at your attempts to pass.");

    room landOfTheDead("Land of the Dead",
                "You have entered the Land of the Living Dead.\nThousands of lost souls can be heard weeping and moaning. \nIn the corner are stacked the remains of dozens of previous adventurers \nless fortunate than yourself. A passage exits to the north.\nLying in one corner of the room is a beautifully carved crystal skill. \nIt apears to be grinning at you rather nastily. ");

        landOfTheDead.setHiddenItem("skull");

    room engravingCave("Engraving Cave",
                "You have entered a low cave with passages leading northwest and east.\nThere are old engravings on the walls here.");

    room domeRoom("Dome Room",
                "You are at the periphery of  a large dome, which forms the ceiling \nof another room below. Protecting you from a precipitous drop \nis a wooden railing which circles the dome.");

    room torchRoom("Torch Room",
                "This is a large room with a prominent doorway leading \nto a down staircase. Above you is a large dome. \nUp around the edge of the dome (20 feet up) is a wooden railing. \nIn the center of the room sits a white marble pedestal.\nA piece of rope descends from the railing above, ending some five feet \nabove your head.\nSitting on the pedestal is a flaming torch, made of ivory.");

        torchRoom.setHiddenItem("torch");

    room temple("Temple",
                "This is the north end of a large temple. On the east wall is \nan ancient inscription, probably a prayer in a long-forgotten language. \nBelow the prayer is a staircase leading down. \nThe west wall is solid granite. \nThe exit to the north end of the room is through huge marble pillars.\nThere is are brass bells here.");

        temple.setHiddenItem("bell");

    room egyptianRoom("Egyptian Room",
                "This is a room which looks like an Egyptian tomb. \nThere is an ascending staircase to the west.\nThe solid-gold coffin used for the burial of Ramses II is here.");

    room altar("Altar",
                "This is the south end of a large temple. In front of you \nis what appears to be an altar. In one corner is a small hole in the \nfloor which leads into darkness. You probably could not get \nback up it. On the two ends of the altar are burning candles.\nOn the altar is a large black book, open to page 569.");

        altar.setHiddenItem("candles");
        altar.setHiddenItem("book");

    room gallery("Gallery",
                "This is an art gallery. Most of the paintings have been \nstolen by vandals with exceptional taste. \nThe vandals left through either the north or west exits.\nFortunately there is still on chance for you to \nbe a vandal, for on the far wall are paintings of unparalleled beauty.");

        gallery.setHiddenItem("painting");

    rbelowRooms[0] = cellar;
    rbelowRooms[1] = trollRoom;
    //rbelowRooms[2] = maze1;
    rbelowRooms[3] = eastOfChasm;
    //rbelowRooms[4] = kitchen;
    rbelowRooms[5] = studio;
    rbelowRooms[6] = eastWestPassage;
    rbelowRooms[7] = chasm;
    rbelowRooms[8] = northSouthPassage;
    rbelowRooms[9] = reservoirSouth;
    rbelowRooms[10] = deepCanyon;
    rbelowRooms[11] = dam;
    rbelowRooms[12] = damLobby;
    rbelowRooms[13] = maintenanceRoom;
    rbelowRooms[14] = damBase;
    rbelowRooms[15] = streamView;
    rbelowRooms[16] = roundRoom;
    rbelowRooms[17] = loudRoom;
    rbelowRooms[18] = dampCave;
    rbelowRooms[19] = whiteCliffs;
    rbelowRooms[20] = whiteCliffsBeach;
    rbelowRooms[21] = narrowPassage;
    rbelowRooms[22] = mirrorRoom;
    rbelowRooms[23] = windingPassage;
    rbelowRooms[24] = cave;
    rbelowRooms[25] = entranceToHades;
    rbelowRooms[26] = landOfTheDead;
    rbelowRooms[27] = engravingCave;
    rbelowRooms[28] = domeRoom;
    rbelowRooms[29] = torchRoom;
    rbelowRooms[30] = temple;
    rbelowRooms[31] = egyptianRoom;
    rbelowRooms[32] = altar;
    //rbelowRooms[33] = livingRoom;
    rbelowRooms[34] = gallery;
}

void game::move(char c)                             // Move in direction c
{
    if((currentLevel!=1 && currentRoom!=1) && (currentLevel!=2 && currentRoom!=20))
    {
        if(health < 3)
        {
            health++;
        }
    }
    switch(c)
    {
        case 'N': if(searchArray(currentRoom,c))
                  {                                 // If c is 'N'
                      checkSwitch();                // Check if graph switch is necessary
                      checkLantern();               // Check if room requires lantern
                      getRoomInfo(currentRoom);
                  }                                 // Otherwise display room info
                  else                              // Error if movement not possible
                    cout << "You can't go that way." << endl;
                  break;
        case 'S': if(searchArray(currentRoom,c))
                  {                                 // If c is 'S'
                      checkSwitch();                // Check if graph switch is necessary
                      checkLantern();               // Check if room requires lantern
                      getRoomInfo(currentRoom);
                  }                                 // Otherwise display room info
                  else                              // Error if movement not possible
                    cout << "You can't go that way." << endl;
                  break;
        case 'E': if(searchArray(currentRoom,c))
                  {                                 // If c is 'E'
                      checkSwitch();                // Check if graph switch is necessary
                      checkLantern();               // Check if room requires lantern
                      getRoomInfo(currentRoom);
                  }                                 // Otherwise display room info
                  else                              // Error if movement not possible
                    cout << "You can't go that way." << endl;
                  break;
        case 'W': if(searchArray(currentRoom,c))
                  {                                 // If c is 'W'
                      checkSwitch();                // Check if graph switch is necessary
                      checkLantern();               // Check if room requires lantern
                      getRoomInfo(currentRoom);
                  }                                 // Otherwise display room info
                  else                              // Error if movement not possible
                    cout << "You can't go that way." << endl;
                  break;
        case 'U': if(searchArray(currentRoom,c))
                  {                                 // If c is 'U'
                      checkSwitch();                // Check if graph switch is necessary
                      checkLantern();               // Check if room requires lantern
                      getRoomInfo(currentRoom);
                  }                                 // Otherwise display room info
                  else                              // Error if movement not possible
                    cout << "You can't go that way." << endl;
                  break;
        case 'D': if(searchArray(currentRoom,c))
                  {                                 // If c is 'D'
                      checkSwitch();                // check if graph switch is necessary
                      checkLantern();               // Check if room requires lantern
                      getRoomInfo(currentRoom);
                  }                                 // Other wise display room info
                  else                              // Error if movement not possible
                    cout << "You can't go that way." << endl;
                  break;
        default: cout << "I have no clue where you're trying to go." << endl<<endl;
                  break;
    }
}

void game::action(string s)                         // Perform actions!
{
    if((currentLevel!=1 && currentRoom!=1) && (currentLevel!=2 && currentRoom!=20))
    {
        if(health < 3)
        {
            health++;
        }
    }                                               // Action string parser
    string verb, target, object;                    // String variables
    string line = s;                                // User line

    int pos = line.find(" ",0);                     // Space delimmited search
    verb = line.substr(0,pos);                      // Extract verb input
    line.erase(0,pos+1);                            // Remove verb from line

    pos = line.find(" ",0);                         // Space delimmited search
    target = line.substr(0,pos);                    // Extract target input
    line.erase(0,pos+1);                            // Remove target from line

    if(line.length() > 0)                           // If there is more input
    {                                               // Extract object input
        object = line;
    }

    if(verb == "light" && (target=="match" || target=="matches" || target=="matchbook"))
    {
        string matchbook = "matchbook";
        string litmatch = "litmatch";
        int pos;                                    // Position index
        if(findInventory(matchbook,pos))            // Check if user has matchbook
        {                                           // Light match
            cout << "One of the matches starts to burn" << endl << endl;
            removeInventory(pos);                   // Change matchbook to litmatch
            inventory[pos] = litmatch;
            return;
        }
        else
        {                                           // Item not in inventory
            cout << "You are not carrying that." << endl << endl;
            return;
        }
    }
												// Second step -> light candles
    if(verb == "light" && (target=="candle"||target=="candles"))
    {
        string matchbook = "matchbook";
        string litmatch = "litmatch";
        string candles = "candles";
        int pos;                                    // Position index
        if(findInventory(candles,pos))              // Check if user has candles
        {
            if(findInventory(litmatch,pos))         // Check if user has lit match
            {                                       // If yes
                removeInventory(pos);               // Change litmatch to matchbook
                inventory[pos] = matchbook;
                findInventory(candles,pos);         // Get candles index
                cout << " The candles are lit, but the wind blows them out.\nThe match has gone out."<<endl<<endl;
                return;
            }
            else
            {                                       // Litmatch not in inventory
                cout << "You cannot light the candles." << endl << endl;
                return;
            }
        }
        else
        {                                           // Item not in inventory
            cout << "You are not carrying that." << endl << endl;
            return;
        }
    }

    string litmatch = "litmatch";
    if(findInventory(litmatch,pos))         // Change back to matchbook
    {
        string matchbook = "matchbook";
        cout << "The match has gone out." <<endl<<endl;
        removeInventory(pos);
        inventory[pos] = matchbook;
    }

    if( verb == "diagnose")
    {
        if(health == 3)
            cout << "You are at full health." <<endl<<endl;
        if(health == 2)
            cout << "You are wounded."<<endl<<endl;
        if(health == 1)
            cout << "You are near death."<<endl<<endl;
        return;
    }

    if( verb == "read")
    {
        if(findInventory(target,pos))
        {
            if(target == "leaflet")
            {
                cout<< "'WELCOME TO ZORK!\n\nZork is a game of adventure, danger, and low cunning. \nIn it you will explore some of th most amazing territory \never seen by mortals. No computer should be without one!!'" <<endl<<endl;
            }
            if(target == "paper")
            {
                cout<< "'Congratulations!\n\nYou are the privileged owner of ZORK I: The Great Underground Empire, \na self-contained and self-maintaining universe. If used and maintained \nin accordance with normal operating practices for small universes, \nZORK will provide many months of trouble-free operation.'" <<endl<<endl;
            }
            if(target == "book")
            {
                cout<< "'Commandment #12592\nOh ye who go about saying unto each: 'Hello sailor':\nDost thou know the magnitude of thy sin before the gods?\nYea, verily, thou shalt be ground between two stones.\nShall the angry goods cast thy body into the whirlpool?\nSurely, thy eye shall be put out with a sharp stick!\nEven unto the ends of the earth shalt thou wander and\nUnto the land of the dead shalt thou be sent at last.\nSurely thou shalt repent of thy cunning.'" <<endl<<endl;
            }
            return;
        }
        else                                        // User does not have item
        {
            cout << "You are not carring that." <<endl<<endl;
            return;
        }
    }

    if( s == "turn on lantern" )
    {
        string lanterns = "lantern";
        if(findInventory(lanterns, pos))
        {
            lantern = true;
            cout << "You have turned your lantern on." <<endl<<endl;
            return;
        }
        else                                        // User does not have item
        {
            cout << "You are not carring that." <<endl<<endl;
            return;
        }
    }

    if( s == "turn off lantern" )
    {
        string lanterns = "lantern";
        if(findInventory(lanterns, pos))
        {
            lantern = false;
            cout << "You have turned your lantern off." <<endl<<endl;
            return;
        }
        else                                        // User does not have item
        {
            cout << "You are not carring that." <<endl<<endl;
            return;
        }
    }

    if(verb == "add" && target == "trophy")         // Add trophy to case
    {
        if(currentLevel == 0 && currentRoom == 6)   // if user is in living room
        {
            if(findInventory(object,pos))           // And item is in user inventory
            {
                trophyCase.push_back(object);       // Add item to trophy case
                cout<<"You have added a trophy to the trophy case: "<< object << endl << endl;
                removeInventory(pos);               // Remove item from inventory
                return;
            }
            else                                    // User does not have item
            {
                cout << "You are not carring that." <<endl<<endl;
                return;
            }
        }
        else                                        // User is not in living room
        {
            cout << "The trophy case is not in this room." <<endl<<endl;
            return;
        }
    }

    if(verb == "open")                              // If verb is 'open'
    {                                               // And target is 'window'
        if(target == "window" && currentLevel == 0 && currentRoom == 4)
        {                                           // If user is behind house
            cout << "With great effort, you open the window far enough to allow entry." << endl << endl;
            above[4][5] = 'W';                      // Connect 'behind house' to 'kitchen'
            room behindHouse("Behind House",        // Change script to denote open window
                    "You are behind the white house. A path leads into the forest to the east. In \none corner of the house there is a small window which is open.");
            raboveRooms[4] = behindHouse;
            return;
        }
                                                    // If target is trap or door
        if((target == "trap" || target == "door") && currentLevel == 0 && currentRoom == 6)
        {                                           // And user is in living room
            cout << "The door reluctantly opens to reveal a rickety starcase descending into darkness"<<endl<<endl;
            above[6][19] = 'D';;                    // Connect living room to cellar
            return;
        }
        cout << "There is nothing to open." <<endl<<endl;
        return;
    }

    if(verb == "take")                              // If verb is take
    {
        int pos;                                    // Position index
        int insert;                                 // Insertion index
        if(currentLevel == 0)                       // If user is above ground
        {                                           // And target is in current room
            if(raboveRooms[currentRoom].findItem(target,pos))
            {
                if(inventorySpace(insert))          // And user has space in inventory
                {                                   // Insert item to inventory and remove from room
                    inventory[insert] = raboveRooms[currentRoom].getHiddenItem(pos);
                    raboveRooms[currentRoom].removeItem(pos);
                    cout << "You take "<< target<< endl<< endl;
                    if(target == "egg")
                    {
                        room upATree("Up a Tree",
                            "You are about 10 feet above ground nestled among some large branches.\nThe nearest branch above you is above your reach.\nBeside you on the branch is a small bird's nest.\nThe nest is empty.");
                        raboveRooms[3] = upATree;
                    }
                    return;
                }
            }
            else
            {                                       // Item is not in room
                cout << "You can't find that item in this room." << endl << endl;
                return;
            }
        }

        if(currentLevel == 1)                       // If user is below ground
        {                                           // And target is in current room
            if(rbelowRooms[currentRoom].findItem(target,pos))
            {
                if(inventorySpace(insert))          // And user has space in inventory
                {                                   // Insert item to inventory and remove from room
                    inventory[insert] = rbelowRooms[currentRoom].getHiddenItem(pos);
                    rbelowRooms[currentRoom].removeItem(pos);
                    cout << "You take "<< target<< endl<< endl;
                    return;
                }
            }
            else
            {                                       // Item is not in room
                cout << "You can't find that item in this room." << endl << endl;
                return;
            }
        }

        if(currentLevel == 2)                       // If user is in maze
        {                                           // And target is in current room
            if(rmazeRooms[currentRoom].findItem(target,pos))
            {
                if(inventorySpace(insert))          // And user has space in inventory
                {                                   // Insert item to inventory and remove from room
                    inventory[insert] = rmazeRooms[currentRoom].getHiddenItem(pos);
                    rmazeRooms[currentRoom].removeItem(pos);
                    cout << "You take "<< target << endl << endl;
                    return;
                }
            }
            else
            {                                       // Item is not in room
                cout << "You can't find that item in this room." << endl << endl;
                return;
            }
        }
    }

    if(verb == "look")                              // If verb is look
    {
        if(currentLevel == 0)                       // And current level is above ground
        {
            raboveRooms[currentRoom].displayRoom(); // Display room items
            return;
        }

        if(currentLevel == 1)                       // Or current level is below ground
        {
            rbelowRooms[currentRoom].displayRoom(); // Display room items
            return;
        }

        if(currentLevel == 2)                       // Or current level is the maze
        {
            rmazeRooms[currentRoom].displayRoom();  // Display room items
            return;
        }
    }

    if(verb == "drop")                              // If verb is drop
    {
        int pos;                                    // Position index
        if(findInventory(target,pos))               // If item is in inventory
        {
            if(currentLevel == 0)                   // If current level is above ground
            {                                       // Add item to room
                raboveRooms[currentRoom].setHiddenItem(target);
                removeInventory(pos);               // Remove item from inventory
                cout << "You have dropped " << target << endl << endl;
                return;
            }
            if(currentLevel == 1)                   // If current level is below ground
            {                                       // Add item to room
                rbelowRooms[currentRoom].setHiddenItem(target);
                removeInventory(pos);               // Remove item from inventory
                cout << "You have dropped " << target << endl << endl;
                return;
            }
            if(currentLevel == 2)                   // If current level is the maze
            {                                       // Add item to room
                rmazeRooms[currentRoom].setHiddenItem(target);
                removeInventory(pos);               // remove item from inventory
                cout << "You have dropped " << target << endl << endl;
                return;
            }
        }
        else
        {                                           // Item not in inventory
            cout << "You are not carrying that." << endl << endl;
            return;
        }
    }

    if(verb == "inventory")                         // If verb is inventory
    {
        cout << "Your inventory:" <<endl;           // Display inventory
        for(int i = 0; i < 6; i++)
        {
            if(inventory[i] != "")
                cout << "\t" << inventory[i] << endl;
        }
        cout << endl;
        return;
    }

    if(verb == "ring" && target == "bell")          // If action is 'ring bell'
    {
        if(findInventory(target,pos))               // And bell is in inventory
        {                                           // And user is at entrance to hades
            if(currentLevel == 1 && currentRoom==25)
            {                                       // Ring bell
                cout << "The bell suddenly becomes red hot and falls to the ground. \nThe wraiths, as if paralyzed, stop their jeering and slowly \nturn to face you. Ont heir ashen faces, the expression of a \nlong-forgotten terror takes shape. In your confusion, the \ncandles drop to the ground (and they are out)."<<endl<<endl;
                removeInventory(pos);               // Drop bell
                rbelowRooms[currentRoom].setHiddenItem(target);
                hadesInstance();                    // Start hades instance
                return;
            }
            else                                    // If bell is in inventory, but user is not at entrance to hades
            {                                       // Just ring bell
                cout << "You ring the bell." << endl;
                return;
            }
        }
        else
        {                                           // Item not in inventory
            cout << "You are not carrying that." << endl << endl;
            return;
        }
    }

    if(verb == "tie" && target == "rope")           // If action is 'tie rope'
    {
        int pos;                                    // Position index
        if(findInventory(target,pos))               // If rope is in inventory
        {                                           // And user is in dome room
            if(currentLevel == 1 && currentRoom==28)
            {
                removeInventory(pos);               // Remove rope from inventory
                cout << "You tie your rope to the railing." << endl << endl;
                below[28][29] = 'D';                // Connect dome room to temple room (one-way)
                return;
            }
            else                                    // Rope is in inventory, but user is not in dome room
                cout << "There is nothing for you to tie it to." << endl << endl;
            return;
        }
        else
        {                                           // Item is not in inventory
            cout << "You are not carrying that." << endl << endl;
            return;
        }
    }

    if(verb == "kill")                              // If verb is kill
    {
        string sword = "sword";
        if(target == "troll")                       // If target is troll
        {                                           // And user is in troll room
            if(currentLevel == 1 && currentRoom == 1)
            {
                int pos;                            // Check if user has sword in inventory
                if(findInventory(sword,pos))        // If yes
                {                                   // KILL TROLL!! >:D
                    cout<<"The troll is battered into unconciousness." << endl
                        <<"Almost as soon as the troll breathes his last breath," << endl
                        <<"a cloud of sinister black fog envelops him, and when" << endl
                        <<"the fog lifts, the carcass has disppeared." << endl << endl;
                    room trollRoom("Troll Room","This is a small room with passages to the east and south and \na forbidding hole leading west. \nBloodstains and deep scratches (perhaps made by an axe) mar the walls.\nThere is a bloody axe here.");
                    trollRoom.setHiddenItem("axe"); // Add axe to room
                    rbelowRooms[1] = trollRoom;     // Change troll room
                    below[1][0] = 'S';              // Connect troll room to other rooms
                    below[1][2] = 'W';
                    below[1][6] = 'E';
                    return;
                }
                else
                {                                   // User has no sword and is DOOMED
                    cout << "You think you can kill a troll with your bare hands?!" << endl << endl;
                }
            }
            else
            {                                       // No troll in room
                cout<< "There is no troll to kill." << endl <<endl;
                return;
            }
        }

        if(target == "cyclops")                     // If target is cyclops
        {
            if(currentLevel == 2 && currentRoom == 20)
            {                                       // Cyclops cannot be killed
                cout << "The cyclops can only be defeated by 'Ulysses'." << endl
                     << "The flat of the cyclop's fist hits you delicately on the head" << endl
                     << "It appears that the last blow was too much for you. I'm afraid you are dead."<< endl << endl;
                exit(0);                            // GAME OVER
                return;
            }
            else
            {                                       // No cyclops in room
                cout<< "There is no cyclops to kill." << endl << endl;
                return;
            }
        }
    }

    if(verb == "ulysses" || verb == "Ulysses")
    {                                               // The only way to defeat the cyclops
        if(currentLevel == 2 && currentRoom == 20)
        {
            cout << "The cyclops, hearing the name of his father's deadly nemesis,\nflees the room by knocking down the wall on the east of the room.\nYour sword is no longer glowing." << endl << endl;
            maze[20][21] = 'U';                     // Connect cyclops room to others
            maze[20][22] = 'E';
            below[0][33] = 'U';
            room cellar("Cellar",
                    "You are in a dark and damp cellar with a narrow passageway leading north, and\na crawlway to the south. On the west is the bottom of a steep metal ramp which\nis unclimbable.");
            rbelowRooms[0] = cellar;
            return;
        }
        else
        {                                           // Saying ulysses outside of cyclops room
            cout << "Why are you saying that? It's not like theres a cyclops around." << endl << endl;
            return;
        }
    }

    if(currentLevel == 1 && currentRoom == 1)
    {
        health--;
        if(health == 0)                             // Troll kills user
        {
            cout << "The flat of the troll's axe hits you delicately on the head" << endl
                 << "It appears that the last blow was too much for you. I'm afraid you are dead." << endl
                 << "GAME OVER"<<endl<<endl;        // GAME OVER
                exit(0);
        }
        else
            cout << "The flat of the troll's axe hits you delicately on the head" << endl <<endl;
        return;
    }

    if(currentLevel == 2 && currentRoom == 20)
    {
        health--;
        if(health == 0)                                                // Cyclops kills user
        {
            cout << "The flat of the cyclop's fist hits you delicately on the head" << endl
                 << "It appears that the last blow was too much for you. I'm afraid you are dead." << endl <<endl
                 << "GAME OVER"<<endl<<endl;        // GAME OVER
                exit(0);
        }
        else
            cout << "The flat of the cyclop's fist hits you delicately on the head" << endl;
        return;
    }

    cout << "You can't do that." <<endl<<endl;      // Action not possible
    return;
}

void game::checkSwitch()                            // Check if graph switch is necessary
{                                                   // Change adjacency tables, currentRoom, currentLevel
    if((currentLevel == 0) && (currentRoom == 19))
    {
                                                    // Go to cellar
        currentLevel = 1;                           // Change currentLevel to 1
        currentRoom = 0;                            // Change currentRoom to 0
        return;
    }

    if((currentLevel == 1) && (currentRoom == 2))
    {
                                                    // Go to maze
        currentLevel = 2;                           // Change currentLevel to 2
        currentRoom = 1;                            // Change currentRoom to 1
        return;
    }

    if((currentLevel == 1) && (currentRoom == 33))
    {
                                                    // Go to living room
        currentLevel = 0;                           // Change currentLevel to 0
        currentRoom = 6;                            // Change currentRoom to 6
        return;
    }

    if((currentLevel == 1) && (currentRoom == 4))
    {
                                                    // Go to kitchen
        currentLevel=0;                             // Change currentLevel to 0
        currentRoom=5;                              // Change currentRoom to 5
        return;
    }

    if((currentLevel == 2) && (currentRoom == 0))
    {
                                                    // Go to troll room
        currentLevel = 1;                           // Change currentLevel to 2
        currentRoom = 1;                            // Change currentRoom to 1
        return;
    }

    if((currentLevel == 2) && (currentRoom == 23))
    {
                                                    // Go to living room
        currentLevel = 0;                           // Change currentLevel to 0
        currentRoom = 6;                            // Change currentRoom to 6
        return;
    }
}

bool game::inventorySpace(int &index)               // Check if inventory has free space
{
    for(int i =0; i < 6; i++)
    {
        if(inventory[i] == "")
        {
            index = i;
            return true;
        }
    }
    return false;
}

bool game::findInventory(string &val, int &index)   // Find item in inventory
{                                                   // Returns index
    for(unsigned int i = 0; i < 6; i++)
    {
        if(inventory[i] == val)
        {
            index = i;
            return true;
        }
    }
    return false;
}

void game::removeInventory(int i)                   // Remove item from inventory
{
    inventory[i]="";
}

void game::hadesInstance()                          // Entrance to Hades instances
{
    string litcandle = "lit candle";
    string litmatch = "litmatch";
    string matchbook = "matchbook";
    string candles = "candles";
    string wavecandle = "wave candle";
    string book = "book";

    string s = getInput();                          // Get user input
    string verb, target, object;                    // Parse
    string line = s;

    int pos = line.find(" ",0);                     // Get verb
    verb = line.substr(0,pos);
    line.erase(0,pos+1);

    pos = line.find(" ",0);                         // Get target
    target = line.substr(0,pos);
    line.erase(0,pos+1);

    if(line.length() > 0)                           // Get object
    {
        object = line;
    }
                                                    // First step -> Light matches
    if(verb == "light" && (target=="match" || target=="matches" || target=="matchbook"))
    {
        int pos;                                    // Position index
        if(findInventory(matchbook,pos))            // Check if user has matchbook
        {                                           // Light match
            cout << "One of the matches starts to burn" << endl << endl;
            removeInventory(pos);                   // Change matchbook to litmatch
            inventory[pos] = litmatch;
            hadesInstance();                        // Go to next step in hades instance
            if(findInventory(litmatch,pos))         // Change back to matchbook
            {
                removeInventory(pos);
                inventory[pos] = matchbook;
            }
            return;
        }
        else
        {                                           // Item not in inventory
            cout << "You are not carrying that." << endl << endl;
            return;
        }
    }
                                                    // Second step -> light candles
    if(verb == "light" && (target=="candle"||target=="candles"))
    {
        int pos;                                    // Position index
        if(findInventory(candles,pos))              // Check if user has candles
        {
            if(findInventory(litmatch,pos))         // Check if user has lit match
            {                                       // If yes
                removeInventory(pos);               // Change litmatch to matchbook
                inventory[pos] = matchbook;
                findInventory(candles,pos);         // Get candles index
                cout << " The candles are lit.\nThe match has gone out."<<endl<<endl;
                removeInventory(pos);
                inventory[pos] = litcandle;         // Change candle to litcandle
                hadesInstance();                    // Go to next step in hades instance
                if(findInventory(litcandle,pos))    // Change back to candles
                {
                    removeInventory(pos);
                    inventory[pos] = candles;
                }
                return;
            }
            else
            {                                       // Litmatch not in inventory
                cout << "You cannot light the candles." << endl << endl;
                return;
            }
        }
        else
        {                                           // Item not in inventory
            cout << "You are not carrying that." << endl << endl;
            return;
        }
    }

                                                    // Third Step -> Wave candles
    if(verb == "wave" && (target=="candle"||target=="candles"))
    {
        int pos;                                    // Position index
        if(findInventory(litcandle,pos))            // Check if user has litcandle
        {                                           // If yes, wave candles
            cout << "The flames flicker wildly and appear to dance. \nThe earth beneath your feet trembles, \nand your legs nearly buckle beneath you. \nThe spirits cower at your unearthly power."<<endl<<endl;
            removeInventory(pos);                   // Change to wavecandle
            inventory[pos] = wavecandle;
            cout << "The flame is extinguished." << endl << endl;
            hadesInstance();                        // Next step in hades instance
            if(findInventory(wavecandle,pos))       // Change back to candles
            {
                removeInventory(pos);
                inventory[pos] = candles;
            }
            return;
        }
        else
        {                                           // Wave unlit candles
            cout << "Waving the unlit candles has no effect." << endl << endl;
            return;
        }
    }

                                                    // Fourth Step -> Read from book
    if(verb == "read" && target=="book")
    {
        int pos;                                    // Position index
        if(findInventory(book,pos))                 // Check if user has book
        {                                           // Read from the book
            cout << "Each word of the prayer reverberates through the hall \nin a defeaning confusion. As the last word fades, \n voice, loud and commanding, speaks:\n'Begone, friends!' A heart-stopping scream fills the cavern, \nand the spirits, sensing a greater power, flee through the walls."<<endl<<endl;
            below[25][26] = 'S';                    // Connect to land of the dead
            cout << "The gate south is no longer barred." << endl << endl;
            if(findInventory(wavecandle,pos))       // Change back to candles
            {
                removeInventory(pos);
                inventory[pos] = candles;
            }
            return;
        }
        else
        {                                           // Item not in inventory
            cout << "You are not carrying that." << endl << endl;
            return;
        }
    }
                                                    // No other actions do anything
    cout << "Doing that has no effect in this place." << endl << endl;
    return;
}

void game::checkTrophy()                            // Check if tropy case has all treasures
{
    string egg = "egg";
    string painting ="painting";
    string skull = "skull";
    string torch = "torch";
    string coins = "coins";
    int trophies = 0;

    for(unsigned int i=0; i < trophyCase.size(); i++)
    {                                               // If trophy found, increment trophy counter
        if(trophyCase[i] == egg)
            trophies++;
        if(trophyCase[i] == painting)
            trophies++;
        if(trophyCase[i] == skull)
            trophies++;
        if(trophyCase[i] == torch)
            trophies++;
        if(trophyCase[i] == coins)
            trophies++;
    }

    if(trophies == 5)                               // If counter = 5, all trophies have been collected
    {                                               // User wins
        cout << "Congratulations! You have collected all the trophies!" << endl
             << "Thanks for playing Zork!" << endl << endl;
             exit(0);
    }
    else                                            // Otherwise continue game
        return;
}

void game::checkCheat(string s)
{
    if(s == "uuddlrlrbas")
    {
        cout << "Congratulations! You have collected all the trophies!" << endl
             << "Thanks for playing Zork!" << endl << endl;
             exit(0);
    }
}

int game::getHealth()
{
    return health;
}

void game::checkLantern()
{
    if(currentLevel == 1 && currentRoom == 0)       // If player is in the cellar
    {
        if(lantern)                                 // Normal room
        {
            room cellar("Cellar",
                    "You are in a dark and damp cellar with a narrow passageway leading north, and\na crawlway to the south. On the west is the bottom of a steep metal ramp which\nis unclimbable.The trap door crashes shut, and you hear someone barring it.");
            rbelowRooms[0] = cellar;
            return;
        }
        else                                        // Dark room
        {
            room cellar("",
                    "You have moved into a dark place. You are likely to be eaten by a grue.");
            rbelowRooms[0] = cellar;
            health--;
            if(health == 0)
            {
                cout << "You have been eaten by a grue and died a horribly painful death! GAME OVER"<<endl<<endl;
                exit(0);
            }
        }
    }

    if(currentLevel == 0 && currentRoom == 7)       // If player is in the attic
    {
        if(lantern)                                 // Normal room
        {
            room attic("Attic",
                            "This is the attic. The only exit is a stairway leading down. A large coil of \nrope is lying in the corner. On the table is nasty-looking knife.");
                attic.setHiddenItem("rope");
                attic.setHiddenItem("knife");
            raboveRooms[7] = attic;
            return;
        }
        else                                        // Dark room
        {
            room attic("Attic",
                            "You have moved into a dark place. You are likely to be eaten by a grue.");
            raboveRooms[7] = attic;
            health--;
            if(health == 0)
            {
                cout << "You have been eaten by a grue and died a horribly painful death! GAME OVER"<<endl<<endl;
                exit(0);
            }
        }
    }
}
