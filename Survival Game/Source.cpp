#include <iostream>
#include <sstream>
#include <time.h>

using namespace std;

class Player {
public:
    Player(int x, int y) {
        health = MAX_HEALTH;
        hunger = MAX_HUNGER;
        thirst = MAX_THIRST;

        this->x = x;
        this->y = y;
        this->score = 0;
    }

    int getScore() const {
        return score;
    }

    void takeDamage(int val) {
        this->health -= val;
        if (this->health < 0) this->health = 0;
    }

    void takeTurn() {
        this->thirst--;
        this->hunger--;

        if (this->thirst <= 0) {
            this->health--;
            this->thirst = 0;
        }

        if (this->hunger <= 0) {
            this->health--;
            this->hunger = 0;
        }

        this->score++;
    }

    string getStats() const {
        stringstream ss;
        ss << "============\n"
            << "Health: " << this->health << "\n"
            << "Hunger: " << this->hunger << "\n"
            << "Thirst: " << this->thirst << "\n"
            << "============\n";
        return ss.str();
    }

    bool isAlive() const {
        return this->health > 0;
    }

    void increaseThrist(int val) {
        this->thirst = this->thirst + val;
        if (this->thirst > MAX_THIRST) this->thirst = MAX_THIRST;
    }

    void increaseHealth(int val) {
        this->health = this->health + val;
        if (this->health > MAX_HEALTH) this->health = MAX_HEALTH;
    }
    void decreaseThirst(int val) {
        this->thirst = this->thirst - val;
        if (this->thirst <= 0) this->thirst = 0;
    }

    void decreaseHunger(int val) {
        this->hunger = this->hunger - val;
        if (this->hunger <= 0) this->hunger = 0;
    }

    void decreaseHealth(int val) {
        this->health = this->health - val;
        if (this->health <= 0) this->health = 0;
    }

    void increaseHunger(int val) {
        this->hunger += val;
        if (this->hunger > MAX_HUNGER) this->hunger = MAX_HUNGER;
    }

    int x, y;
private:
    int health, hunger, thirst, score;
    const int MAX_HEALTH = 3;
    const int MAX_HUNGER = 5;
    const int MAX_THIRST = 3;
};

class Land {
public:
    virtual string getDescription() = 0;
    virtual string visit(Player& player) = 0;
};

// TODO: Define at least 3 more types of derivded land types
// TODO: Add some unique effect to each new type

class Forest : public Land {
public:
    string getDescription() {
        return "a densely wooded forest.";
    }

    string visit(Player& player) {
        int randomNum = rand() % 100;

        if (randomNum > 74) {
            player.takeDamage(1);
            return "You are attacked by a bear while foraging for berries.";
        }
        else {
            player.increaseHunger(1);
            return "You forage for berries in the woods and eat a few.";
        }
    }
};

class Lake : public Land {
public:
    string getDescription() {
        return "a clear sparkling lake.";
    }

    string visit(Player& player) {
        player.increaseThrist(2);
        return "You visit the lake and drink its clean water";
    }
};

class Desert : public Land {
    public:
        string getDescription() {
            return "a dusty dry desert";
        }

        string visit(Player& player) {
            player.decreaseThirst(2);
            return "You visit the desert and become very thirsty";
        }
};

class Tropical_Island : public Land {
    public:
        string getDescription() {
            return "a relaxing tropical island";
        }

        string visit(Player & player) {
            int randomNum = rand() % 100;
            
            if (randomNum > 98) {
                player.decreaseHealth(100);
                return "A tsunami hits the island and you drown";
            }

            else if (randomNum > 59) {
                player.decreaseHealth(1);
                return "You are attacked by a seagull";
            }

            else if (randomNum > 49) {
                player.decreaseHunger(2);
                return "You eat a mysterious red fruit and get food poisoning";
            }

            else{
                player.increaseHunger(2);
                player.increaseHealth(1);
                return "You eat a mysterious green fruit and satisfy your hunger";
            }
        }
};
 
class City : public Land {
    string getDescription() {
        return "a large bustling city";
    }

