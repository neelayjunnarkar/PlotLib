#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include <functional>

class Graph {
	public:
		Graph() = delete;

		//Takes an array of x and an array of y
		Graph(const std::vector<double> &x, const std::vector<double> &y, const sf::Color &color = sf::Color::Blue);

		//Takes a map of x->y
		Graph(const std::map<double, double> &xy_map, const sf::Color &color = sf::Color::Blue);

		//Takes an array of x and a function
		Graph(const std::vector<double> &x, std::function<double(double)> fn, const sf::Color &color = sf::Color::Blue);

		~Graph();

		void set_color(const sf::Color &color) { this->color = color; }

		void translate(float x, float y);

		void stretch(float xfactor, float yfactor);

		//used to convert graph to the plane in which the top left is (0, 0)
		void invert(float axis);

		void draw(sf::RenderTarget &target, sf::RenderStates states, float xmin, float xmax, float ymin, float ymax) const;

	private:

		std::vector<sf::Vertex> vertices;

		sf::Color color;
};

