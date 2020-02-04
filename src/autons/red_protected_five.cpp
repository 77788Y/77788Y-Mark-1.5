#include "main.h"
#include "subsystems/lift.hpp"
#include "subsystems/angler.hpp"
#include "subsystems/chassis.hpp"
#include "subsystems/intake.hpp"
#include "autons.hpp"

using namespace subsystems;

void red_protected_five() {

  int start_time = pros::millis();

  // tare orientation
  chassis::tare_orientation(0 * units::DEGREES);

  // intake preload and first orange cube
  intake::move_voltage(12000);
  chassis::rotate_to(0 * units::DEGREES);
  chassis::move_to(15 * units::INCHES, 3000, 12000);
  chassis::rotate_to(0 * units::DEGREES);
  pros::delay(200);

  // go to purple cube
  chassis::rotate_to(-75 * units::DEGREES, 1800);
  chassis::rotate_to(-90 * units::DEGREES);
  intake::move_voltage(12000);
  chassis::move_by(6 * units::INCHES, 800, 9000);
  intake::move_voltage(0);

  // go to second orange cube
  chassis::move_by(-1 * units::INCHES);
  chassis::rotate_to(-113 * units::DEGREES);
  intake::move_voltage(12000);
  chassis::move_by(14 * units::INCHES, 1000, 9000);
  chassis::rotate_to(-122 * units::DEGREES);
  chassis::move_by(-40 * units::INCHES, 3000, 12000);
  intake::hold();
  // angler::m_motor.move_absolute(320, 50);
  chassis::rotate_to(-203 * units::DEGREES);

  intake::move_voltage(7000);
  angler::m_motor.move_absolute(320, 50);
  chassis::move_by(29 * units::INCHES, 1100, 10000, 7000, 5 * units::INCHES, 0, 12 * units::INCHES);

  // deposit stack
  intake::move_voltage(-4000);
  pros::delay(50);
  while (angler::pos > angler::POS_DEPOSIT + 15 * units::DEGREES) {
    angler::update_auto_deposit(3);
    pros::delay(10);
  }
  angler::hold();
  intake::move_voltage(0);

  // make sure load is fully in place
  if (pros::millis() - start_time < 13750) chassis::move_by(1 * units::INCHES, 300, 6000);

  // back out
  chassis::move_by(-15 * units::INCHES, 1000, 12000, 6500);

}
