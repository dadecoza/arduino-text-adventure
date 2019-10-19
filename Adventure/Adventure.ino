/*
 *
 * The Abandoned Farm House Adventure
 *
 * Jeff Tranter <tranter@pobox.com>
 *
 * Written in standard C but designed to run on the Apple Replica 1
 * or Apple II using the CC65 6502 assembler.
 *
 * Copyright 2012-2015 Jeff Tranter
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Revision History:
 *
 * Version  Date         Comments
 * -------  ----         --------
 * 0.0      13 Mar 2012  First alpha version
 * 0.1      18 Mar 2012  First beta version
 * 0.9      19 Mar 2012  First public release
 * 1.0      06 Sep 2015  Lower case and other Apple II improvements.
 *
 */

/*
 * Ported to Arduino by
 * Johannes le Roux <dade@dade.co.za>
 * 
 * 19 Oct 2019
 * 
 */
 
/* CONSTANTS */

/* Maximum number of items user can carry */
#define MAXITEMS 5

/* Number of locations */
#define NUMLOCATIONS 32

/* TYPES */

/* Directions */
typedef enum {
    North,
    South,
    East,
    West,
    Up,
    Down
} Direction_t;

/* Items */
typedef enum {
    NoItem,
    Key,
    Pitchfork,
    Flashlight,
    Lamp,
    Oil,
    Candybar,
    Bottle,
    Doll,
    ToyCar,
    Matches,
    GoldCoin,
    SilverCoin,
    StaleMeat,
    Book,
    Cheese,
    OldRadio,
    LastItem=OldRadio
} Item_t;

/* Locations */
typedef enum {
    NoLocation,
    Driveway1,
    Driveway2,
    Driveway3,
    Driveway4,
    Driveway5,
    Garage,
    WorkRoom,
    Hayloft,
    Kitchen,
    DiningRoom,
    BottomStairs,
    DrawingRoom,
    Study,
    TopStairs,
    BoysBedroom,
    GirlsBedroom,
    MasterBedroom,
    ServantsQuarters,
    LaundryRoom,
    FurnaceRoom,
    VacantRoom,
    Cistern,
    Tunnel,
    Woods24,
    Woods25,
    Woods26,
    WolfTree,
    Woods28,
    Woods29,
    Woods30,
    Woods31,
} Location_t;

/* TABLES */

/* Names of directions */
const char DescriptionOfDirection_0[] PROGMEM = "north";
const char DescriptionOfDirection_1[] PROGMEM = "south";
const char DescriptionOfDirection_2[] PROGMEM = "east";
const char DescriptionOfDirection_3[] PROGMEM = "west";
const char DescriptionOfDirection_4[] PROGMEM = "up";
const char DescriptionOfDirection_5[] PROGMEM = "down";
const char *const DescriptionOfDirection[] PROGMEM = { DescriptionOfDirection_0, DescriptionOfDirection_1, DescriptionOfDirection_2, DescriptionOfDirection_3, DescriptionOfDirection_4,  DescriptionOfDirection_5};

/* Names of items */
const char DescriptionOfItem_0[] PROGMEM = "";
const char DescriptionOfItem_1[] PROGMEM = "key";
const char DescriptionOfItem_2[] PROGMEM = "pitchfork";
const char DescriptionOfItem_3[] PROGMEM = "flashlight";
const char DescriptionOfItem_4[] PROGMEM = "lamp";
const char DescriptionOfItem_5[] PROGMEM = "oil";
const char DescriptionOfItem_6[] PROGMEM = "candybar";
const char DescriptionOfItem_7[] PROGMEM = "bottle";
const char DescriptionOfItem_8[] PROGMEM = "doll";
const char DescriptionOfItem_9[] PROGMEM = "toy car";
const char DescriptionOfItem_10[] PROGMEM = "matches";
const char DescriptionOfItem_11[] PROGMEM = "gold coin";
const char DescriptionOfItem_12[] PROGMEM = "silver coin";
const char DescriptionOfItem_13[] PROGMEM = "stale meat";
const char DescriptionOfItem_14[] PROGMEM = "book";
const char DescriptionOfItem_15[] PROGMEM = "cheese";
const char DescriptionOfItem_16[] PROGMEM = "old radio";
const char *const DescriptionOfItem[] PROGMEM = {DescriptionOfItem_0, DescriptionOfItem_1, DescriptionOfItem_2, DescriptionOfItem_3, DescriptionOfItem_4, DescriptionOfItem_5, DescriptionOfItem_6, DescriptionOfItem_7, DescriptionOfItem_8, DescriptionOfItem_9, DescriptionOfItem_10, DescriptionOfItem_11, DescriptionOfItem_12, DescriptionOfItem_13, DescriptionOfItem_14, DescriptionOfItem_15, DescriptionOfItem_16};

