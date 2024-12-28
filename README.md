Overview
This simulation models an ecosystem of ants, where various species of ants can form colonies, perform actions, and interact with each other. The simulation includes features like colony management, resource management, and ant behavior simulations. Users can spawn colonies, give resources, run simulation ticks, and view summaries of colonies.

Features
Colony Management: You can create and manage multiple colonies of different species.
Ant Actions: Each ant has a behavior depending on its species.
Resource Management: You can give resources to a colony.
Simulation Ticks: The simulation can run for several ticks, and each tick executes the actions of ants in the colonies.
Colony Summaries: You can view detailed information about the status of a colony.
Classes
Meadow Class
Meadow is a singleton class that manages all the ant farms (colonies). It ensures that there is only one instance of the Meadow and provides functionality to spawn new colonies and retrieve information about them.

Key Methods:
getInstance(int studentRollNumber): Retrieves the singleton instance of the Meadow.
spawnColony(int x, int y, const string& species): Spawns a new ant farm at the specified coordinates with a given species.
getAntFarm(int id): Retrieves a specific ant farm by its ID.
getAntFarms(): Returns all the ant farms in the meadow.
getSpeciesCount(): Returns the total number of ant species in the simulation.
getSpeciesNames(): Returns a list of all available species names.
AntFarmBase Class
AntFarmBase is the base class for all ant farms, providing a common interface for all colony types.

Key Methods:
tick(): Advances the simulation by one tick.
displaySummary(): Displays a summary of the colony's status.
giveResource(const string& resource, int amount): Adds a resource (e.g., food or warriors) to the colony.
Ant Class
Ant is the base class for all types of ants, defining the core properties and behavior of an ant.

Key Methods:
performAction(): Executes the specific action of the ant (depends on the species).
battle(shared_ptr<Ant> otherAnt): Allows ants to battle another ant based on their strength.
rest(int food): Puts the ant to rest if food is available.
stopRest(): Wakes up the ant from resting.
Key Properties:
species: The species of the ant.
health: The health of the ant.
strength: The strength of the ant, used for battles.
foodCost: The amount of food the ant consumes when resting.
isResting: A boolean flag that indicates whether the ant is resting.
Ant Species
The following species of ants are defined, each with unique characteristics:

Warrior: Strong and aggressive.
Drone: Foraging worker.
Queen: Lays eggs and generates new ants.
Gatherer: Collects food.
Killer: Hunts prey.
Pansy: A lazy ant that rests.
Worker: General worker ant.
Soldier: Protects the colony.
Scout: Explores new areas.
Hunter: Hunts for resources and food.
Protector: Defends the colony from enemies.
Builder: Constructs colony infrastructure.
Researcher: Analyzes and conducts research.
Each species has a corresponding class (e.g., Warrior, Drone, etc.), inheriting from the Ant base class, and implementing its specific behavior in the performAction() method.

Room Class
Rooms are structures within each ant farm (colony) that serve various purposes. Rooms can be added to colonies, and they have different effects on the colony's functionality.

Key Classes:
Room: Abstract base class for rooms.
WorkerRoom: A room for workers.
WarriorRoom: A room for warriors.
AntFactory Class
The AntFactory class is responsible for creating ants based on their type and species. It simplifies the process of spawning new ants.

Key Method:
createAnt(const string& type, const string& species): Creates and returns a new ant of the specified type and species.
AntFarm Class (Template)
AntFarm is a templated class representing a colony of ants. The template parameter defines the type of ants the colony consists of (e.g., Warrior, Drone, etc.).

Key Methods:
addRoom(shared_ptr<Room> room): Adds a room to the colony.
spawnAnt(const string& type): Spawns a new ant of the specified type.
tick(): Advances the simulation by one tick, performing actions for all ants in the colony.
displaySummary(): Displays a summary of the colony's stats.
giveResource(const string& resource, int amount): Provides a resource to the colony.
Key Properties:
id: Unique ID for the colony.
x, y: Coordinates of the colony.
species: Species of the ants in the colony.
ants: A list of ants in the colony.
rooms: A map of rooms within the colony.
warriors: The number of warrior ants in the colony.
workers: The number of worker ants in the colony.
antKills: Number of ants killed by the colony.
colonyKills: Number of other colonies killed by this colony.
ticksAlive: The number of simulation ticks the colony has survived.
isAlive: Boolean flag indicating whether the colony is still alive.
Main Simulation Interface
The simulation provides an interactive command-line interface where users can:

Spawn a Colony: Create a new colony at specified coordinates with a given species.
Give Resources: Provide resources (e.g., food or warriors) to a colony.
Tick the Simulation: Advance the simulation by a specified number of ticks.
View Colony Summary: Display detailed information about a colony's status.
Quit: Exit the simulation.
Command Syntax:
spawn X Y T: Spawn a new colony at position (X, Y) with species type T.
give I R A: Give resource R to colony I in the amount of A.
tick T: Run T ticks of the simulation.
summary I: Show the summary of colony I.
quit: Exit the simulation.
