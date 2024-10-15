#include <iostream> 
#include "FlsImporter.h"
#include <fl/Headers.h>

using namespace fl;

int main()
{
	Engine* engine = new Engine();

	

	/*
	* TODO - Define input, output and rules
	*/
	InputVariable* obstacle = new InputVariable;
	obstacle->setName("obstacle");
	obstacle->setRange(0.0000000, 1.0000000000);
	obstacle->addTerm(new Triangle("left", 0, 0.05,
		0.6));
	obstacle->addTerm(new Triangle("right", 0.4, 0.95,
		1.0));
	engine->addInputVariable(obstacle);

	InputVariable* speed = new InputVariable;
	speed->setName("speed");
	speed->setRange(0.0000000, 1.0000000000);
	speed->addTerm(new Triangle("moving_left", 1, 1,
		0.6));
	speed->addTerm(new Triangle("moving_right", 0.4, 1,
		1.0));
	speed->addTerm(new Triangle("none", 0.25, 0.75,
		.0));
	engine->addInputVariable(speed);

	OutputVariable* mSteer = new OutputVariable;
	engine->addOutputVariable(mSteer);
	mSteer->setName("mSteer");
	mSteer->setRange(0.000, 1.000);
	mSteer->addTerm(new Triangle("left", 0, 0.3, 0.6));
	mSteer->addTerm(new Triangle("right", 0.4, 0.7, 1.0));
	mSteer->addTerm(new Triangle("slightLeft", 0, 0.4, 0.4));
	mSteer->addTerm(new Triangle("slightRight", 0.5, 0.8, .9));
	mSteer->setDefuzzifier(new Centroid(100));
	mSteer->setAggregation(new Maximum);
	mSteer->setDefaultValue(fl::nan);

	RuleBlock* mamdani = new RuleBlock;
	mamdani->setName("mamdani");
	mamdani->setConjunction(new AlgebraicProduct);
	mamdani->setDisjunction(new Maximum);
	mamdani->setImplication(new AlgebraicProduct);
	mamdani->setActivation(new General);
	mamdani->addRule(Rule::parse("if obstacle is left or speed is moving_left and speed is none then mSteer is slightRight", engine));
	mamdani->addRule(Rule::parse("if obstacle is right or speed is moving_right and speed is none then mSteer is slightLeft", engine));
	mamdani->addRule(Rule::parse("if obstacle is left or speed is moving_left then mSteer is right", engine));
	mamdani->addRule(Rule::parse("if obstacle is right or speed is moving_right then mSteer is left", engine));
	engine->addRuleBlock(mamdani);




	// Check the status and print error if engine not setup
	std::string status;
	if (not engine->isReady(&status))
		std::cout << "Engine is not ready" << std::endl << status << std::endl;


	/*
	* TODO - Add a gameplay loop 
	*/
	while (1)
	{
		std::string input = "";
		std::cin >> input;
		std::stringstream ss(input);
		double number = 0.;
		ss >> number;
		obstacle->setValue(number);
		engine->process();
		std::cout << "obstacle.input = " << number <<
		" => steer.output = " << mSteer->getValue() <<
		std::endl;
		speed->setValue(mSteer->getValue());
	}





	//exit
	delete engine;
	return 0;
}
