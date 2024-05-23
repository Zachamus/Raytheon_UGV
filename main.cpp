#include <iostream>
#include <mavsdk/plugins/telemetry/telemetry.h>
#include <mavsdk/mavsdk.h>
#include <mavsdk/plugins/offboard/offboard.h>
#include <mavsdk/plugins/action/action.h>
#include <thread>
#include <iostream>
#include <ctime>
#include <chrono>
#include <future>
using namespace mavsdk;
using std::chrono::seconds;
using std::this_thread::sleep_for;
using namespace std::chrono_literals;


int main() {
    Mavsdk mavsdk{Mavsdk::Configuration{Mavsdk::ComponentType::CompanionComputer}};
    mavsdk::ConnectionResult conn_result = mavsdk.add_any_connection("serial:///dev/ttyAMA0:57600");

    if (conn_result != ConnectionResult::Success) {
        std::cerr << "Connection failed: " << conn_result << '\n';
        return 1;
    }

    auto system = mavsdk.first_autopilot(3.0);
    auto offboard = mavsdk::Offboard{system.value()};
    auto action = mavsdk::Action{system.value()};
    auto telemetry = mavsdk::Telemetry{system.value()};


    while (telemetry.health_all_ok() == false) {
        std::cout << "Telemetry not healthy" << std::endl;
        std::this_thread::sleep_for(0.5s);
    }
    std::cout << "System is ready";

    Action::Result arm_result = action.arm();

    if (arm_result != Action::Result::Success) {
        std::cerr << "Arm failed: " << arm_result << std::endl;
        return 1;
    }
    Action::Result act_res = action.set_actuator(0, 0.5);

    if (act_res != Action::Result::Success){
        std::cerr << "KYS LOL YOU SUCK" << act_res << std::endl;
        return 1;
    }
    sleep_for(5s);


    return 0;
}
