#include <iostream>
#include <thread>
#include <chrono>
#include "Eventer.hpp"

using namespace std;

int main() {
	// Create an Eventer that we can submit callbacks to.
	// Default timout is 1000ms but you can pass any you like.
	Eventer er(2000);

	// You may name your event aribitrarily. "ev" is just easy to type :)
	// A standard .on() event will be called when it's emitted
	er.on("ev", [](){
		cout << "EV!" << endl; 
	});
	er.emit("ev"); // Like this!

	// A timed event will be called in multiples of the Eventer timeout
	er.on("ev-timed", [](){
		cout << "EV TIMED!" << endl;
	}, 2); // This will be called every ~4000ms
	
	while (true) { // Just a sleep to watch the timed events :)
		this_thread::sleep_for(chrono::milliseconds(10));
	}
	return 0;
}