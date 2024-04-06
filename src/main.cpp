#include <iostream>
#include <vector>
#include <string>
#include <fstream>
// Main Code Starts......
// Define the Event structure..
struct Event {
    std::string name;
    std::string date;
    std::string time;
    std::string description;
};

// Define the Calendar class.....
class Calendar {
private:
    std::vector<Event> events;

public:
    //Function to add an event to the calendar..
    void addEvent(const Event& event) {
        events.push_back(event);
    }

    // Function to edit an event in the calendar
    void editEvent(int index, const Event& newEvent) {
        if (index >= 0 && index < events.size()) {
            events[index] = newEvent;
        } else {
            std::cout << "Invalid event index." << std::endl;
        }
    }

    // Function to delete an event from the calendar....
    void deleteEvent(int index) {
        if (index >= 0 && index < events.size()) {
            events.erase(events.begin() + index);
        } else {
            std::cout << "Invalid event index." << std::endl;
        }
    }

    //Function to display all events in the calendar
    void displayEvents() const {
        if (events.empty()) {
            std::cout << "No events found." << std::endl;
        } else {
            for (size_t i = 0; i < events.size(); ++i) {
                std::cout << "Event " << i + 1 << ":" << std::endl;
                std::cout << std::endl;

                std::cout << "Name: " << events[i].name << std::endl;
                std::cout << std::endl;

                std::cout << "Date: " << events[i].date << std::endl;
                std::cout << std::endl;

                std::cout << "Time: " << events[i].time << std::endl;
                std::cout << std::endl;

                std::cout << "Description: " << events[i].description << std::endl;
                std::cout << std::endl;

                std::cout << std::endl;
                std::cout << std::endl;

            }
        }
    }

    // Function for getting  the number of events in the calendar
    size_t size() const {
        return events.size();
    }

    //Function to save calendar data to a file..
    void saveToFile(const std::string& filename) const {
        std::ofstream file(filename);
        if (file.is_open()) {
            for (const auto& event : events) {
                file << event.name << ',' << event.date << ',' << event.time << ',' << event.description << std::endl;
            }
            file.close();
            std::cout << "Calendar data saved to " << filename << std::endl;
        } else {
            std::cerr << "Unable to open file: " << filename << std::endl;
        }
    }

    // Function to load calendar data from a file
    void loadFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (file.is_open()) {
            events.clear(); // Clear existing events
            std::string line;
            while (std::getline(file, line)) {
                Event event;
                size_t pos = line.find(',');
                event.name = line.substr(0, pos);
                line.erase(0, pos + 1);
                pos = line.find(',');
                event.date = line.substr(0, pos);
                line.erase(0, pos + 1);
                pos = line.find(',');
                event.time = line.substr(0, pos);
                line.erase(0, pos + 1);
                event.description = line;
                events.push_back(event);
            }
            file.close();
            std::cout << "Calendar data loaded from " << filename << std::endl;
        } else {
            std::cerr << "Unable to open file: " << filename << std::endl;
        }
    }
};

int main() {
    Calendar calendar;

    // Load calendar data from a file (if available)
    calendar.loadFromFile("calendar_data.txt");

    // Display menu
    std::cout << "Calendar/Planner Application" << std::endl;
    std::cout << "1. Add Event" << std::endl;
    std::cout << "2. Edit Event" << std::endl;
    std::cout << "3. Delete Event" << std::endl;
    std::cout << "4. Display Events" << std::endl;
    std::cout << "5. Save Calendar" << std::endl;
    std::cout << "6. Exit" << std::endl;

    int choice;
    do {
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cout << std::endl;
        std::cout << std::endl;


        switch (choice) {
            case 1: {
                Event newEvent;
                std::cout << "Enter event name: ";
                std::cout << std::endl;

                std::cin.ignore(); // helps clear input buffer
                std::getline(std::cin, newEvent.name);
                std::cout << std::endl;

                std::cout << "Enter event date (e.g., YYYY-MM-DD): ";
                std::getline(std::cin, newEvent.date);
                std::cout << std::endl;

                std::cout << "Enter event time (e.g., HH:MM): ";
                std::getline(std::cin, newEvent.time);
                std::cout << std::endl;

                std::cout << "Enter event description: ";
                std::getline(std::cin, newEvent.description);
                calendar.addEvent(newEvent);
                break;
            }
            case 2: {
                int index;
                std::cout << "Enter index of event to edit: ";
                std::cin >> index;
                if (index >= 1 && index <= calendar.size()) {
                    Event editedEvent;
                    std::cout << "Enter new name for the event: ";
                    std::cin.ignore(); 
                    std::getline(std::cin, editedEvent.name);
                    std::cout << "Enter new date for the event: ";
                    std::getline(std::cin, editedEvent.date);
                    std::cout << "Enter new time for the event: ";
                    std::getline(std::cin, editedEvent.time);
                    std::cout << "Enter new description for the event: ";
                    std::getline(std::cin, editedEvent.description);
                    calendar.editEvent(index - 1, editedEvent);
                } else {
                    std::cout << "Invalid event index." << std::endl;
                }
                break;
            }
            case 3: {
                int index;
                std::cout << "Enter index of event to delete: ";
                std::cin >> index;
                if (index >= 1 && index <= calendar.size()) {
                    calendar.deleteEvent(index - 1);
                } else {
                    std::cout << "Invalid event index." << std::endl;
                }
                break;
            }
            case 4:
                calendar.displayEvents();
                break;
            case 5:
                calendar.saveToFile("calendar_data.txt");
                break;
            case 6:
                std::cout << "Exiting..." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    } while (choice != 6);

    return 0;
}