/* Names of locations */
const char DescriptionOfLocation_0[] PROGMEM = "";
const char DescriptionOfLocation_1[] PROGMEM = "in the driveway near your car";
const char DescriptionOfLocation_2[] PROGMEM = "in the driveway";
const char DescriptionOfLocation_3[] PROGMEM = "in front of the garage";
const char DescriptionOfLocation_4[] PROGMEM = "in front of the barn";
const char DescriptionOfLocation_5[] PROGMEM = "at the door to the house";
const char DescriptionOfLocation_6[] PROGMEM = "in the garage";
const char DescriptionOfLocation_7[] PROGMEM = "in the workroom of the barn";
const char DescriptionOfLocation_8[] PROGMEM = "in the hayloft of the barn";
const char DescriptionOfLocation_9[] PROGMEM = "in the kitchen";
const char DescriptionOfLocation_10[] PROGMEM = "in the dining room";
const char DescriptionOfLocation_11[] PROGMEM = "at the bottom of the stairs";
const char DescriptionOfLocation_12[] PROGMEM = "in the drawing room";
const char DescriptionOfLocation_13[] PROGMEM = "in the study";
const char DescriptionOfLocation_14[] PROGMEM = "at the top of the stairs";
const char DescriptionOfLocation_15[] PROGMEM = "in a boy's bedroom";
const char DescriptionOfLocation_16[] PROGMEM = "in a girl's bedroom";
const char DescriptionOfLocation_17[] PROGMEM = "in the master bedroom next to\na bookcase";
const char DescriptionOfLocation_18[] PROGMEM = "in the servant's quarters";
const char DescriptionOfLocation_19[] PROGMEM = "in the basement laundry room";
const char DescriptionOfLocation_20[] PROGMEM = "in the furnace room";
const char DescriptionOfLocation_21[] PROGMEM = "in a vacant room next to a\r\nlocked door";
const char DescriptionOfLocation_22[] PROGMEM = "in the cistern";
const char DescriptionOfLocation_23[] PROGMEM = "in an underground tunnel. There are rats here";
const char DescriptionOfLocation_24[] PROGMEM = "in the woods near a trapdoor";
const char DescriptionOfLocation_25[] PROGMEM = "in the woods";
const char DescriptionOfLocation_26[] PROGMEM = "in the woods";
const char DescriptionOfLocation_27[] PROGMEM = "in the woods next to a tree";
const char DescriptionOfLocation_28[] PROGMEM = "in the woods";
const char DescriptionOfLocation_29[] PROGMEM = "in the woods";
const char DescriptionOfLocation_30[] PROGMEM = "in the woods";
const char DescriptionOfLocation_31[] PROGMEM = "in the woods";
const char *const DescriptionOfLocation[] PROGMEM = { DescriptionOfLocation_0, DescriptionOfLocation_1, DescriptionOfLocation_2, DescriptionOfLocation_3, DescriptionOfLocation_4, DescriptionOfLocation_5, DescriptionOfLocation_6, DescriptionOfLocation_7, DescriptionOfLocation_8, DescriptionOfLocation_9, DescriptionOfLocation_10, DescriptionOfLocation_11, DescriptionOfLocation_12, DescriptionOfLocation_13, DescriptionOfLocation_14, DescriptionOfLocation_15, DescriptionOfLocation_16, DescriptionOfLocation_17, DescriptionOfLocation_18, DescriptionOfLocation_19, DescriptionOfLocation_20, DescriptionOfLocation_21, DescriptionOfLocation_22, DescriptionOfLocation_23, DescriptionOfLocation_24, DescriptionOfLocation_25, DescriptionOfLocation_26, DescriptionOfLocation_27, DescriptionOfLocation_28, DescriptionOfLocation_29, DescriptionOfLocation_30, DescriptionOfLocation_31 };

