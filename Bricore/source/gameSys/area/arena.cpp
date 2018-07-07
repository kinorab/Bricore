#include "arena.h"
#include "../effect/entireEffect.h"
#include <SFML/Graphics.hpp>

using namespace game;

std::map<std::string, std::shared_ptr<sf::Texture>> Arena::lightPreviews;
std::map<item::Enerma::Kind, std::shared_ptr<sf::Texture>> Arena::enermaPreviews;

Arena::Arena()
	: System(false) {

}

void Arena::update(const sf::Event * const event) {
}

void Arena::loadEnermaPreviews(const std::map<item::Enerma::Kind, std::string> &fileName, const bool isSmooth) {
	std::for_each(fileName.begin(), fileName.end(), [&](const std::pair<item::Enerma::Kind, std::string> file) {
		enermaPreviews.emplace(file.first, std::shared_ptr<sf::Texture>(new sf::Texture));
		enermaPreviews.at(file.first)->loadFromFile(file.second);
		enermaPreviews.at(file.first)->setSmooth(isSmooth);
	});
}

void Arena::loadLightPreviews(const std::vector<std::string> &fileName, const bool isSmooth) {
	std::for_each(fileName.begin(), fileName.end(), [&](const std::string &file) {
		lightPreviews.emplace(file, std::shared_ptr<sf::Texture>(new sf::Texture));
		lightPreviews.at(file)->loadFromFile(file);
		lightPreviews.at(file)->setSmooth(isSmooth);
	});
}

void Arena::cleanUpLightPowerCache() {
	lightPreviews.clear();
}

Arena::~Arena() {
}

void Arena::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	states.transform *= getTransform();
	std::for_each(enermas.begin(), enermas.end(), [&](const std::pair<item::Enerma::Kind, Content> &core) {
		target.draw(*core.second.context, states);
		target.draw(*core.second.lightPower, states);
	});
}
