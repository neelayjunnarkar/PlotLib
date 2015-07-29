#include "Plot.h"

Plot::~Plot() {
	
}

void Plot::add_graph(Graph graph) {

	graph.stretch(xaxis.ator_factor(), yaxis.ator_factor()); //convert to real units from axis units
	graph.translate(origin.position.x, origin.position.y);
	graph.invert(origin.position.y);
	graph.translate(0, origin.position.y);

	graphs.push_back(graph);
}

void Plot::draw(sf::RenderTarget& target, sf::RenderStates states) const {

	//Draw Axes
	target.draw(xaxis, states);
	target.draw(yaxis, states);

	for (Graph graph : graphs)
		graph.draw(target, states, pos.x, pos.x+dim.x, pos.y, pos.y+dim.y);
}

void Plot::clear() {
	graphs.clear();
}

Plot::Builder::Builder(const std::string &title, sf::Vector2f &position, const sf::Vector2f &dimensions) {
	if (!font.loadFromFile("C:\\Windows\\Fonts\\calibri.ttf"))
		std::cerr << "failed to load font" << std::endl;

	plot.title = sf::Text(title, font);
	plot.pos = position;
	plot.dim = dimensions;
}

Plot::Builder& Plot::Builder::xaxis(double max, double min, double tick_sep, const std::string &label) {
	xmax = max;
	xmin = min;
	xticksep = tick_sep;
	xlabel = label;
	return *this;
}

Plot::Builder& Plot::Builder::yaxis(double max, double min, double tick_sep, const std::string &label) {
	ymax = max;
	ymin = min;
	yticksep = tick_sep;
	ylabel = label;
	return *this;
}

Plot Plot::Builder::build() {
	
	//build xaxis

	double c_atory = (plot.dim.y) / (ymax - ymin);

	sf::Vertex xbegin{{plot.pos.x, (float) (plot.pos.y + plot.dim.y - c_atory*(-ymin))}};
	sf::Vertex xend{{plot.pos.x + plot.dim.x, (float) (plot.pos.y + plot.dim.y - c_atory*(-ymin))}};

	plot.xaxis = Axis{xbegin, xend, xmin, xmax, xticksep, xlabel};
	plot.xaxis.set_color(colour);

	//build yaxis
	double c_atorx = (plot.dim.x) / (xmax - xmin); 

	sf::Vertex ybegin{{(float)(plot.pos.x + c_atorx*(-xmin)), (float)(plot.pos.y+plot.dim.y) }};
	sf::Vertex yend{{(float)(plot.pos.x + c_atorx*(-xmin)), (float)(plot.pos.y)}};

	plot.yaxis = Axis{ybegin, yend, ymin, ymax, yticksep, ylabel};
	plot.yaxis.set_color(colour);

	plot.origin = sf::Vertex({(float)(plot.pos.x + c_atorx*(-xmin)), (float) (plot.pos.y +plot.dim.y - c_atory*(-ymin))}, colour);

	return plot;
}
