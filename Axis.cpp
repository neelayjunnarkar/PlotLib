#include "Axis.h"

Axis::Axis(sf::Vertex begin, sf::Vertex end, double min, double max, double tick_sep, std::string label):
begin(begin),
end(end),
min(min),
max(max),
tick_interval(tick_sep),
label(sf::Text(label, font)) //probs doesnt work
{

	if (!font.loadFromFile("C:\\Windows\\Fonts\\calibri.ttf"))
		std::cerr << "font not loaded" << std::endl;
	//this->label = sf::Text(label, font);

	//add ticks
	if (end.position.x == begin.position.x && end.position.y != begin.position.y) { //if vertical
		for (float a = 0; a <= (max - min) / tick_sep; ++a) {
			std::array<sf::Vertex, 2> arr;
			float ad = a*tick_sep*((end.position.y - begin.position.y) / (max-min)); // a*d multiplied by a factor to convert from axis units to real
			arr[0] = sf::Vertex({(float) (begin.position.x + tick_len / 2), (float) (ad + begin.position.y)}, begin.color);
			arr[1] = sf::Vertex({(float) (begin.position.x - tick_len / 2), (float) (ad + begin.position.y)}, begin.color);
			
			ticks.push_back(arr);
		}
	} else if (end.position.y == begin.position.y && end.position.x != begin.position.x) { //if horizontal
		for (float a = 0; a <= (max - min) / tick_sep; ++a) {
			std::array<sf::Vertex, 2> arr;
			float ad = a*tick_sep*((end.position.x - begin.position.x) / (max - min)); // a*d multiplied by a factor to convert from axis units to real
			arr[0] = sf::Vertex({(float) (ad + begin.position.x), (float) (begin.position.y + tick_len/2)}, begin.color);
			arr[1] = sf::Vertex({(float) (ad + begin.position.x), (float) (begin.position.y - tick_len/2)}, begin.color);

			ticks.push_back(arr);
		}
	} else { //neither vertical nor horizontal; DOESNT WORK (currently)

		/*float slope = ((end.position.y - begin.position.y) / (end.position.x - begin.position.x));
		float k = (tick_sep) / (std::sqrtf(1 + std::pow(slope, 2)));
		float g = (tick_len) / (std::sqrtf(1 + (1/std::pow(slope, 2))));

		for (float a = 0; a <= (max - min) / tick_sep; ++a) {
			std::array<sf::Vertex, 2> arr;
			float ak = a*k;
			float akm = ak*slope;
			float gdiv2 = (g / 2);
			float gdiv2m = gdiv2/slope;
			arr[0] = sf::Vertex({(float) (ak*ator_factor() + begin.position.x - gdiv2*ator_factor()), (float) (akm*ator_factor() + begin.position.y - gdiv2m*ator_factor())}, begin.color);
			arr[1] = sf::Vertex({(float) (ak*ator_factor() + begin.position.x + gdiv2*ator_factor()), (float) (akm*ator_factor() + begin.position.y + gdiv2m*ator_factor())}, begin.color);

			ticks.push_back(arr);
		}*/
	}
}

void Axis::draw(sf::RenderTarget& target, sf::RenderStates states) const {

	//draw axis
	sf::Vertex arr[2] {begin, end};
	target.draw(arr, 2, sf::Lines, states);

	//draw ticks
	for (std::array<sf::Vertex, 2> tick : ticks) {
		target.draw(tick.data(), 2, sf::Lines, states);
	}

}

void Axis::set_color(const sf::Color &color) {
	this->color = color;

	begin.color = color;
	end.color = color;

	for (std::array<sf::Vertex, 2> &tick : ticks)
		for (sf::Vertex &vertex : tick)
			vertex.color = color;
	
}


Axis& Axis::operator=(const Axis &rhs) {

	this->label = rhs.label;
	this->begin = rhs.begin;
	this->end = rhs.end;
	this->max = rhs.max;
	this->min = rhs.min;
	this->ticks = rhs.ticks;
	this->tick_interval = rhs.tick_interval;
	this->font = rhs.font;

	return *this;
}
