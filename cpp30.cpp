#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <memory>
#include <sstream>

class Resident {
private:
    std::string name;
    int age;
    char gender;

public:
    Resident(const std::string& name, int age, char gender)
        : name(name), age(age), gender(gender) {}

    const std::string& getName() const { return name; }
    void setName(const std::string& name) { this->name = name; }

    int getAge() const { return age; }
    void setAge(int age) { this->age = age; }

    char getGender() const { return gender; }
    void setGender(char gender) { this->gender = gender; }

    friend std::ostream& operator<<(std::ostream& os, const Resident& resident) {
        os << "Name: " << resident.name << ", Age: " << resident.age
            << ", Gender: " << resident.gender;
        return os;
    }
};

class Premises {
protected:
    int roomCount;
    double area;
    std::string address;
    std::vector<Resident> residents;

public:
    Premises(int roomCount, double area, const std::string& address)
        : roomCount(roomCount), area(area), address(address) {}

    virtual ~Premises() = default;

    int getRoomCount() const { return roomCount; }
    void setRoomCount(int roomCount) { this->roomCount = roomCount; }

    double getArea() const { return area; }
    void setArea(double area) { this->area = area; }

    const std::string& getAddress() const { return address; }
    void setAddress(const std::string& address) { this->address = address; }

    const std::vector<Resident>& getResidents() const { return residents; }
    void addResident(const Resident& resident) { residents.push_back(resident); }
    void removeResident(const std::string& name) {
        residents.erase(
            std::remove_if(residents.begin(), residents.end(), [&name](const Resident& r) { return r.getName() == name; }),
            residents.end());
    }

    virtual void displayInfo(std::ostream& os) const = 0;

    friend std::ostream& operator<<(std::ostream& os, const Premises& premises) {
        premises.displayInfo(os);
        return os;
    }
};

class Apartment : public Premises {
private:
    int entranceNumber;
    int floor;
    int apartmentNumber;

public:
    Apartment(int roomCount, double area, const std::string& address, int entranceNumber, int floor, int apartmentNumber)
        : Premises(roomCount, area, address), entranceNumber(entranceNumber), floor(floor), apartmentNumber(apartmentNumber) {}

    int getEntranceNumber() const { return entranceNumber; }
    void setEntranceNumber(int entranceNumber) { this->entranceNumber = entranceNumber; }

    int getFloor() const { return floor; }
    void setFloor(int floor) { this->floor = floor; }

    int getApartmentNumber() const { return apartmentNumber; }
    void setApartmentNumber(int apartmentNumber) { this->apartmentNumber = apartmentNumber; }

    void displayInfo(std::ostream& os) const override {
        os << "Apartment [Address: " << address << ", Area: " << area
            << ", Rooms: " << roomCount << ", Entrance: " << entranceNumber
            << ", Floor: " << floor << ", Apartment: " << apartmentNumber
            << "]\nResidents:\n";
        for (const auto& resident : residents) {
            os << resident << "\n";
        }
    }
};

class PrivateHouse : public Premises {
private:
    double yardArea;

public:
    PrivateHouse(int roomCount, double area, const std::string& address, double yardArea)
        : Premises(roomCount, area, address), yardArea(yardArea) {}

    double getYardArea() const { return yardArea; }
    void setYardArea(double yardArea) { this->yardArea = yardArea; }

    void displayInfo(std::ostream& os) const override {
        os << "Private House [Address: " << address << ", Area: " << area
            << ", Rooms: " << roomCount << ", Yard Area: " << yardArea
            << "]\nResidents:\n";
        for (const auto& resident : residents) {
            os << resident << "\n";
        }
    }
};

class Cottage : public Premises {
private:
    int bathroomCount;
    int sleepingPlaces;

public:
    Cottage(int roomCount, double area, const std::string& address, int bathroomCount, int sleepingPlaces)
        : Premises(roomCount, area, address), bathroomCount(bathroomCount), sleepingPlaces(sleepingPlaces) {}

    int getBathroomCount() const { return bathroomCount; }
    void setBathroomCount(int bathroomCount) { this->bathroomCount = bathroomCount; }

    int getSleepingPlaces() const { return sleepingPlaces; }
    void setSleepingPlaces(int sleepingPlaces) { this->sleepingPlaces = sleepingPlaces; }

    void displayInfo(std::ostream& os) const override {
        os << "Cottage [Address: " << address << ", Area: " << area
            << ", Rooms: " << roomCount << ", Bathrooms: " << bathroomCount
            << ", Sleeping Places: " << sleepingPlaces << "]\nResidents:\n";
        for (const auto& resident : residents) {
            os << resident << "\n";
        }
    }
};

class Hotel : public Premises {
private:
    int roomCount;
    double maxRoomPrice;
    double minRoomPrice;

public:
    Hotel(int roomCount, double area, const std::string& address, int roomCount_, double maxRoomPrice, double minRoomPrice)
        : Premises(roomCount, area, address), roomCount(roomCount_), maxRoomPrice(maxRoomPrice), minRoomPrice(minRoomPrice) {}

    double getMaxRoomPrice() const { return maxRoomPrice; }
    void setMaxRoomPrice(double maxRoomPrice) { this->maxRoomPrice = maxRoomPrice; }

    double getMinRoomPrice() const { return minRoomPrice; }
    void setMinRoomPrice(double minRoomPrice) { this->minRoomPrice = minRoomPrice; }

    void displayInfo(std::ostream& os) const override {
        os << "Hotel [Address: " << address << ", Area: " << area
            << ", Rooms: " << roomCount << ", Max Price: " << maxRoomPrice
            << ", Min Price: " << minRoomPrice << "]\nResidents:\n";
        for (const auto& resident : residents) {
            os << resident << "\n";
        }
    }
};

class HousingManager {
private:
    std::vector<std::shared_ptr<Premises>> premises;

public:
    void addPremises(const std::shared_ptr<Premises>& premises_) {
        premises.push_back(premises_);
    }

    void removePremises(const std::string& address) {
        premises.erase(
            std::remove_if(premises.begin(), premises.end(), [&address](const std::shared_ptr<Premises>& p) { return p->getAddress() == address; }),
            premises.end());
    }

    void displayAll(std::ostream& os) const {
        for (const auto& p : premises) {
            os << *p << "\n";
        }
    }

    void displayByType(const std::string& type, std::ostream& os) const {
        for (const auto& p : premises) {
            if (typeid(*p).name() == type)
                os << *p << "\n";
        }
    }
};

int main() {
    // Створюємо менеджер житла
    HousingManager manager;

    // Створюємо та додаємо приміщення
    auto apartment = std::make_shared<Apartment>(3, 80.5, "123 Main St", 1, 2, 101);
    apartment->addResident(Resident("John Doe", 30, 'M'));
    apartment->addResident(Resident("Jane Smith", 28, 'F'));

    auto house = std::make_shared<PrivateHouse>(5, 120.0, "456 Elm St", 50.0);
    house->addResident(Resident("Alice Brown", 45, 'F'));

    manager.addPremises(apartment);
    manager.addPremises(house);

    // Виводимо інформацію про всі приміщення
    std::cout << "All Premises:\n";
    manager.displayAll(std::cout);

    // Видаляємо приміщення за адресою
    manager.removePremises("123 Main St");

    // Виводимо залишені приміщення
    std::cout << "\nAfter Removing Premises:\n";
    manager.displayAll(std::cout);

    return 0;
}

