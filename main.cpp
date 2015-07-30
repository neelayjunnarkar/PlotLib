#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <SFML/Graphics.hpp>
#include "Plot.h"

struct Range {
	double min, max, step;
	Range(double min, double max, double step=1) :
		min{min-step},
		max{max},
		step{step}
	{
	}
	double operator()() { return (min < max) ? min += step : 0; }
};

std::tuple<sf::Vector2f, std::vector< std::vector<sf::Vector2f>>> grid(sf::Vector2f pos, sf::Vector2f dim, int row, int col, float sep=0) {
	std::vector<std::vector<sf::Vector2f>> plot(row, std::vector<sf::Vector2f>(col, sf::Vector2f{0,0}));
	sf::Vector2f plot_dim{(dim.x - sep*(col - 1)) / col, (dim.y - sep*(row-1))/row};

	for (unsigned c = 0; c < col; ++c) {
		for (unsigned r = 0; r < row; ++r) {
			plot[r][c] = sf::Vector2f{pos.x+c*plot_dim.x+(c)*sep, pos.y+r*plot_dim.y+(r)*sep};
		}
	}
	return std::tie(plot_dim, plot);
}


int main() {
	
	sf::Vector2f screen_dim{720, 720};
	
	sf::ContextSettings settings;
	settings.antialiasingLevel = 20;

	sf::RenderWindow window(sf::VideoMode(screen_dim.x, screen_dim.y), "PlotLib", sf::Style::Default, settings);
	window.setFramerateLimit(15);


	std::vector< std::vector<sf::Vector2f>> plot_poss;
	sf::Vector2f plot_dim;

	std::tie(plot_dim, plot_poss) = grid(sf::Vector2f{4,4}, sf::Vector2f{screen_dim.x-8, screen_dim.y-8}, 2, 2, 32);

	Plot plot{Plot::Builder("title", plot_poss[0][0], plot_dim)
		.color(sf::Color{250, 250, 250})
		.xaxis(10, -10, 1, "x")
		.yaxis(10, -10, 1, "y")
		.build()
	};

	Plot plot2{Plot::Builder("2", plot_poss[0][1], plot_dim)
		.color(sf::Color{250, 250, 250})
		.xaxis(10, -10, 1, "x")
		.yaxis(10, -10, 1, "y")
		.build()
	};

	Plot plot3{Plot::Builder("3", plot_poss[1][0], plot_dim)
		.color(sf::Color{250, 250, 250})
		.xaxis(10, -10, 1, "x")
		.yaxis(10, -10, 1, "y")
		.build()
	};

	Plot plot4{Plot::Builder("4", plot_poss[1][1], plot_dim)
		.color(sf::Color{250, 250, 250})
		.xaxis(10, -10, 1, "x")
		.yaxis(10, -10, 1, "y")
		.build()
	};


	std::vector<double> x(10000);
	std::generate(x.begin(), x.end(), Range{-50, 50, .01});	

	Graph slope1{x, x, sf::Color{13, 105, 235}};
	Graph log{x, std::log10f, sf::Color{236, 80, 42}};
	Graph sin{x, std::sinf, sf::Color::Magenta};
		
	plot.add_graph(slope1);
	plot.add_graph(log);
	plot.add_graph(sin);

	plot2.add_graph(slope1);
	
	plot3.add_graph(log);

	plot4.add_graph(sin);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color{30, 41, 53});
		window.draw(plot);
		window.draw(plot2);
		window.draw(plot4);
		window.draw(plot3);
		window.display();
	}

}