/* Other Strings */
const char String_0[] PROGMEM = "You pull back a book and the bookcase\nopens up to reveal a secret room.";
const char String_1[] PROGMEM = "I don't see it here.";
const char String_2[] PROGMEM = "It is a very old book entitled\n\"Apple 1 operation manual\".";
const char String_3[] PROGMEM = "It doesn't have any batteries.";
const char String_4[] PROGMEM = "It is a nice toy car.\nYour grandson Matthew would like it.";
const char String_5[] PROGMEM = "It is a 1940 Zenith 8-S-563 console\nwith an 8A02 chassis. You'd turn it on\nbut the electricity is off.";
const char String_6[] PROGMEM = "You see nothing special about it.";
const char String_7[] PROGMEM = "You insert the key in the door and it\nopens, revealing a tunnel.";
const char String_8[] PROGMEM = "You jab the wolf with the pitchfork.\nIt howls and runs away.";
const char String_9[] PROGMEM = "You show Matthew the toy car and he\ncomes down to take it. You take Matthew\nin your arms and carry him home.";
const char String_10[] PROGMEM = "You fill the lamp with oil.";
const char String_11[] PROGMEM = "You don't have anything to use it with.";
const char String_12[] PROGMEM = "You light the lamp. You can see!";
const char String_13[] PROGMEM = "You can't light the lamp. It needs oil.";
const char String_14[] PROGMEM = "Nothing here to light";
const char String_15[] PROGMEM = "That hit the spot. You no longer feel\nhungry.";
const char String_16[] PROGMEM = "You fill the bottle with water from the\ncistern and take a drink. You no longer\nfeel thirsty.";
const char String_17[] PROGMEM = "The bottle is empty. If only you had\nsome water to fill it!";
const char String_18[] PROGMEM = "The meat looked and tasted bad. You\nfeel very sick and pass out.";
const char String_19[] PROGMEM = "Nothing happens";
const char String_20[] PROGMEM = "It will be getting dark soon. You need\nsome kind of light or soon you won't\nbe able to see.";
const char String_21[] PROGMEM = "It is dark out and you have no light.\nYou stumble around for a while and\nthen fall, hit your head, and pass out.";
const char String_22[] PROGMEM = "You are getting very thirsty.\nYou need to get a drink soon.";
const char String_23[] PROGMEM = "You are getting very hungry.\nYou need to find something to eat.";
const char String_24[] PROGMEM = "You pass out due to thirst.";
const char String_25[] PROGMEM = "You pass out from hunger.";
const char String_26[] PROGMEM = "The rats go after the cheese.";
const char String_27[] PROGMEM = "The rats are coming towards you!";
const char String_28[] PROGMEM = "The rats attack and you pass out.";
const char String_29[] PROGMEM = "A wolf is circling around the tree.\nMatthew is up in the tree. You have to\nsave him! If only you had some kind of\nweapon!";
const char String_30[] PROGMEM = "Matthew is afraid to come\ndown from the tree. If only you had\nsomething to coax him with.";
const char String_31[] PROGMEM = "Congratulations! You succeeded and won\nthe game. I hope you had as much fun\nplaying the game as I did creating it.\n- Jeff Tranter <tranter@pobox.com>";
const char *const StringTable[] PROGMEM = {String_0, String_1, String_2, String_3, String_4, String_5, String_6, String_7, String_8, String_9, String_10, String_11, String_12, String_13, String_14, String_15, String_16, String_17, String_18, String_19, String_20, String_21, String_22, String_23, String_24, String_25, String_26, String_27, String_28, String_29, String_30, String_31};

/* DATA */

/* Inventory of what player is carrying */
Item_t Inventory[MAXITEMS];

/* Location of each item. Index is the item number, returns the location. 0 if item is gone */
Location_t locationOfItem[LastItem+1];

