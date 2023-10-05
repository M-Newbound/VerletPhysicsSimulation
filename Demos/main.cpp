#include "BallpitDemo.h"
#include "DoublePendulumDemo.h"
#include "ClothSimDemo.h"

enum class demoSelection {
	BALL_PIT,
	DOUBLE_PENDULUM,
	CLOTH_SIM
};

demoSelection selection = demoSelection::BALL_PIT;

int main()
{
	if (selection == demoSelection::BALL_PIT) BallpitDemo::runDemo();
	if (selection == demoSelection::DOUBLE_PENDULUM) DoublePendulumDemo::runDemo();
	if (selection == demoSelection::CLOTH_SIM) ClothSimDemo::runDemo();
}