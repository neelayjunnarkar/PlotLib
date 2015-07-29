#include "Graph.h"


Graph::Graph(const std::vector<double> &x, const std::vector<double> &y, const sf::Color &color):
color{color} 
{
	for (size_t i = 0; i < ((x.size() > y.size()) ? y.size() : x.size()); i++) {
		vertices.push_back(sf::Vertex({(float) x[i], (float) y[i]}, color));
	}
}

Graph::Graph(const std::map<double, double> &xy_map, const sf::Color &color):
color{color}
{
	for (auto pair : xy_map)
		vertices.push_back(sf::Vertex({(float) pair.first, (float)pair.second}, color));
}

Graph::Graph(const std::vector<double> &x, std::function<double(double)> fn, const sf::Color &color):
color{color}
{
	for (auto e : x)
		vertices.push_back(sf::Vertex({(float)e, (float)fn(e)}, color));
}

Graph::~Graph() {

}

void Graph::draw(sf::RenderTarget &target, sf::RenderStates states, float xmin, float xmax, float ymin, float ymax) const {
	
	auto in_bounds = [xmin, xmax, ymin, ymax] (sf::Vector2f pos) -> bool {
		if (pos.y < ymin || pos.y > ymax || pos.x < xmin || pos.x > xmax)
			return false;
		return true;
	};

	static auto get_slope = [] (sf::Vector2f pos1, sf::Vector2f pos2) -> float {
		return (pos2.y - pos1.y) / (pos2.x - pos1.x);
	};

	for (unsigned i = 1; i < vertices.size(); ++i) {
		if (!in_bounds(vertices[i - 1].position) || !in_bounds(vertices[i].position)) {
			float slope = get_slope(vertices[i].position, vertices[i-1].position);
			//should find intersection of line and border, so it can draw the line until the border (by creating a temporary vertex at the border)
		} else {
			sf::Vertex arr[2] { vertices[i - 1], vertices[i] };
			target.draw(arr, 2, sf::Lines, states);
		}
		
	}
	//target.draw(vertices.data(), vertices.size(), sf::LinesStrip);
}

void Graph::translate(float x, float y) {
	for (sf::Vertex &vertex : vertices) {
		vertex.position.x += x;
		vertex.position.y += y;
	}
}

void Graph::stretch(float xfactor, float yfactor) {
	for (sf::Vertex &vertex : vertices) {
		vertex.position.x *= xfactor;
		vertex.position.y *= yfactor;
	}
}

void Graph::invert(float axis) {
	for (sf::Vertex &vertex : vertices) {
		vertex.position.y = axis-vertex.position.y;
	}
}