/* Map. Given a location and a direction to move, returns the location it connects to, or 0 if not a valid move. */
const Direction_t Move[][6] PROGMEM = {
    /* N  S  E  W  U  D */
    {Direction_t(0), Direction_t(0), Direction_t(0), Direction_t(0), Direction_t(0), Direction_t(0)},
    {Direction_t(2), Direction_t(0), Direction_t(0), Direction_t(0), Direction_t(0), Direction_t(0)},
    {Direction_t(4), Direction_t(1), Direction_t(3), Direction_t(5), Direction_t(0), Direction_t(0)},
    {Direction_t(0), Direction_t(0), Direction_t(6), Direction_t(2), Direction_t(0), Direction_t(0)},
    {Direction_t(7), Direction_t(2), Direction_t(0), Direction_t(0), Direction_t(0), Direction_t(0)},
    {Direction_t(0), Direction_t(0), Direction_t(2), Direction_t(9), Direction_t(0), Direction_t(0)},
    {Direction_t(0), Direction_t(0), Direction_t(0), Direction_t(3), Direction_t(0), Direction_t(0)},
    {Direction_t(0), Direction_t(4), Direction_t(0), Direction_t(0), Direction_t(8), Direction_t(0)},
    {Direction_t(0), Direction_t(0), Direction_t(0), Direction_t(0), Direction_t(0), Direction_t(7)},
    {Direction_t(0), Direction_t(10), Direction_t(5), Direction_t(0), Direction_t(0), Direction_t(19)},
    {Direction_t(9), Direction_t(0), Direction_t(0), Direction_t(11), Direction_t(0), Direction_t(0)},
    {Direction_t(0), Direction_t(0), Direction_t(10), Direction_t(12), Direction_t(14), Direction_t(0)},
    {Direction_t(13), Direction_t(0), Direction_t(11), Direction_t(0), Direction_t(0), Direction_t(0)},
    {Direction_t(0), Direction_t(12), Direction_t(0), Direction_t(0), Direction_t(0), Direction_t(0)},
    {Direction_t(16), Direction_t(0), Direction_t(15), Direction_t(17), Direction_t(0), Direction_t(11)},
    {Direction_t(0), Direction_t(0), Direction_t(0), Direction_t(14), Direction_t(0), Direction_t(0)},
    {Direction_t(0), Direction_t(14), Direction_t(0), Direction_t(0), Direction_t(0), Direction_t(0)},
    {Direction_t(0), Direction_t(0), Direction_t(14), Direction_t(0), Direction_t(0), Direction_t(0)},
    {Direction_t(0), Direction_t(0), Direction_t(0), Direction_t(0), Direction_t(0), Direction_t(13)},
    {Direction_t(0), Direction_t(0), Direction_t(0), Direction_t(20), Direction_t(9), Direction_t(0)},
    {Direction_t(21), Direction_t(0), Direction_t(19), Direction_t(0), Direction_t(0), Direction_t(0)},
    {Direction_t(0), Direction_t(20), Direction_t(0), Direction_t(22), Direction_t(0), Direction_t(0)},
    {Direction_t(0), Direction_t(0), Direction_t(21), Direction_t(0), Direction_t(0), Direction_t(0)},
    {Direction_t(24), Direction_t(21), Direction_t(0), Direction_t(0), Direction_t(0), Direction_t(0)},
    {Direction_t(29), Direction_t(23), Direction_t(0), Direction_t(26), Direction_t(0), Direction_t(0)},
    {Direction_t(26), Direction_t(0), Direction_t(24), Direction_t(0), Direction_t(0), Direction_t(0)},
    {Direction_t(27), Direction_t(25), Direction_t(29), Direction_t(0), Direction_t(0), Direction_t(0)},
    {Direction_t(0), Direction_t(26), Direction_t(28), Direction_t(0), Direction_t(0), Direction_t(0)},
    {Direction_t(0), Direction_t(29), Direction_t(31), Direction_t(27), Direction_t(0), Direction_t(0)},
    {Direction_t(28), Direction_t(24), Direction_t(30), Direction_t(26), Direction_t(0), Direction_t(0)},
    {Direction_t(31), Direction_t(0), Direction_t(0), Direction_t(29), Direction_t(0), Direction_t(0)},
    {Direction_t(0), Direction_t(30), Direction_t(0), Direction_t(29), Direction_t(0), Direction_t(0)}
};

/* Current location */
int currentLocation;

/* Number of turns played in game */
int turnsPlayed;

/* True if player has lit the lamp. */
int lampLit;

/* True if lamp filled with oil. */
int lampFilled;

/* True if player ate food. */
int ateFood;

/* True if player drank water. */
int drankWater;

/* Incremented each turn you are in the tunnel. */
int ratAttack;

/* Tracks state of wolf attack */
int wolfState;

/* True if tunnel is revealed */
int tunnelRevealed = 0;

/* True if secret room is revealed */
int roomRevealed = 0;

/* Set when game is over */
int gameOver;

const char IntroText[] PROGMEM = "     Abandoned Farmhouse Adventure\r\n           By Jeff Tranter\r\n\r\nYour three-year-old grandson has gone\r\nmissing and was last seen headed in the\r\ndirection of the abandoned family farm.\r\nIt's a dangerous place to play. You\r\nhave to find him before he gets hurt,\r\nand it will be getting dark soon...\r\n";

const char helpString[] PROGMEM = "Valid commands:\r\ngo east/west/north/south/up/down \r\nlook\r\nuse <object>\r\nexamine <object>\r\ntake <object>\r\ndrop <object>\r\ninventory\r\nhelp\r\nquit\r\nYou can abbreviate commands and\r\ndirections to the first letter.\r\nType just the first letter of\r\na direction to move.\r\n";

/* Line of user input */
char buffer[40];

