#include <iostream>
#include <string>
#include <vector>
using std::cout, std::endl, std::vector;

struct vec3 {
	float x, y, z;
	vec3(float x, float y, float z) : x(x), y(y), z(z) {}
	vec3(float uniform) : x(uniform), y(uniform), z(uniform) {}
};
	
vec3 operator+(const vec3 &lhs, const vec3 &rhs) {
	return vec3(lhs.x+rhs.x, lhs.y+rhs.y, lhs.z+rhs.z);
}
vec3 operator-(const vec3 &lhs, const vec3 &rhs) { 
	return vec3(lhs.x-rhs.x, lhs.y-rhs.y, lhs.z-rhs.z);
}
vec3 operator*(const vec3 &lhs, float s) { 
	return vec3(lhs.x*s, lhs.y*s, lhs.z*s);
}
vec3 operator*(float s, const vec3 &rhs) { 
	return lhs * s;
}
float operator|(const vec3 &lhs, const vec3 &rhs) {
	return lhs.x*rhs.x + lhs.y*rhs.y + lhs.z*rhs.z;
}

// geht auch
// vec3 operator*(const vec3 &lhs, const vec3 &rhs) { 
// 	return vec3(lhs.x * rhs.x,
// 				lhs.y * rhs.y,
// 				lhs.z * rhs.z);
// }

struct triangle {
	vec3 a, b, c;
};

vec3 cross(vec3 a, vec3 b) {
	return vec3(0,0,0);
}

vector<triangle> read_mesh(const std::string &file) {
	// ...
	vector<triangle> v;
	return v;
}


int main() {
	vector<triangle> tris = read_mesh("/tmp/data");
	
	float scale = .1;

	vector<vec3> normals;
	for (int i = 0; i < tris.size(); ++i) {
		// erst mal skalieren 
		tris[i].a = scale * tris[i].a;
		tris[i].b = scale * tris[i].b;
		tris[i].c = scale * tris[i].c;

		triangle t = tris[i];
		vec3 norm = cross((t.b-t.a), (t.c-t.a));
		normals.push_back(norm);

		float zero = (norm|(t.b-t.a))
	}

}
