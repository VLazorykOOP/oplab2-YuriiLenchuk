#include <iostream>
#include <thread>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <chrono>

using namespace std;

const int w = 1000;
const int h = 800;
const int carSpeed = 6;
const int truckSpeed = 3;

struct Automobile {
    int x1, y1;
    int x2, y2;
    bool isMoving;

    Automobile(int startX, int startY, int endX, int endY)
        : x1(startX), y1(startY), x2(endX), y2(endY), isMoving(true) {}
};

vector<Automobile> cars;
vector<Automobile> trucks;

static void moveAutomobile(Automobile& automobile, int speed) {
    int dx = automobile.x2 - automobile.x1;
    int dy = automobile.x2 - automobile.y1;
    float length = sqrt(dx * dx + dy * dy);

    if (length > speed) {
        automobile.x1 += int(speed * dx / length);
        automobile.y1 += int(speed * dy / length);
    }
    else {
        automobile.x1 = automobile.x2;
        automobile.y1 = automobile.x2;
        automobile.isMoving = false;
    }
}

static void carThread() {
    while (true) {
        for (auto& car : cars) {
            if (car.isMoving) {
                moveAutomobile(car, carSpeed);
            }
        }
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

static void truckThread() {
    while (true) {
        for (auto& truck : trucks) {
            if (truck.isMoving) {
                moveAutomobile(truck, truckSpeed);
            }
        }
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

static void printAutos() {
    while (true) {
        system("cls");
        cout << "Cars:" << endl;
        for (const auto& car : cars)
            cout << "Position(x1, y1): (" << car.x1 << ", " << car.y1 << "), Destination(x2, y2): ("
                << car.x2 << ", " << car.y2 << ")" << endl;
        cout << endl << "Trucks:" << endl;
        for (const auto& truck : trucks)
            cout << "Position(x1, y1): (" << truck.x1 << ", " << truck.y1 << "), Destination(x2, y2): ("
                << truck.x2 << ", " << truck.y2 << ")" << endl;
        this_thread::sleep_for(chrono::seconds(1));
    }
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    for (int i = 0; i < 5; ++i) {
        cars.emplace_back(
            rand() % (w / 2),
            rand() % (h / 2),
            rand() % (w / 2),
            rand() % (h / 2)
        );
        trucks.emplace_back(
            w / 2 + rand() % (w / 2),
            h / 2 + rand() % (h / 2),
            w / 2 + rand() % (w / 2),
            h / 2 + rand() % (h / 2)
        );
    }

    thread t1(carThread);
    thread t2(truckThread);
    thread t3(printAutos);

    t1.join();
    t2.join();
    t3.join();

    return 0;
}