/* Buffer for progmem strings */
char pbuffer[200];

/* Display string */
void xprint(String str) {
  Serial.print(str);
}

/* Move to next line on screen. */
void xprintln() {
  xprint("\r\n");
}

/* Displpay string and move to next line */
void xprintln(String str) {
  xprint(str);
  xprintln();
}

/* Read serial input until enter is pressed. */
void xinput() {
  int incomingByte = 0;
  int inx = 0;
  do {
     if (Serial.available() > 0) {
        // read the incoming byte:
        incomingByte = Serial.read();
        buffer[inx] = incomingByte;
        inx++;
     }
  } while (incomingByte != 13);
  /* Remove trailing newline */
  buffer[inx-1] = '\0';
  xprintln();
}

/* Display character on the screen.*/
void xwrite(char c) {
  Serial.write(c);
}

/* Clear the screen */
void clearScreen()
{
  xwrite(12);
}

/* Return 1 if carrying an item */
int carryingItem(char *item)
{
    int i;

    for (i = 0; i < MAXITEMS; i++) {
        if ((Inventory[i] != 0) && (!strcasecmp(getDescriptionOfItem(Inventory[i]), item)))
            return 1;
    }
    return 0;
}

/* Return 1 if item it at current location (not carried) */
int itemIsHere(char *item)
{
    int i;

    /* Find number of the item. */
    for (i = 1; i <= LastItem; i++) {
        if (!strcasecmp(item, getDescriptionOfItem(i))) {
            /* Found it, but is it here? */
            if (locationOfItem[i] == currentLocation) {
                return 1;
            } else {
                return 0;
            }
        }
    }
    return 0;
}

/* Inventory command */
void doInventory()
{
    int i;
    int found = 0;

    xprintln("You are carrying:");
    for (i = 0; i < MAXITEMS; i++) {
        if (Inventory[i] != 0) {
            xprintln(getDescriptionOfItem(Inventory[i]));
            found = 1;
        }
    }
    if (!found)
        xprintln("  nothing");
}

/* Help command */
void doHelp()
{
    char c;
    int j = 0;
    do {
      c = (char) pgm_read_byte(&helpString[j++]);
      xwrite(c);
    } while (c!='\0');
}

/* Intro screen */
void doIntro()
{
    char c;
    int j = 0;
    do {
      c = (char) pgm_read_byte(&IntroText[j++]);
      xwrite(c);
    } while (c!='\0');
}

/* Helper functions for progmem tables */
char* getDescriptionOfLocation(int inx) {
  strcpy_P(pbuffer, (char *)pgm_read_word(&(DescriptionOfLocation[inx])));
  return pbuffer;
}

char* getDescriptionOfItem(int inx) {
  strcpy_P(pbuffer, (char *)pgm_read_word(&(DescriptionOfItem[inx])));
  return pbuffer;
}

char* getDescriptionOfDirection(int inx) {
  strcpy_P(pbuffer, (char *)pgm_read_word(&(DescriptionOfDirection[inx])));
  return pbuffer;
}

int getLocationDirection(int dir) {
  if ((currentLocation == VacantRoom) && (dir == North) && (tunnelRevealed == 1)) {
    return 23;
  }

  if ((currentLocation == MasterBedroom) && (dir == North) && (roomRevealed == 1)) {
    return 18;
  }
  
  return pgm_read_byte(&Move[currentLocation][dir]);
}

void printString(int inx) {
  strcpy_P(pbuffer, (char *)pgm_read_word(&(StringTable[inx])));
  xprintln(pbuffer);
}

/* Look command */
void doLook()
{
    int i, loc, seen;

    xprint("You are ");
    xprint(getDescriptionOfLocation(currentLocation));
    xprintln(".");
    
    seen = 0;
    xprintln("You see:");
    for (i = 1; i <= LastItem; i++) {
        if (locationOfItem[i] == currentLocation) {
            xprint("  "); xprintln(getDescriptionOfItem(i));
            seen = 1;
        }
    }
    if (!seen)
        xprintln("  nothing special");

    xprintln("You can go:");

    for (i = North; i <= Down; i++) {
        loc = getLocationDirection(i);
        if (loc != 0) {
            xprint("  "); xprintln(getDescriptionOfDirection(i));
        }
    }
    xprintln();
}

/* Quit command */
void doQuit()
{
    xprintln("Are you sure you want to quit (y/n)?");
    xinput();
    if (tolower(buffer[0]) == 'y') {
        gameOver = 1;
    }
}

