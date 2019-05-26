#pragma once

#include <string>
#include <glm\glm\glm.hpp>
#include <Tempest\GLObjects.h>

const int CHARACTER_WIDTH = 8;
const int MAX_CHARACTER_HEALTH = 100;

class Character
{
public:
	Character();
	~Character();

	// getters
	glm::vec2 getDirection() { return m_direction; }
	glm::vec2 getPosition() { return m_position; }
	std::string getName() { return m_name; }
	Tempest::glTexture getTexture() { return m_texture; }
	int getHealth() { return m_health; }
	int getCavesSurvived() { return m_cavesSurvived; }
	float getSpeed() { return m_speed; }
	bool isDead() { return m_dead; }
	bool isSelected() { return m_selected; }

	// setters
	void setDirection(glm::vec2 direction) { m_direction = direction; }
	void setPosition(glm::vec2 position) { m_position = position; }
	void setHealth(int health) { m_health = health; }
	void setCavesSurvived(int caves) { m_cavesSurvived = caves; }
	void setSpeed(float speed) { m_speed = speed; }
	void setName(std::string name) { m_name = name; }
	void setDeath(bool isDead) { m_dead = isDead; }
	void setSelected(bool selected) { m_selected = selected; }
	void setTexture(Tempest::glTexture texture) { m_texture = texture; }

	void applyDamage(int damage);
	void applyHealth(int health);
	glm::vec4 calculateDestRect();

protected:
	std::string m_name;
	int m_health;
	int m_cavesSurvived;
	float m_speed;
	bool m_dead = false;
	bool m_selected = false;
	glm::vec2 m_position;
	glm::vec2 m_direction;

	// TODO: animated textures
	Tempest::glTexture m_texture;

};

