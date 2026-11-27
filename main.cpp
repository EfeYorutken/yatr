/*

	 there is a chat with geminei, read it

	 essentially, containers are what listen to events and elements are what gets rendered
	 you want to put the elements in the game_engine into a container and handle the
	 event stuff that way

 */

#include "game_engine.cpp"

const int w = 50;
const int h = 50;

int main(){

	Engine<w, h, 10> engine;

	engine.start();


	return 0;
}