/* Drop command */
void doDrop()
{
    int i;
    char *sp;
    char *item;

    /* Command line should be like "D[ROP] ITEM" Item name will be after after first space. */
    sp = strchr(buffer, ' ');
    if (sp == NULL) {
        xprintln("Drop what?");
        return;
    }

    item = sp + 1;

    /* See if we have this item */
    for (i = 0; i < MAXITEMS; i++) {
        if ((Inventory[i] != 0) && (!strcasecmp(getDescriptionOfItem(Inventory[i]), item))) {
            /* We have it. Add to location. */
            locationOfItem[Inventory[i]] = Location_t(currentLocation);
            /* And remove from inventory */
            Inventory[i] = Item_t(0);
            xprint("Dropped "); xprint(item); xprintln(".");
            ++turnsPlayed;
            return;
        }
    }
    /* If here, don't have it. */
    xprint("Not carrying "); xprint(item); xprintln(".");
}

/* Take command */
void doTake()
{
    int i, j;
    char *sp;
    char *item;

    /* Command line should be like "T[AKE] ITEM" Item name will be after after first space. */
    sp = strchr(buffer, ' ');
    if (sp == NULL) {
        xprintln("Take what?");
        return;
    }

    item = sp + 1;

    if (carryingItem(item)) {
        xprintln("Already carrying it.");
        return;
    }

    /* Find number of the item. */
    for (i = 1; i <= LastItem; i++) {
        if (!strcasecmp(item, getDescriptionOfItem(i))) {
            /* Found it, but is it here? */
            if (locationOfItem[i] == currentLocation) {
            /* It is here. Add to inventory. */
            for (j = 0; j < MAXITEMS; j++) {
                if (Inventory[j] == 0) {
                    Inventory[j] = Item_t(i);
                    /* And remove from location. */
                    locationOfItem[i] = NoLocation;
                    xprint("Took ");
                    xprint(item);
                    xprintln(".");
                    ++turnsPlayed;
                    return;
                }
            }

            /* Reached maximum number of items to carry */
            xprintln("You can't carry any more. Drop something.");
            return;
            }
        }
    }

    /* If here, don't see it. */
    xprint("I see no "); xprint(item); xprintln(" here.");
}

/* Go command */
void doGo()
{
    char *sp;
    char dirChar;
    Direction_t dir;

    /* Command line should be like "G[O] N[ORTH]" Direction will be
       the first letter after a space. Or just a single letter
       direction N S E W U D or full directon NORTH etc. */

    sp = strrchr(buffer, ' ');
    if (sp != NULL) {
        dirChar = *(sp+1);
    } else {
        dirChar = buffer[0];
    }
    dirChar = tolower(dirChar);

    if (dirChar == 'n') {
        dir = North;
    } else if (dirChar == 's') {
        dir = South;
    } else if (dirChar == 'e') {
        dir = East;
    } else if (dirChar == 'w') {
        dir = West;
    } else if (dirChar == 'u') {
        dir = Up;
    } else if (dirChar == 'd') {
        dir = Down;
    } else {
        xprintln("Go where?");
        return;
    }
    int location = getLocationDirection(dir);
    
    if (location == 0) {
        xprint("You can't go "); xprint(getDescriptionOfDirection(dir)); xprintln(" from here.");
        return;
    }

    /* We can move */
    currentLocation = location;
    xprint("You are "); xprint(getDescriptionOfLocation(currentLocation)); xprintln(".");
    ++turnsPlayed;
}

/* Examine command */
void doExamine()
{
    char *sp;
    char *item;

    /* Command line should be like "E[XAMINE] ITEM" Item name will be after after first space. */
    sp = strchr(buffer, ' ');
    if (sp == NULL) {
        printf("Examine what?\n");
        return;
    }

    item = sp + 1;
    ++turnsPlayed;

    /* Examine bookcase - not an object */
    if (!strcasecmp(item, "bookcase")) {
        printString(0); // You pull back a book and the bookcase opens up to reveal a secret room.
        roomRevealed = 1;
        return;
    }

    /* Make sure item is being carried or is in the current location */
    if (!carryingItem(item) && !itemIsHere(item)) {
        printString(1); // I don't see it here.
        return;
    }

    /* Examine Book */
    if (!strcasecmp(item, "book")) {
        printString(2); // It is a very old book entitled "Apple 1 operation manual".
        return;
    }

    /* Examine Flashlight */
    if (!strcasecmp(item, "flashlight")) {
        printString(3); // It doesn't have any batteries.
        return;
    }

    /* Examine toy car */
    if (!strcasecmp(item, "toy car")) {
        printString(4); // It is a nice toy car. Your grandson Matthew would like it.
        return;
    }

    /* Examine old radio */
    if (!strcasecmp(item, "old radio")) {
        printString(5); // It is a 1940 Zenith 8-S-563 console with an 8A02 chassis. You'd turn it on but the electricity is off.
        return;
    }

   /* Nothing special about this item */
   printString(6); // You see nothing special about it.
}

