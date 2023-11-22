typedef struct {
	int x;
	int y;
	char symbol[20];
	int initial_x;
	int initial_y;
} Character;

void printCharacter(Character character);
void moveCharacter(Character *character, int key);
void resetCharacterPosition(Character *character);
