// framework.h

#include <string>

class Game {
protected:
		std::string gameName;	
public:
	virtual void startGame() = 0;
	virtual void playTurn() = 0;
	virtual bool isGameOver() = 0;
	virtual void printGameState() = 0;
};

class Player {
private:
	std::string name;
	int score;
public:
	Player (const std::string name) : name(name), score(0) {};
	std::string getName() const { return name; }
	void addPoints(int points) { score += points; }
    int getScore() const { return score; }	
	void resetScore() { score = 0; }
	friend std::ostream &operator<<(std::ostream &os, const Player &p);
};

class gameManager {
private:
	Game game;
public:
		
};