/* Use command */
void doUse()
{
    char *sp;
    char *item;

    /* Command line should be like "U[SE] ITEM" Item name will be after after first space. */
    sp = strchr(buffer, ' ');
    if (sp == NULL) {
        xprintln("Use what?");
        return;
    }

    item = sp + 1;

    /* Make sure item is being carried or is in the current location */
    if (!carryingItem(item) && !itemIsHere(item)) {
        printString(1); // I don't see it here.
        return;
    }

    ++turnsPlayed;

    /* Use key */
    if (!strcasecmp(item, "key") && (currentLocation == VacantRoom)) {
        printString(7); // You insert the key in the door and it opens, revealing a tunnel.
        tunnelRevealed = 1;
        return;
    }

    /* Use pitchfork */
    if (!strcasecmp(item, "pitchfork") && (currentLocation == WolfTree) && (wolfState == 0)) {
        printString(8); // You jab the wolf with the pitchfork. It howls and runs away.
        wolfState = 1;
        return;
    }

    /* Use toy car */
    if (!strcasecmp(item, "toy car") && (currentLocation == WolfTree && wolfState == 1)) {
        printString(9); // You show Matthew the toy car and he comes down to take it. You take Matthew in your arms and carry him home.
        wolfState = 2;
        return;
    }

    /* Use oil */
    if (!strcasecmp(item, "oil")) {
        if (carryingItem((char *)"lamp")) {
            printString(10); // You fill the lamp with oil.
            lampFilled = 1;
            return;
        } else {
            printString(11); // You don't have anything to use it with.
            return;
        }
    }

    /* Use matches */
    if (!strcasecmp(item, "matches")) {
        if (carryingItem((char *)"lamp")) {
            if (lampFilled) {
                printString(12); // You light the lamp. You can see!
                lampLit = 1;
                return;
            } else {
                printString(13); // You can't light the lamp. It needs oil.
                return;
            }
        } else {
            printString(14); // Nothing here to light
        }
    }

    /* Use candybar */
    if (!strcasecmp(item, "candybar")) {
        printString(15); // That hit the spot. You no longer feel hungry.
        ateFood = 1;
        return;
    }

    /* Use bottle */
    if (!strcasecmp(item, "bottle")) {
        if (currentLocation == Cistern) {
            printString(16); // You fill the bottle with water from the cistern and take a drink. You no longer feel thirsty.
            drankWater = 1;
            return;
        } else {
            printString(17); // The bottle is empty. If only you had some water to fill it!
            return;
        }
    }

    /* Use stale meat */
    if (!strcasecmp(item, "stale meat")) {
        printString(18); // The meat looked and tasted bad. You feel very sick and pass out.
        gameOver = 1;
        return;
    }

    /* Default */
    printString(19); // Nothing happens
}

/* Prompt user and get a line of input */
void prompt()
{
    xprint("? ");
    xinput();
}

/* Do special things unrelated to command typed. */
void doActions()
{
    if ((turnsPlayed == 10) && !lampLit) {
        printString(20); // It will be getting dark soon. You need some kind of light or soon you won't be able to see.
    }

    if ((turnsPlayed >= 60) && (!lampLit || (!itemIsHere((char *)"lamp") && !carryingItem((char *)"lamp")))) {
        printString(21); // It is dark out and you have no light. You stumble around for a while and then fall, hit your head, and pass out.
        gameOver = 1;
        return;
    }

    if ((turnsPlayed == 20) && !drankWater) {
        printString(22); // You are getting very thirsty. You need to get a drink soon.
    }

    if ((turnsPlayed == 30) && !ateFood) {
        printString(23); // You are getting very hungry. You need to find something to eat.
    }

    if ((turnsPlayed == 50) && !drankWater) {
        printString(24); // You pass out due to thirst.
        gameOver = 1;
        return;
    }

    if ((turnsPlayed == 40) && !ateFood) {
        //printf("You pass out from hunger.\n");
        printString(25);
        gameOver = 1;
        return;
    }

    if (currentLocation == Tunnel) {
        if (itemIsHere((char *)"cheese")) {
            //printf("The rats go after the cheese.\n");
            printString(26);
        } else {
            if (ratAttack < 3) {
                //printf("The rats are coming towards you!\n");
                printString(27);
                ++ratAttack;
            } else {
                //printf("The rats attack and you pass out.\n");
                printString(28);
                gameOver = 1;
                return;
            }
        }
    }

    /* wolfState values:  0 - wolf attacking 1 - wolf gone, Matthew in tree. 2 - Matthew safe, you won. Game over. */
    if (currentLocation == WolfTree) {
        switch (wolfState) {
            case 0:
                printString(29); // A wolf is circling around the tree. Matthew is up in the tree. You have to save him! If only you had some kind of weapon!
                break;
            case 1:
                printString(30); // Matthew is afraid to come down from the tree. If only you had something to coax him with.
                break;
            case 2:
                printString(31); // Congratulations! You succeeded and won the game. I hope you had as much fun playing the game as I did creating it. - Jeff Tranter <tranter@pobox.com>
                gameOver = 1;
                return;
                break;
            }
    }
}

