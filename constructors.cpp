#include <iostream>
#include <string>
#include <vector>
#include <memory>

class Person {
public:
  int age;
  std::string name;

  Person() : age(0), name("") {
    std::cout << name << " constructor with no parameters." << '\n';
  }

  Person(int age, std::string name) : age(age), name(std::move(name)) {
    std::cout << this->name << " constructor with parameters." << '\n';
  }

  Person(const Person& other) : Person{ other.age, other.name } {
    std::cout << name << " copy constructor." << '\n';
  }

  Person(Person&& other) noexcept : age(other.age), name(std::move(other.name)) {
    other.age = 0;
    other.name = "";
    std::cout << name << " move constructor." << '\n';
  }

  Person& operator=(const Person& other) {
    if (this != &other) {
      age = other.age;
      name = other.name;
      std::cout << name << " copy assignment operator." << '\n';
    }

    return *this;
	}

	Person& operator=(Person&& other) noexcept {
    if (this != &other) {
      age = other.age;
      name = std::move(other.name);
      other.age = 0;
      other.name = "";
      std::cout << name << " move assignment operator." << '\n';
    }

    return *this;
	}

  ~Person() {
    std::cout << name << " destructor." << '\n';
  }
};

class Manager {
public:
  int id;
	std::string name;
  std::unique_ptr<Person> personPtr;
  std::vector<std::unique_ptr<Person>> peopleVector;

public:
	Manager() : id(0), name(""), personPtr(nullptr), peopleVector(std::vector<std::unique_ptr<Person>>{}) {
		std::cout << name << " constructor with no parameters." << '\n';
	}

	Manager(int id, std::string name, std::unique_ptr<Person> personPtr, std::vector<std::unique_ptr<Person>> peopleVector)
  : id(id), name(std::move(name)), personPtr(std::move(personPtr)), peopleVector(std::move(peopleVector)) {
    std::cout << this->name << " constructor with parameters." << '\n';
	}

	Manager(const Manager& other) : id(other.id), name(other.name) {
    personPtr = other.personPtr ? std::make_unique<Person>(*other.personPtr) : nullptr;
    peopleVector.clear();

    for (const auto& ptr : other.peopleVector) {
      ptr ? peopleVector.emplace_back(std::make_unique<Person>(*ptr)) : peopleVector.emplace_back(nullptr);
    }

		std::cout << name << " copy constructor." << '\n';
	}

	Manager(Manager&& other) noexcept 
  : id(other.id), name(std::move(other.name)), personPtr(std::move(other.personPtr)), peopleVector(std::move(other.peopleVector)) {
		other.id = 0;
		other.name = "";
    other.personPtr = nullptr;
    other.peopleVector.clear();
		std::cout << name << " move constructor." << '\n';
	}

	Manager& operator=(const Manager& other) {
    if (this != &other) {
      id = other.id;
  		name = other.name;
      personPtr = other.personPtr ? std::make_unique<Person>(*other.personPtr) : nullptr;
      peopleVector.clear();

      for (const auto& ptr : other.peopleVector) {
        ptr ? peopleVector.emplace_back(std::make_unique<Person>(*ptr)) : peopleVector.emplace_back(nullptr);
      }

  		std::cout << name << " copy assignment operator." << '\n';
    }

		return *this;
	}

	Manager& operator=(Manager&& other) noexcept {
    if (this != &other) {
  		id = other.id;
  		name = std::move(other.name);
  		personPtr = std::move(other.personPtr);
      peopleVector = std::move(other.peopleVector);
  		other.id = 0;
  		other.name = "";
      other.personPtr = nullptr;
      other.peopleVector.clear();
  		std::cout << "Manager move assignment operator." << '\n';
    }

		return *this;
	}

  Manager(std::initializer_list<int> il) : Manager{} {
    std::cout << "Manager initializer list constructor." << '\n';
  }

  ~Manager() {
    std::cout << name << " destructor." << '\n';
  }
  
};
