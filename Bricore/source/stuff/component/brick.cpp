#include "brick.h"
#include "../../definition/gameState.h"
#include "../../definition/utility.h"
#include "../../manager/textureManager.h"
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace item;

Brick::Brick(const sf::Vector2f & size, const float frameSize)
	: brick(new RectangleShape){
	setSize(size);
	brick->setOrigin(brick->getSize() / 2.f);
	setFrameSize(frameSize);
}

Brick::Brick(const Brick & copy) 
	: brick(new RectangleShape(*copy.brick)){
}

bool Brick::containsPoint(const sf::Vector2f & point) const {
	return brick->getGlobalBounds().contains(point);
}

std::shared_ptr<sf::Drawable> Brick::getDrawable() const {
	return std::const_pointer_cast<sf::Drawable>(std::static_pointer_cast<const sf::Drawable>(shared_from_this()));
}

void Brick::update(const float updateRatio) {
	brick->move(speed / updateRatio);
}

void Brick::loadTexture(const std::string & fileName) {
	brick->setTexture(TextureManager::getInstance().get(fileName), true);
}

void Brick::setPosition(const sf::Vector2f & position) {
	brick->setPosition(position);
}

void Brick::setFillColor(const Color &color) {
	brick->setFillColor(color);
}

void Brick::setFrameColor(const Color &color) {
	if (getFrameSize() <= 0.0f) throw std::invalid_argument("Brick frames do not exist.");
	brick->setOutlineColor(color);
}

void Brick::setSpeed(const sf::Vector2f & speed) {
	this->speed = speed;
}

void Brick::setSize(const Vector2f & size) {
	if (size.x <= 0 || size.y <= 0) throw std::invalid_argument("Side-length cannot be negative.");
	brick->setSize(size);
}

void Brick::setFrameSize(const float frameSize) {
	if (frameSize < 0.0f) throw std::invalid_argument("Frame size cannot be negative.");
	brick->setOutlineThickness(frameSize);
}

const Vector2f & Brick::getBrickSize() const {
	return brick->getSize();
}

float Brick::getFrameSize() const {
	return brick->getOutlineThickness();
}

sys::DPointf Brick::getDP() const {
	return sys::DPointf(brick->getGlobalBounds());
}

FloatRect Brick::getGlobalBounds() const {
	return brick->getGlobalBounds();
}

const sf::Color & Brick::getBrickColor() const {
	return brick->getFillColor();
}

const Color & Brick::getFrameColor() const {
	return brick->getOutlineColor();
}

const Vector2f & Brick::getPosition() const {
	return brick->getPosition();
}

Brick::~Brick() { }

#pragma warning(suppress: 26434)
Brick & Brick::operator=(Brick right) {
	brick.swap(right.brick);
	return *this;
}

void Brick::draw(RenderTarget &target, RenderStates states) const {
	target.draw(*brick, states);
}