/* Set variables to values for start of game */
void initialize()
{
    currentLocation = Driveway1;
    lampFilled = 0;
    lampLit = 0;
    ateFood = 0;
    drankWater = 0;
    ratAttack = 0;
    wolfState = 0;
    turnsPlayed = 0;
    gameOver= 0;

    /* These doors can get changed during game and may need to be reset O*/
    tunnelRevealed = 0;
    roomRevealed = 0;
    
    /* Set inventory to default */
    memset(Inventory, 0, sizeof(Inventory[0])*MAXITEMS);
    Inventory[0] = Flashlight;

    /* Put items in their default locations */
    locationOfItem[0]  = NoLocation;       /* NoItem */
    locationOfItem[1]  = Driveway1;        /* Key */
    locationOfItem[2]  = Hayloft;          /* Pitchfork */
    locationOfItem[3]  = NoLocation;       /* Flashlight */
    locationOfItem[4]  = WorkRoom;         /* Lamp */
    locationOfItem[5]  = Garage;           /* Oil */
    locationOfItem[6]  = Kitchen;          /* Candybar */
    locationOfItem[7]  = Driveway2;        /* Bottle */
    locationOfItem[8]  = GirlsBedroom;     /* Doll */
    locationOfItem[9]  = BoysBedroom;      /* ToyCar */
    locationOfItem[10] = ServantsQuarters; /* Matches */
    locationOfItem[11] = Woods25;          /* GoldCoin */
    locationOfItem[12] = Woods29;          /* SilverCoin */
    locationOfItem[13] = DiningRoom;       /* StaleMeat */
    locationOfItem[14] = DrawingRoom;      /* Book */
    locationOfItem[15] = LaundryRoom;      /* Cheese */
    locationOfItem[16] = MasterBedroom;    /* OldRadio */
}

void setup() {
  Serial.begin(2400);
}

void loop() {
  initialize();
  clearScreen();
  doIntro();
  while (!gameOver) {
    prompt();
    if (buffer[0] == '\0') {
    } else if (tolower(buffer[0]) == 'h') {
      doHelp();
    } else if (tolower(buffer[0]) == 'i') {
      doInventory();
    } else if ((tolower(buffer[0]) == 'g')
       || !strcasecmp(buffer, "n") || !strcasecmp(buffer, "s")
       || !strcasecmp(buffer, "e") || !strcasecmp(buffer, "w")
       || !strcasecmp(buffer, "u") || !strcasecmp(buffer, "d")
       || !strcasecmp(buffer, "north") || !strcasecmp(buffer, "south")
       || !strcasecmp(buffer, "east") || !strcasecmp(buffer, "west")
       || !strcasecmp(buffer, "up") || !strcasecmp(buffer, "down")) {
      doGo();
    } else if (tolower(buffer[0]) == 'l') {
      doLook();
    } else if (tolower(buffer[0]) == 't') {
      doTake();
    } else if (tolower(buffer[0]) == 'e') {
      doExamine();
    } else if (tolower(buffer[0]) == 'u') {
      doUse();
    } else if (tolower(buffer[0]) == 'd') {
      doDrop();
    } else if (tolower(buffer[0]) == 'q') {
      doQuit();
    } else if (!strcasecmp(buffer, "xyzzy")) {
      xprintln("Nice try, but that won't work here.");
    } else {
      xprintln("I don't understand. Try 'help'.");
    }
    /* Handle special actions. */
    doActions();
  }
  
  xprint("Game over after "); xprint(String(turnsPlayed)); xprintln(" turns.");
  xprintln("Press enter to restart.");
  xinput();
}
