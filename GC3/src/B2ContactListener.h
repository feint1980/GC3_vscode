// #pragma once
// #include <Box2D/Box2D.h>
// #include <iostream>
// class B2ContactListener : public b2ContactListener
// {
// public:
// 	B2ContactListener();
// 	~B2ContactListener();

// 	void BeginContact(b2Contact* contact) override {

// 		std::cout << "BeginContact \n";
// 		//check if fixture A was a ball
// 		void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
// 		if (bodyUserData)
// 		{
// 			std::cout << "contact \n";
// 			//static_cast<Ball*>(bodyUserData)->startContact();
// 		}
			

// 		//check if fixture B was a ball
// 		bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
// 		if (bodyUserData)
// 		{
// 			std::cout << "contact B \n";
// 			//static_cast<Ball*>(bodyUserData)->startContact();
// 		}
			

// 	}

// 	void EndContact(b2Contact* contact) override {


// 		std::cout << "EndContact \n";
// 		//check if fixture A was a ball
// 		void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
// 		if (bodyUserData)
// 		{
// 			std::cout << "end contact \n";
// 			//static_cast<Ball*>(bodyUserData)->endContact();
// 		}
			

// 		//check if fixture B was a ball
// 		bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
// 		if (bodyUserData)
// 		{
// 			std::cout << "end contact B \n";
// 			//static_cast<Ball*>(bodyUserData)->endContact();
// 		}
			

// 	}

// };

