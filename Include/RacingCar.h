﻿/*
	Racing game project - Racing car class

	2019
	Nicolas Bouchard, Timothee Guy, Timothee Laurent
*/

#ifndef RACINGCAR_H
#define RACINGCAR_H

#include <Position.h>
#include <BoundingBox.h>

class RacingCar {

public:
	static const float MAX_SPD_FW;	// Maximum speed forward
	static const float MAX_SPD_BW;	// Maximum speed backward
	static const float ACCEL;		// Acceleration
	static const float ROT_ANGLE;	// Rotation rate

private:
	Position *pos;			// Position
	BoundingBox *hitbox;	// Hitbox

	bool handbrakeState;	// Handbrake state
	bool dirForward;		// Direction state

	float speed, length, width, height;

public:
	/* Constructors */
	RacingCar(float clength, float cwidth, float cheight, float cx, float cy, float cz);

	RacingCar(float clength, float cwidth, float cheight);

	RacingCar(RacingCar *rc);

	RacingCar(void);

	/* Destructor */
	~RacingCar(void);

	/* Getters */
	Position getPos(void);

	BoundingBox getBoundingBox(void);

	float getSpeed(void);

	bool getHandbrakeState(void);
	bool getDirForward(void);
	
	/*Draw */
	void draw(void);

	/* Input handling */
	void handleInputs(bool *keyStates, bool *specialKeyStates);

	/* Movement handling */
	void handleMovement(double deltaTime);

	/* Forward */
	void forward(float distance);

	/* Backward */
	void backward(float distance);

	/* Turn right */
	void turnRight(float degrees);

	/* Turn left */
	void turnLeft(float degrees);

	/* Use the handbrake */
	void handbrake();

	/* Reset car's properties */
	void reset();
};

#endif