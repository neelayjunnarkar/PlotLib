#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <vector>

#include "Axis.h"
#include "Graph.h"

class Plot : public sf::Drawable {
public:

	virtual ~Plot();

	class Builder;

	//adds graph to the Plot
	void add_graph(Graph graph);

	//removes all graphs
	void clear();

	sf::Vector2f get_pos() const { return pos; }
	sf::Vector2f get_dim() const { return dim; }
	sf::Vertex get_origin() const { return origin; }

private:

	//used by RenderWindow to draw the Plot
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::Text title;

	std::vector<Graph> graphs;

	sf::Vector2f pos;	
	sf::Vector2f dim;

	Axis xaxis;
	Axis yaxis;

	sf::Vertex origin;

	sf::Color color;

};

class Plot::Builder {
	public:
		Builder(const std::string &title, sf::Vector2f &position, const sf::Vector2f &dimensions);

		Builder& xaxis(double max, double min = 0, double tick_sep = 10, const std::string &label = "");
		Builder& yaxis(double max, double min = 0, double tick_sep = 10, const std::string &label = "");
		Builder& color(const sf::Color &val) { plot.color = val; this->colour = val; return *this;}

		Plot build();

	private:
		Plot plot;
		sf::Font font;

		float xmin,
			xmax,
			ymin,
			ymax,
			xticksep,
			yticksep;

		std::string xlabel, ylabel;

		sf::Color colour;
};

