#include "Player.h"
#include <iostream>

void Player::update(float dt) {

}

void Player::scrollWheel(double yoffset) {
	if (yoffset > 0)
		blockInHand++;
	else
		blockInHand--;
	
	if (blockInHand > 7)
		blockInHand = 1;
	else if (blockInHand < 1)
		blockInHand = 7;

	std::cout << blockInHand << std::endl;
};