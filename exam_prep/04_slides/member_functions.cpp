#include <iostream>
#include <string>

class Vec2D {
	float X;
	float Y;
public:
	Vec2D() = default;
	explicit Vec2D(const float x, const float y) : X(x), Y(y) {}
	explicit Vec2D(const float v) : Vec2D(v, v) {} 
	Vec2D(const Vec2D &other) = default; //c ctor
	Vec2D(Vec2D &&other) = default; // m ctor


	Vec2D& operator=(const Vec2D &other) = default; // could also be implemented by me, but un-
	Vec2D& operator=(Vec2D &&other) = default;		// necessary because of default float types
	
	void operator+=(const Vec2D &other);
	

	friend Vec2D operator+(const Vec2D &lhs, const Vec2D &rhs);
  	friend std::ostream& operator<<(std::ostream& out, const Vec2D& my_vec);
};

void Vec2D::operator+=(const Vec2D &other) {
	X += other.X;
	Y += other.Y;
}

Vec2D operator+(const Vec2D &lhs, const Vec2D &rhs) {
	return Vec2D( (lhs.X + rhs.X ), (lhs.Y + rhs.Y) );
}

std::ostream& operator<<(std::ostream& out, const Vec2D& my_vec) {
	return out << my_vec.X << "/" << my_vec.Y;
}

int main() {
	Vec2D first_point(2.3, 3.1);
	Vec2D second_point(8.3, 4.9);

	Vec2D result = first_point + second_point;
	std::cout << result << std::endl;

	result += Vec2D(1, 1);
	std::cout << result << std::endl;
	Vec2D cast_test(2.3, 1.2);
	result = cast_test + 3.0f;
	std::cout << result << std::endl;

	return 0;
}
