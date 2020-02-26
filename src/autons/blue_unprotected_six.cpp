#include "main.h"
#include "macros.hpp"
#include "subsystems/lift.hpp"
#include "subsystems/angler.hpp"
#include "subsystems/chassis.hpp"
#include "subsystems/intake.hpp"
#include "autons.hpp"

using namespace subsystems;

namespace autons {

  void blue_unprotected_six() {
    pros::ADIAnalogIn cube_detect('H');
    int start_time = pros::millis();

    // tare orientation
    chassis::tare_orientation(0 * units::DEGREES);

    // start intake and move forward, grabbing cubes
    intake::move_voltage(12000);
    pros::delay(10);
    intake::move_voltage(12000);
    pros::delay(10);
    intake::move_voltage(12000);
    pros::delay(10);
    intake::move_voltage(12000);
    pros::delay(10);
    intake::move_voltage(12000);
    chassis::move_to(36 * units::INCHES, 7000, 4500, 3000, 3 * units::INCHES, 2500, 3 * units::INCHES);
    pros::delay(300);
    intake::hold();

    // turn to cube
    chassis::rotate_to(-18 * units::DEGREES, 1200, 6000);

    //go to intake cube
    intake::move_voltage(12000);
    macros::notify(macros::CODE_INTAKE_TOWER);
    chassis::move_by(11 * units::INCHES, 3000, 4000);
    pros::delay(100);

    // back out
    chassis::move_by(-26.5 * units::INCHES, 5000, 10000, 4000, 2 * units::INCHES, 2000, 12 * units::INCHES, 1200);
    macros::notify(macros::CODE_INTERRUPT);
    intake::hold();

    // rotate
    pros::delay(200);
    chassis::rotate_to(132 * units::DEGREES, 2000, 8500);

    // move to goal
    chassis::move_by(10 * units::INCHES, 800, 10000, 2700, 6 * units::INCHES, 1100, 9.2 * units::INCHES);
    pros::delay(10);

    // make sure cubes are in place
    while (cube_detect.get_value() < 1700) {
      intake::move_voltage(-1000);
    }
    intake::hold();
    // chassis::move_voltage(5800, 0);
    // pros::delay(150);
    // chassis::move_voltage(0, 0);
    pros::delay(100);
    chassis::hold();

    // dump load
    intake::move_voltage(-1000);
    while (angler::pos > angler::POS_DEPOSIT + 9 * units::DEGREES) {
      angler::update_auto_deposit();
      pros::delay(10);
    }
    angler::hold();
    intake::move_voltage(0);

    // make sure load is fully in place
    if (pros::millis() - start_time < 13750) chassis::move_by(3.5 * units::INCHES, 300, 4000);

    // back out
    chassis::move_by(-12 * units::INCHES, 3000, 9000, 1500, 3.5 * units::INCHES);
    chassis::hold();
  }
}
