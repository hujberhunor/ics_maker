#include <ostream>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using std::string;

// Global variables --> Go to a class and a header
std::ofstream file;
string FILEPATH = "../resources/calendar.ics";

class Event{
private:
    string summary;
    string startDate;
    string endDate;
    string description;
    string location;
public:
    // Konstruktor
    Event(const string& summary, const string& startDate, const string& endDate,
             const string& description, const string& location)
           : summary(summary), startDate(startDate), endDate(endDate),
             description(description), location(location) {}

    // Konstuktor ami vector-ból alkot
    Event(std::vector<string> userInputElements){
        if(!(userInputElements.size() == 5)){
            std::cout << "Nincs megadva elegendő paraméter" << std::endl;
            return;
        }
        summary = userInputElements.at(0);
        startDate = userInputElements.at(1);
        endDate = userInputElements.at(2);
        description = userInputElements.at(3);
        location = userInputElements.at(4);
    }

    friend std::ostream& operator<<(std::ostream& os, Event& event);
};

// toString cuccos, hogy ne kelljen egyesével beírnom a fileba.
std::ostream& operator<<(std::ostream& os, Event& event){
   os << "BEGIN:VEVENT\n";
   os << "SUMMARY:" << event.summary << "\n";
   os << "DTSTART:" << event.startDate << "\n";
   os << "DTEND:" << event.endDate << "\n";
   os << "DESCRIPTION:" << event.description << "\n";
   os << "LOCATION:" << event.location << "\n";
   os << "END:VEVENT\n";
   return os;
}

// --- EVENT CUCCOS ---

// ics file-t csinál a megadott event vektorokból
void create_ics(const std::string& filepath, std::vector<Event>& events) {
    std::ofstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Error: Could not create file " << filepath << std::endl;
        return ;
    }

    try {
        file << "BEGIN:VCALENDAR\n";
        file << "VERSION:2.0\n";
        file << "CALSCALE:GREGORIAN\n\n";

        for (Event& e : events) {
            file << e;
            std::cout << std::endl;
        }

        file << "END:VCALENDAR\n";
        return;
    }
    catch (const std::exception& e) {
        std::cerr << "Error writing to file: " << e.what() << std::endl;
        return;
    }
}

// --- USER INPUT TO CREATE EVENTS ---

// User inputból eventet csinál
Event userIn(){
    string userInput; // Amit beír a user
    std::vector<string> userInputElements; // Split után a userinput

    std::cout << "Type the event info (format: sum, star, end, desc, loc)" << std::endl;
    std::getline(std::cin, userInput);

    userInputElements.clear(); // Hogy ne legyen benne semmi amikor feltöltöm

    // Basically egy split()
    // , szerinte kell splitelni nem space szerint
    std::stringstream ss(userInput);
    string word;
    while (ss >> word) {
        userInputElements.push_back(word);
    }

    Event e(userInputElements);
    return e;
}


int main(){
    Event e = userIn();

    std::vector<Event> events;
    events.push_back(e);

    create_ics(FILEPATH, events);

   return 0;
}
