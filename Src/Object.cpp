/*
	Racing game project - Object class

	2019
	Nicolas Bouchard, Timothee Guy, Timothee Laurent
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <vector>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <Object.h>

/*-- Classes written to be synctactically comprehensive --*/

/* MTV : Constructor */
MTV::MTV(void) {
	overlap = FLT_MAX;
}

/* MTV : Destructor */
MTV::~MTV(void) {}


/*------------------------------
	Object Class
--------------------------------*/

/* Constructors */
Object::Object(float length, float width, float height, float x, float y, float z) {
	pos = new Position(x, y, z);
	hitbox = new BoundingBox(length, width, height, &pos);
	this->length = length;
	this->width = width;
	this->height = height;
	isColliding = false;
}

Object::Object(float length, float width, float height)
	:Object(length, width, height, 0.0, 0.0, 0.0)
{}

Object::Object(Object *o)
{
	pos = new Position(o->getPos());
	hitbox = new BoundingBox(o->getBoundingBox());
	length = o->length;
	width = o->width;
	height = o->height;
	isColliding = o->isColliding;
}

Object::Object(void)
	:Object(5.0, 5.0, 5.0, 0.0, 0.0, 0.0)
{}

/* Destructor */
Object::~Object(void) {}

/* Getters */
BoundingBox Object::getBoundingBox(void) {
	return hitbox;
}

Position Object::getPos(void) {
	return pos;
}

float Object::getLength(void) {
	return length;
}

float Object::getWidth(void) {
	return width;
}

float Object::getHeight(void) {
	return height;
}

bool Object::getIsColliding(void) {
	return isColliding;
}

/* Setters */
void Object::resetIsColliding(void) {
	isColliding = false;
}

/* Draw */
void Object::draw(void) {
	hitbox.draw();
}

/* Collision handling */
void Object::collision(Object *o) {
	MTV *mtv = collisionTestSAT(o);

	if (mtv != NULL) {
		pos.x += -mtv->axis.x * mtv->overlap;
		pos.z += mtv->axis.z * mtv->overlap;

		hitbox.update(&pos);
	}
}

/* Collision test between this object and another object
 * using the Separating Axis Theorem (SAT)
 * Y VALUES AREN'T TESTED
 * Implemented thanks to : http://www.dyn4j.org/2010/01/sat/
 */
MTV *Object::collisionTestSAT(Object *o) {
	/* An axis is a normal of a side of the object 
	 * We don't use the Y parameter of our bounding boxes,
	 * so we'll check only 4 axes like in a 2D world
	 * An axis is a 2D normalized vector
	 */
	Axis axes[4];  // Axes for this object
	Axis oaxes[4]; // Axes for the other object

	/* A projection is composed of [0] = min and [1] = max.
	 * Thoses are the result of the projection of the points of a bounding box
	 * on one of the axis previously found
	 */
	Projection *projection = new Projection();
	Projection *oprojection = new Projection();

	/* MTV : the Minimum Translation Vector is used to reposition the object
	 * if there's a collision
	 */
	MTV *mtv = new MTV();

	/* Get the axes */
	getAxesSAT(axes, &hitbox);
	getAxesSAT(oaxes, &o->hitbox);

	/* For every axis found for the first object */
	for (int i = 0; i < 4; i++) {
		/* Do the projection for both objects */
		projectObjectSAT(axes[i], &hitbox, projection);
		projectObjectSAT(axes[i], &o->hitbox, oprojection);

		float over = getOverlap(projection, oprojection);

		/* Check projections overlapping */
		if (over < 0) {
			/* If there's no overlap, there's no collision, return nothing
			 * Change the color if there's no collision at all
			 */
			if (!isColliding) {
				hitbox.setColor(1.0, 0.0, 0.0);
			}

			if (!o->isColliding) {
				o->hitbox.setColor(1.0, 0.0, 0.0);
			}

			return NULL;
		}
		else if (over < mtv->overlap) {
			mtv->overlap = over;
			mtv->axis = axes[i];
		}
	}

	/* For every axis found for the second object */
	for (int i = 0; i < 4; i++) {
		/* Do the projection for both objects */
		projectObjectSAT(oaxes[i], &hitbox, projection);
		projectObjectSAT(oaxes[i], &o->hitbox, oprojection);

		/* Calculate overlap */
		float over = getOverlap(projection, oprojection);

		/* Check projections overlapping */
		if (over < 0) {
			/* If there's no overlap, there's no collision, return nothing
			 * Change the color if there's no collision at all
			 */
			if (!isColliding) {
				hitbox.setColor(1.0, 0.0, 0.0);
			}

			if (!o->isColliding) {
				o->hitbox.setColor(1.0, 0.0, 0.0);
			}
			
			return NULL;
		}
		else if (over < mtv->overlap) {
			mtv->overlap = over;
			mtv->axis = axes[i];
		}
	}

	/* If we haven't returned, it means that all the projections overlap
	 * so there is a collision between the objects.
	 * Change the color if it's the first collision
	 */
	if (!isColliding) {
		isColliding = true;
		hitbox.setColor(0.0, 1.0, 0.0);
	}

	if (!o->isColliding) {
		o->isColliding = true;
		o->hitbox.setColor(0.0, 1.0, 0.0);
	}

	/* Return the MTV */
	return mtv;
}

/* Get the overlap between two projections */
float Object::getOverlap(Projection *projection, Projection *oprojection) {
	if (projection->min >= oprojection->min && projection->min <= oprojection->max) {
		return abs(oprojection->max - projection->min);
	}
	else if (projection->max >= oprojection->min && projection->max <= oprojection->max) {
		return abs(oprojection->min - projection->max);
	}
	else if (oprojection->min >= projection->min && oprojection->min <= projection->max) {
		return abs(projection->max - oprojection->min);
	}
	else if (oprojection->max >= projection->min && oprojection->max <= projection->max) {
		return abs(projection->min - oprojection->max);
	}

	return -1;
}

/* Get the 4 axes of a bounding box for the SAT */
void Object::getAxesSAT(Axis axes[4], BoundingBox *hitbox) {
	for (int i = 0; i < 4; i++) {
		/* Get 2 points that makes one edge of the box */
		Position p1 = hitbox->points[i];
		Position p2 = hitbox->points[i + 1 == 4 ? 0 : i + 1];

		/* Calculate the vector representing one edge of the box */
		float vec[2] = { p1.x - p2.x, p1.z - p2.z };

		/* Normalize the vector */
		float magnitude = sqrt(vec[0] * vec[0] + vec[1] * vec[1]);
		vec[0] = vec[0] / magnitude;
		vec[1] = vec[1] / magnitude;

		/* Store the axis as the normal of the vector */
		axes[i].x = -vec[1];
		axes[i].z = vec[0];
	}
}

/* Projection for the SAT */
void Object::projectObjectSAT(Axis axis, BoundingBox *hitbox, Projection *projection) {
	/* Initialize values */
	projection->min = axis.x * hitbox->points[0].x + axis.z * hitbox->points[0].z;
	projection->max = projection->min;
	
	/* Get the min and the max by looping through all points */
	for (int j = 1; j < 4; j++) {
		float p = axis.x * hitbox->points[j].x + axis.z * hitbox->points[j].z;

		if (p < projection->min) {
			projection->min = p;
		}
		else if (p > projection->max) {
			projection->max = p;
		}
	}
}