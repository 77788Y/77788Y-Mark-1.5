#include "main.h"
#include "subsystems/lift.hpp"
#include "subsystems/angler.hpp"
#include "subsystems/chassis.hpp"
#include "subsystems/intake.hpp"
#include "autons.hpp"

using namespace subsystems;

namespace autons {

  void blue_protected_four() {

    int start_time = pros::millis();

    // tare orientation
    chassis::tare_orientation(0 * units::DEGREES);

    // intake preload and first orange cube
    intake::move_voltage(12000);
    chassis::rotate_to(0 * units::DEGREES);
    chassis::move_to(15 * units::INCHES);
    pros::delay(200);

    // go to purple cube
    chassis::rotate_to(80 * units::DEGREES, 1800, 6000);
    intake::move_voltage(12000);
    chassis::move_by(6 * units::INCHES);

    // go to second orange cube
    chassis::move_by(-8 * units::INCHES);
    chassis::rotate_to(-70 * units::DEGREES, 5000);
    chassis::rotate_to(-90 * units::DEGREES, 500);
    chassis::move_by(16 * units::INCHES, 1500, 6000);
    intake::hold();
    chassis::rotate_to(-126 * units::DEGREES, chassis::Side::LEFT, 1200, 5000);
    // angler::m_motor.move_absolute(320, 50);
    chassis::move_by(4.75 * units::INCHES, 1100, 4000, 4000, 1 * units::INCHES, 0, 2 * units::INCHES);

    // deposit stack
    intake::move_voltage(-6000);
    pros::delay(300);
    intake::move_voltage(-1000);
    while (angler::pos > angler::POS_DEPOSIT + 15 * units::DEGREES) {
      angler::update_auto_deposit(1);
      pros::delay(10);
    }
    angler::hold();
    intake::move_voltage(0);

    // make sure load is fully in place
    if (pros::millis() - start_time < 13750) chassis::move_by(3 * units::INCHES, 300, 6000);

    // back out
    chassis::move_by(-15 * units::INCHES, 1000, 12000, 6500);
  }
}