    string visit(Player& player) {
        int randNum = rand() % 100;

        if (randNum > 84) {
            player.decreaseHealth(2);
            return "You get in a fight with Dwayne 'the rock' Johnson";
        }

        else if (randNum > 74) {
            player.decreaseThirst(1);
            player.increaseHealth(1);
            return "You enter into a bar for a drink";
        }

        else if (randNum > 49) {
            player.increaseThrist(2);
            player.increaseHunger(2);
            return "You drink a McDonald's Sprit and eat a Big Mac";
        }

        else {
            player.increaseHunger(2);
            return "You go to Burger King and eat a Whopper";
        }
    }
};


const int MAP_SIZE = 20;
Land* map[MAP_SIZE][MAP_SIZE];

void populateMap() {
    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            // TODO: Modify this code to add your new land types
            int randomNum = rand() % 5;
            switch (randomNum) {
            case 0: // Forest
                map[i][j] = new Forest;
                break;
            case 1: // Lake
                map[i][j] = new Lake;
                break;
            case 2: //Desert
                map[i][j] = new Desert;
                break;
            case 3: //Tropical Island
                map[i][j] = new Tropical_Island;
                break;
            case 4: //City
                map[i][j] = new City;
                break;
            default:
                cout << "Invalid land type selected" << endl;
                break;
            }
        }
    }
}

int main() {
    srand(time(0));

    populateMap();

    Player player(MAP_SIZE / 2, MAP_SIZE / 2);

    cout << "You wake up and find yourself lost in the middle of a strange wilderness." << endl;

    // TODO: Handle boundary conditions (e.g., if index out of bounds north, you index the south-most location)

    while (player.isAlive()) {
        bool validInput = false;
        cout << player.x << ", " << player.y << endl;

        //Checks North
        if (player.y == MAP_SIZE - 1) cout << "To the north you see " << map[player.x][player.y - (MAP_SIZE - 1)]->getDescription() << endl;
        else cout << "To the north you see " << map[player.x][player.y + 1]->getDescription() << endl;
        
        // Checks East
        if(player.x == MAP_SIZE - 1) cout << "To the east you see " << map[player.x - (MAP_SIZE -1)][player.y]->getDescription() << endl;
        else cout << "To the east you see " << map[player.x + 1][player.y]->getDescription() << endl;

        // Checks South
        if (player.y == 0) cout << "To the south you see " << map[player.x][player.y + (MAP_SIZE - 1)]->getDescription() << endl;
        else cout << "To the south you see " << map[player.x][player.y - 1]->getDescription() << endl;

        //Checks West
        if (player.x == 0) cout << "To the west you see " << map[player.x + (MAP_SIZE - 1)][player.y]->getDescription() << endl;
        else cout << "To the west you see " << map[player.x - 1][player.y]->getDescription() << endl;

        char userInput;
      
        while (validInput == false) { //Loops until the user enters a valid input
            cout << "Which way will you go? Enter N, E, S, or W:" << endl;
            cin >> userInput;
            cout << endl;
            if (userInput == 'N' || userInput == 'S' || userInput == 'E' || userInput == 'W') validInput = true;
            if (!validInput) cout << "Invalid input please enter a valid direction" << endl;
        }
        
        switch (userInput) {
        case 'N':
            if (player.y == MAP_SIZE - 1) player.y = player.y - MAP_SIZE; //check if the player is at the top of the map
            player.y = player.y + 1;
            break;
        case 'E':
            if (player.x == MAP_SIZE - 1) player.x = player.x - MAP_SIZE; // checks if the player is at the extreme right
            player.x = player.x + 1;
            break;
        case 'S':
            if (player.y == 0)
                player.y = player.y + MAP_SIZE; // checks if the player is at the bottom of the map
            player.y = player.y - 1;
            break;
        case 'W':
            if (player.x == 0) player.x = player.x + MAP_SIZE; //checks if the palyer is at the extreme left of the map
            player.x = player.x - 1;
            break;
        default:
            break;
        }

        cout << map[player.x][player.y]->visit(player) << endl;
        cout << player.getStats() << endl;
        player.takeTurn();
    }

    cout << player.getStats() << endl;
    cout << "You died." << endl;
    cout << player.getScore() << endl;

    return 0;
}