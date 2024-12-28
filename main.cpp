#include <iostream>
#include <vector>
#include <unordered_map>
#include <memory>
#include <string>
#include <sstream>
#include <ctime>
#include <random>
class Ant;
class Warrior;
class Drone;
using namespace std;


class Meadow;
template <typename TypeofAnt> class AntFarm;
class Room;

class AntFarmBase
{
public:
    virtual ~AntFarmBase() = default;
    virtual void tick() = 0;
    virtual void displaySummary() = 0;
    virtual void giveResources(const string& Resources, int Amount) = 0;
};
class Meadow
{
private:
    static Meadow* instance;
    int sCount;
    unordered_map<int, shared_ptr<AntFarmBase>> antFarms;

    Meadow(int studentRollNumber)
    {
        sCount= 11;
    }

public:
    static Meadow* getInstance(int studentRollNumber)
    {
        if (instance == nullptr)
            {
            instance = new Meadow(studentRollNumber);
        }
        return instance;
    }

    template<typename TypeofAnt>
    void spawnColony(int x, int y, const string& species)
     {
        int id = antFarms.size() + 1;
        auto newFarm = make_shared<AntFarm<TypeofAnt>>(id, x, y, species);  // Instantiate with specific TypeofAnt
        antFarms[id] = newFarm;
        cout << "Colony " << id << " created at (" << x << ", " << y << ") with species " << species << ".\n";
    }

    shared_ptr<AntFarmBase> getFarmofAnts(int id)
    {
        return antFarms.at(id);
    }

    unordered_map<int, shared_ptr<AntFarmBase>> getFarmofAnts()
    {
        return antFarms;
    }

    int getcount_species() const
     {
        return sCount;
    }

    vector<string> getnames_species() const
    {
        return {
            "Warrior", "Drone", "Queen", "Gatherer", "Killer",
            "Pansy", "Worker", "Soldier", "Scout", "Hunter",
            "Protector"
        };
    }
};

// Initialize static member of Meadow
Meadow* Meadow::instance = nullptr;

// ----- AntBase Class -----
class Ant {
protected:
    string species;
    int health;
    int strength;
    int foodCost;
    bool isResting;

public:
    Ant(string species, int health, int strength, int foodCost)
        : species(species), health(health), strength(strength), foodCost(foodCost), isResting(false) {}

    virtual void Actionpeformance() = 0;

    virtual ~Ant() {}

    string getSpecies() const
    {
        return species;
        }
    int getStrength() const
    {
        return strength;
        }
    int getHealth() const
     {
         return health;
         }
    void reduceHealth(int damage)
     {
         health -= damage;
         }

    bool battle(shared_ptr<Ant> otherAnt)
    {
        if (this->strength > otherAnt->getStrength())
            {
            otherAnt->reduceHealth(this->strength);
            return true;
        }
        return false;
    }

    bool isDead()
    {
        return health <= 0;
    }

    void rest(int food)
     {
        if (food > 0 && !isResting)
            {
            isResting = true;
            cout << species << " is resting and consuming " << foodCost << " food.\n";
        }
    }

    void stopRest()
    {
        isResting = false;
    }

    bool isrestingget() const
    {
        return isResting;
    }
};

// ----- Define 13 Species -----

class Warrior : public Ant
 {
public:
    Warrior(string species)
        : Ant(species, 100, 20, 10) {}

    void Actionpeformance() override
    {
        cout << "Warrior is hunting.\n";
    }
};

class Drone : public Ant
{
public:
    Drone(string species)
        : Ant(species, 50, 10, 5) {}

    void Actionpeformance() override
    {
        cout << "Drone is foraging.\n";
    }
};

class Queen : public Ant
{
public:
    Queen(string species)
        : Ant(species, 200, 5, 0) {}

    void Actionpeformance() override
    {
        cout << "Queen is laying eggs.\n";
    }
};

class Gatherer : public Ant
 {
public:
    Gatherer(string species)
        : Ant(species, 60, 15, 5) {}

    void Actionpeformance() override
    {
        cout << "Gatherer is collecting food.\n";
    }
};

