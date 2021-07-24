#include <iostream>
#include <string>
#include <tuple>
#include <map>

struct Point {
	double x;
	double y;
};

class Person {
	int age;
	double weight;
	std::string name;
};

std::tuple<int, std::string, Person> returnTuple() {
	return { 3, "String", Person() };
}

int main(int argc, char* argv[]) {

	/* Binding return value to already existing variables. */

	int integer;
	std::string str;
	Person person;

	std::tie(integer, str, person) = returnTuple();

	/* Binding return value. */

	const auto [number, string, personObject] = returnTuple();
	auto [a, b] = std::pair<std::string, int>("String", 10);
	auto [c, d, e, f] = std::tuple<std::string, int, double, Person>("String", 10, 20.3, Person());
		
	/* Binding struct. */

	Point p;
	auto& [x1, y1] = p;
	
	auto [x2, y2] = Point();

	/* Looping through map. */

	std::map<int, double> map = {{ 1, 4.0 }, { 3, 2.0 }};

	for (const auto& [key, value] : map) {
		std::cout << key << ' ' << value << '\n';
	}

	/* Binding an array. */

	int arr[2] = {1, 2};

	const auto& [first, second] = arr;

}