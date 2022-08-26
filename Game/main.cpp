#include <iostream>

#include <Constellate.h>
#include <iostream>


class Game : public csl::Application {

public:
	Game() {

	}
	~Game(){

	}
};

//This is the entry point of the library
csl::Application* csl::CreateApplication()
{
	return new Game();
}