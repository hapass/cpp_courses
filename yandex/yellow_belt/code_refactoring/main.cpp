#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Walker {
public:
    Walker(const string& name, const string& type): Name(name), Type(type) {}

    virtual void Walk(const string& destination) const {
        Announce();
        cout << " walks to: " << destination << endl;
    }

    virtual ~Walker() = default;

    const string Name;
    const string Type;
protected:
    void Announce() const {
        cout << Type << ": " << Name;
    }
};

class Student: public Walker {
public:
    Student(const string& name, const string& favouriteSong): Walker(name, "Student"), FavouriteSong(favouriteSong) {}

    void Learn() const {
        Announce();
        cout << " learns" << endl;
    }

    void Walk(const string& destination) const override {
        Walker::Walk(destination);
        SingSong();
    }

    void SingSong() const {
        Announce();
        cout << " sings a song: " << FavouriteSong << endl;
    }
private:
    const string FavouriteSong;
};

class Teacher: public Walker {
public:
    Teacher(const string& name, const string& subject): Walker(name, "Teacher"), Subject(subject) {}

    void Teach() const {
        Announce();
        cout << " teaches: " << Subject << endl;
    }
private:
    const string Subject;
};

class Policeman: public Walker {
public:
    Policeman(const string& name): Walker(name, "Policeman") {}

    void Check(const Walker& walker) const {
        Announce();
        cout << " checks " << walker.Type << ". " << walker.Type << "'s name is: " << walker.Name << endl;
    }
};

void VisitPlaces(const Walker& walker, const vector<string>& places) {
    for (const auto& place : places) {
        walker.Walk(place);
    }
}

int main() {
    Teacher teacher("Jim", "Math");
    Student student("Ann", "We will rock you");
    Policeman policeman("Bob");

    VisitPlaces(teacher, {"Moscow", "London"});
    policeman.Check(student);
    VisitPlaces(student, {"Moscow", "London"});
    return 0;
}