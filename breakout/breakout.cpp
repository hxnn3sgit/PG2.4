#include "breakout.h"

#include <iostream>
#include <cmath>
using namespace std;

static cairo_t *cr = nullptr;

collistion_type collision(const ball &ball, const block &block) {
	return NONE;
}


breakout::breakout(int w, int h) 
: windowed_app(w, h, "BREAKOUT"),
  cells_x(8),
  cells_y(24),
  block_border_y(13) {
	// To be implemented (A3)
	// To be implemented (A4)
}

void breakout::draw() {
	cout << "out of breakout::draw" << endl;
	::cr = cr;
	cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
	if (state == INIT) {

	// To be implemented (A2)
	}
	// To be implemented (A3)
	// To be implemented (A4)
	// To be implemented (A5)
	
}

void breakout::tick(int time_diff) {
	cout << "out of breakout::tick" << endl;
	// To be implemented (A2)
	// To be implemented (A3)
	// To be implemented (A4)
	// To be implemented (A5)
}	

// ball
void ball::position(float posx, float posy) {
	x = posx;
	y = posy;
}

void ball::direction(float dirx, float diry) {
	cout << "out of ball::direction" << endl;
	// To be implemented (A4)
}

void ball::draw() {
	cout << "out of ball:draw" << endl;
	// To be implemented (A4)
}

void ball::use_random_start_dir(float scale_x, float scale_y) {
	// To be implemented (A4)
}

void ball::step(float gamespeed) {
	// To be implemented (A4)
}

void ball::collision(const block &b, breakout *game, collistion_type type) {
}

// board
void board::draw() {
	// To be implemented (A3)
}
	
void board::move_left(float by) {
	// To be implemented (A3)
}
	
void board::move_right(float by) {
	// To be implemented (A3)
}
	
void board::bounce(ball &ball) {
}
	
void board::rest(ball &ball) {
	// To be implemented (A4)
}

// blocks
void block::draw() {
}