class Killer : public Ant
{
public:
    Killer(string species)
        : Ant(species, 80, 25, 12) {}

    void Actionpeformance() override
    {
        cout << "Killer is hunting prey.\n";
    }
};

class Pansy : public Ant
{
public:
    Pansy(string species)
        : Ant(species, 50, 8, 5) {}

    void Actionpeformance() override
    {
        cout << "Pansy is relaxing.\n";
    }
};

class Worker : public Ant
 {
public:
    Worker(string species)
        : Ant(species, 50, 10, 5) {}

    void Actionpeformance() override
    {
        cout << "Worker is gathering Resourcess.\n";
    }
};

class Soldier : public Ant
{
public:
    Soldier(string species)
        : Ant(species, 90, 18, 10) {}

    void Actionpeformance() override
    {
        cout << "Soldier is protecting the colony.\n";
    }
};

class Scout : public Ant
{
public:
    Scout(string species)
        : Ant(species, 60, 12, 7) {}

    void Actionpeformance() override
    {
        cout << "Scout is exploring the area.\n";
    }
};

class Hunter : public Ant
{
public:
    Hunter(string species)
        : Ant(species, 100, 30, 15) {}

    void Actionpeformance() override
    {
        cout << "Hunter is hunting.\n";
    }
};

class Protector : public Ant
{
public:
    Protector(string species)
        : Ant(species, 120, 15, 10) {}

    void Actionpeformance() override
    {
        cout << "Protector is defending the colony.\n";
    }
};



// ----- roomClass -----
class Room
{
public:
    virtual void build() = 0;  // Every roomtype should implement its own build method
    virtual ~Room() {}
};

class Workerroom: public Room
{
public:
    void build() override
    {
        cout << "Building a worker room...\n";
    }
};

class Warriorroom: public Room
{
public:
    void build() override
    {
        cout << "Building a warrior room...\n";
    }
};

// ----- AntFactory -----
class AntFactory
{
public:
    static shared_ptr<Ant> createAnt(const string& type, const string& species)
    {
        if (type == "warrior")
            {
            return make_shared<Warrior>(species);
        }
        else if (type == "drone")
            {
            return make_shared<Drone>(species);
        }
        else if (type == "queen")
            {
            return make_shared<Queen>(species);
        }
        else if (type == "gatherer")
            {
            return make_shared<Gatherer>(species);
        }
        else if (type == "killer")
            {
            return make_shared<Killer>(species);
        }
        else if (type == "pansy")
            {
            return make_shared<Pansy>(species);
        }
        else if (type == "worker")
            {
            return make_shared<Worker>(species);
        }
        else if (type == "soldier")
            {
            return make_shared<Soldier>(species);
        }
        else if (type == "scout")
            {
            return make_shared<Scout>(species);
        }
        else if (type == "hunter")
            {
            return make_shared<Hunter>(species);
        }
        else if (type == "protector")
            {
            return make_shared<Protector>(species);
        }

        return nullptr;
    }
};

