#pragma once

#include <array>
#include <vector>
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>

class Axis : public sf::Drawable {
	public:
		Axis(sf::Vertex begin = sf::Vertex({0, 0}), sf::Vertex end = sf::Vertex({0, 0}), double min = 0, double max = 0, double tick_sep = 10, std::string label = "");

		Axis& operator=(const Axis &rhs);

		void set_color(const sf::Color &color);

		double rtoa_factor() { return (max - min)/(std::sqrt(std::pow(end.position.y-begin.position.y,2) + std::pow(end.position.x - begin.position.x, 2))); }

		double ator_factor() { return (std::sqrt(std::pow(end.position.y - begin.position.y, 2) + std::pow(end.position.x - begin.position.x, 2))) / (max - min); }
	private:

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		sf::Text label;

		//max-min is length of line in axis units
		double min;
		double max;

		sf::Font font;

		//the length of each tick mark line
		const double tick_len = 10;

		//pos of line
		sf::Vertex begin;

		sf::Vertex end;

		//vector of tick marks
		std::vector< std::array<sf::Vertex, 2> > ticks;

		//seperation between tick marks in axis units
		double tick_interval;

		sf::Color color;

};