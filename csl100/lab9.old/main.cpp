#include "renderer.h"
#include "game.h"
#include <iostream>
using namespace std;
int main(){
	
	cout<<"\nHELLO!\n";
	renderer r;
	game g(&r,"input.txt");
	g.play();
	cout<<"\nExiting\n";
	return 0;
}