// ----- AntFarm Class (Template) -----
template<typename TypeofAnt>
class AntFarm : public AntFarmBase
{
private:
    int id;
    int x, y;
    string species;
    vector<shared_ptr<Ant>> ants;
    unordered_map<int, shared_ptr<Room>> rooms;
    int warriors, workers, antKills, colonyKills, ticksAlive;
    bool isAlive;
    int killedByColonyId;
public:
    AntFarm(int id, int x, int y, const string& species)
        : id(id), x(x), y(y), species(species), warriors(0), workers(0),
          antKills(0), colonyKills(0), ticksAlive(0), isAlive(true), killedByColonyId(-1) {}
    void addRoom(shared_ptr<Room> room)
    {
        rooms[rooms.size() + 1] = room;
        room->build();
    }
    void spawnAnt(const string& type)
    {
        auto newAnt = AntFactory::createAnt(type, species);
        ants.push_back(newAnt);
        if (type == "warrior") warriors++;
        else if (type == "drone") workers++;
        cout << type << " ant spawned for colony " << id << ".\n";
    }
    void tick() override
    {
        if (!isAlive) return;

        ticksAlive++;
        for (auto& ant : ants)
            {
            if (!ant->isrestingget())
            {
                ant->Actionpeformance();
            }
        else
            {
                cout << ant->getSpecies() << " is resting.\n";
            }
        }
    }
    void displaySummary() override
    {
        cout << "Colony ID: " << id << " Summary:\n";
        cout << "Species: " << species << "\n";
        cout << "Workers: " << workers << "\n";
        cout << "Warriors: " << warriors << "\n";
        cout << "Ant Kills: " << antKills << "\n";
        cout << "Colony Kills: " << colonyKills << "\n";
        cout << "Ticks Alive: " << ticksAlive << "\n";
        cout << "Status: " << (isAlive ? "Alive" : "Killed by " + to_string(killedByColonyId)) << "\n";
    }
    void giveResources(const string& Resources, int Amount) override {
        if (Resources == "food")
            {
            // Increase food
            cout << "Colony " << id << " received " << Amount << " food.\n";
        }
        else if (Resources == "warrior")
            {
            warriors += Amount;
            cout << "Colony " << id << " spawned " << Amount << " warriors.\n";
            for (int i = 0; i < Amount; ++i) {
                spawnAnt("warrior");
            }
        }
    }
    void killColony(int colonyId)
    {
        isAlive = false;
        killedByColonyId = colonyId;
    }

    bool getIsAlive() const
    {
        return isAlive;
    }

    shared_ptr<Ant> getAnt(int index)
    {
        return ants.at(index);
    }
};

void displayMenu() {
    cout << "\n\t--- variable Menu ---\n\n";
    cout << "1. spawn X Y T - Spawn colony position (X, Y) species(T)\n";
    cout << "2. give I R A - Give colony I (Resources R) and Amount(A)\n";
    cout << "3. tick  T  -  Run  (T)  ticks  of   the  simulation\n";
    cout << "4. summary  I  -  Show   summary  of   colony  (I)\n";
    cout << "5. quit - Exit the simulation\n\n";
}
void variableexecution(const string& variable, Meadow* meadow)
 {
    istringstream stream(variable);
    string Action;
    stream >> Action;
    if (Action == "spawn")
        {
        int x, y;
        string species;
        stream >> x >> y >> species;
        meadow->spawnColony<Warrior>(x, y, species);  // Add species-specific logic as needed
    }
    else if (Action == "give")
        {
        int id, Amount;
        string Resources;
        stream >> id >> Resources >> Amount;
        auto farm = meadow->getFarmofAnts(id);
        farm->giveResources(Resources, Amount);
    }
    else if (Action == "tick")
        {
        int ticks;
        stream >> ticks;
        for (auto& farm : meadow->getFarmofAnts())
        {
            for (int i = 0; i < ticks; ++i)
            {
                farm.second->tick();
            }
        }
    }
    else if (Action == "summary")
    {
        int id;
        stream >> id;
        auto farm = meadow->getFarmofAnts(id);
        farm->displaySummary();
    }
    else
    {
        cout<<"Invalid variable"<<endl;
    }
}

int main()
{

    cout<<"___________WellCome in the Colony of Ants______________\n";
    int RollNum = 31;
    cout << "\n\tYour Roll Number is : " << RollNum << endl;
    Meadow* meadow = Meadow::getInstance(RollNum);
    cout << "\tTotal Species: " << meadow->getcount_species() << endl;
    cout << "\tSpecies List: \n"<<endl;
    for (const auto& species : meadow->getnames_species())
        {
        cout << species << " ";
    }
    cout << endl;

    string variable;
    do
        {
        displayMenu();
        cout << "\tPlease Enter variable: \n";
        getline(cin, variable);  // Read the input correctly
        variableexecution(variable, meadow);
    } while (variable != "quit");

    return 0;
}
