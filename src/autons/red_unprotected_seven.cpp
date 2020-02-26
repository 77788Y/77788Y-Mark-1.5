#include "main.h"
#include "subsystems/lift.hpp"
#include "subsystems/angler.hpp"
#include "subsystems/chassis.hpp"
#include "subsystems/intake.hpp"
#include "autons.hpp"

using namespace subsystems;

namespace autons {

  void red_unprotected_seven() {

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
    chassis::move_to(34 * units::INCHES, 8000, 4500, 3000, 3 * units::INCHES, 2500, 3 * units::INCHES);

    // turn to cube
    chassis::rotate_to(20 * units::DEGREES, 900, 6000);

    // intake cube
    chassis::move_by(11.5 * units::INCHES);
    pros::delay(300);
    intake::hold();

    // back out
    // chassis::move_by(-12 * units::INCHES);

    // turn to cube
    chassis::rotate_to(-20 * units::DEGREES, 800, 4000);

    //go to intake cube
    intake::move_voltage(12000);
    chassis::move_by(10 * units::INCHES, 3000, 9000);
    pros::delay(100);

    // back out
    chassis::move_by(-21 * units::INCHES, 5000, 10000, 4000, 2 * units::INCHES, 2000, 12 * units::INCHES, 1200);
    intake::hold();

    // rotate
    pros::delay(100);
    chassis::rotate_to(-135 * units::DEGREES, 2000, 8500);
    intake::move_voltage(-4200);
    pros::delay(310);
    intake::hold();

    // move to goal
    chassis::move_by(23 * units::INCHES, 1700, 10000, 4000, 6 * units::INCHES, 900, 9.2 * units::INCHES);
    pros::delay(10);
    // chassis::move_voltage(0, 5800);
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
