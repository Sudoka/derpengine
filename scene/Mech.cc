#include "Mech.h"

#include "../resources/ResourceManager.h"
#include <algorithm>

/// Constructs the mech body and its members
Mech::Mech()
{
	// Body
	body = new MechBody();
	addMember(new GeometryNode(body));

	float upper_bone_radius = 0.1, lower_bone_radius = 0.1,
		  upper_bone_length = 1.2, lower_bone_length = 1.2,
		  leg_spread = 0.8f;

	// Rocket launcher
	launcher[0] = new MechLauncher;
	launcher[0]->setPosition(0.75f, 0.5f, 0.0f);
	addMember(launcher[0]);

	launcher[1] = new MechLauncher;
	launcher[1]->setPosition(-0.75f, 0.5f, 0.0f);
	addMember(launcher[1]);

	// Upper bones
	MechLeg *upper_bone = new MechLeg(upper_bone_length, upper_bone_radius);
	leg[0] = new GeometryNode(upper_bone);
	leg[0]->setPosition(-leg_spread, 0.0f, 0.0f);
	leg[0]->setRotation(45.0f, 0.0f, 0.0f);
	addMember(leg[0]);

	leg[1] = new GeometryNode(upper_bone);
	leg[1]->setPosition(leg_spread, 0.0f, 0.0f);
	leg[1]->setRotation(45.0f, 0.0f, 0.0f);
	addMember(leg[1]);

	// Lower bones
	MechLeg *lower_bone = new MechLeg(lower_bone_length, lower_bone_radius);
	leg[2] = new GeometryNode(lower_bone);
	leg[2]->setPosition(
			(upper_bone_radius+lower_bone_radius)/2.0f+0.1f,
			0.0f,
			upper_bone_length);
	leg[2]->setRotation(90.0f, 0.0f, 0.0f);
	leg[0]->addMember(leg[2]);

	leg[3] = new GeometryNode(lower_bone);
	leg[3]->setPosition(
			-(upper_bone_radius+lower_bone_radius)/2.0f-0.1f,
			0.0f,
			upper_bone_length);
	leg[3]->setRotation(90.0f, 0.0f, 0.0f);
	leg[1]->addMember(leg[3]);

	// Material for the whole thing
	m = new Material();
	m->ambient = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
	m->diffuse = glm::vec4(1.0f);
	m->specular = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
	m->shininess = 10.0f;
	m->texture =
		ResourceManager::getInstance()->getTexture("textures/metal.bmp");
	setMaterial(m);
}

Mech::~Mech()
{
	delete m;
}

void Mech::doRender(RenderingContext *rc) 
{
}

void Mech::bendLeg(int num, float degree)
{
	assert(num >= 0);
	assert(num < 4);

	leg[num]->setRotation(degree, 0.0f, 0.0f);
}

float Mech::getDistanceToGround()
{
	glm::vec4 leg_end_1 = leg[0]->getRelativeCoordinates(
			leg[2]->getRelativeCoordinates(glm::vec4(0.0f, 0.0f, 1.2f, 1.0f)));
	glm::vec4 leg_end_2 = leg[1]->getRelativeCoordinates(
			leg[3]->getRelativeCoordinates(glm::vec4(0.0f, 0.0f, 1.2f, 1.0f)));
	return -std::min(leg_end_1.y, leg_end_2.y);
}
