#include "block.h"
#include "../../definition/gameState.h"
#include "../../definition/utility.h"
#include "../../manager/textureManager.h"
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace item;

Block::Block(const Vector2f & position, const Vector2f &size)
	: block(new VertexArray(Quads, 4))
	, position(position)
	, initPosition(position)
	, size(size)
	, texture(nullptr) {
	setOrigin(getSize() / 2.f);
	settleBlockVertice();
}

Block::Block(const Block & copy)
	: block(copy.block)
	, position(copy.position)
	, initPosition(copy.initPosition)
	, speed(copy.speed)
	, size(copy.size) 
	, texture(copy.texture) {
	setVerticeColor(copy.getVerticeColor(0), copy.getVerticeColor(1)
		, copy.getVerticeColor(2), copy.getVerticeColor(3));
	settleBlockVertice();
}

bool Block::containsPoint(const sf::Vector2f & point) const {
	return getGlobalBounds().contains(point);
}

std::shared_ptr<sf::Drawable> Block::getDrawable() const {
	return std::const_pointer_cast<sf::Drawable>(std::static_pointer_cast<const sf::Drawable>(shared_from_this()));
}

void Block::setVerticeColor(const Color & color) {
	for (size_t i = 0; i < block->getVertexCount(); ++i) {
		(*block)[i].color = color;
	}
}

void Block::setVerticeColor(const Color & c1, const Color & c2, const Color & c3, const Color & c4) {
	(*block)[0].color = c1;
	(*block)[1].color = c2;
	(*block)[2].color = c3;
	(*block)[3].color = c4;
}

void Block::setSize(const sf::Vector2f & size) {
	if (size.x < 0.0f || size.y < 0.0f) throw std::invalid_argument("SideLength cannot be negetive.");
	this->size = size;
	settleBlockVertice();
}

void Block::resetPosition() {
	position = initPosition;
	settleBlockVertice();
}

void Block::setSpeed(const float speedX, const float speedY) {
	speed.x = speedX;
	speed.y = speedY;
}

void Block::setSpeed(const Vector2f & speed) {
	this->speed = speed;
}

// all change direct by using abs() to prevent stuck inside the block
void Block::update(const float updateRatio) {
	const Vector2f posLT = (*block)[0].position;
	const Vector2f posRB = (*block)[2].position;
	if (posLT.x <= 0.0f) {
		speed.x = abs(speed.x);
	}
	else if (posRB.x >= LEVEL_WIDTH) {
		speed.x = -abs(speed.x);
	}
	if (posLT.y <= 0.0f) {
		speed.y = abs(speed.y);
	}
	else if (posRB.y >= LEVEL_HEIGHT) {
		speed.y = -abs(speed.y);
	}
	moveEntity(updateRatio);
}

void Block::loadTexture(const std::string & fileName) {
	texture.reset(TextureManager::getInstance().get(fileName));
	(*block)[1].texCoords = Vector2f(size.x, 0.0f);
	(*block)[2].texCoords = Vector2f(size);
	(*block)[3].texCoords = Vector2f(0.0f, size.y);
}

void Block::setOrigin(const sf::Vector2f & origin) {
	this->origin = origin;
}

void Block::setPosition(const sf::Vector2f & position) {
	this->position = position + origin;
	settleBlockVertice();
}

sys::DPointf Block::getDP() const {
	return sys::DPointf((*block)[0].position, (*block)[2].position);
}

const Color & Block::getVerticeColor(const size_t index) const {
	return (*block)[index].color;
}

const Vector2f & Block::getOrigin() const {
	return origin;
}

const Vector2f & Block::getSize() const {
	return size;
}

Vector2u Block::getTextureSize() const {
	return texture->getSize();
}

sf::FloatRect Block::getLocalBounds() const {
	return block->getBounds();
}

sf::FloatRect Block::getGlobalBounds() const {
	return sf::FloatRect((*block)[0].position, getSize());
}

Vector2f Block::getPosition() const {
	return position + origin;
}

const Vector2f & Block::getInitialPosition() const {
	return initPosition;
}

const Vector2f & Block::getSpeed() const {
	return speed;
}

#pragma warning(suppress: 26434)
Block & Block::operator=(Block right) {
	initPosition = right.initPosition;
	position = right.position;
	origin = right.origin;
	speed = right.speed;
	size = right.size;
	block.swap(right.block);
	texture.swap(right.texture);
	return *this;
}

Block::~Block() {
}

void Block::settleBlockVertice() {
	if (size.x <= 0 && size.y <= 0) throw std::domain_error("Invalid side-length for block.");
	for (size_t i = 0; i < block->getVertexCount(); ++i) {
		(*block)[i].position = position;
	}
	(*block)[1].position += Vector2f(size.x, 0.0f);
	(*block)[1].texCoords = Vector2f(size.x, 0.0f);
	(*block)[2].position += Vector2f(size);
	(*block)[2].texCoords = Vector2f(size);
	(*block)[3].position += Vector2f(0.0f, size.y);
	(*block)[3].texCoords = Vector2f(0.0f, size.y);
}

void Block::moveEntity(const float updateRatio) {
	for (size_t i = 0; i < block->getVertexCount(); ++i) {
		(*block)[i].position += (speed / static_cast<float>(SLICE)) * updateRatio;
	}
	position = (*block)[0].position + origin;// mark new position in [0]
}

void Block::draw(RenderTarget &target, RenderStates states) const {
	states.texture = texture.get();
	target.draw(*block, states);
}
