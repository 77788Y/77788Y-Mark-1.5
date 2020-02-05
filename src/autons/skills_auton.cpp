#include "main.h"
#include "macros.hpp"
#include "subsystems/lift.hpp"
#include "subsystems/angler.hpp"
#include "subsystems/chassis.hpp"
#include "subsystems/intake.hpp"
#include "autons.hpp"

using namespace subsystems;

void skills_auton() {

  int start_time = pros::millis();

  // tare orientation
  chassis::tare_orientation(0 * units::DEGREES);


  // first tower----------------------------------------------------------------

  // fix orientation
  chassis::rotate_to(0 * units::DEGREES);

  // intake cube
  macros::notify(macros::CODE_INTAKE_TOWER);
  chassis::move_to(13 * units::INCHES);
  intake::move_voltage(0);

  // set lift position
  lift::goto_sync(lift::POS_HIGH_TOWER);

  // move to tower
  chassis::rotate_to(80 * units::DEGREES);
  chassis::rotate_to(90 * units::DEGREES);
  chassis::move_by(7 * units::INCHES);

  // deposit cube
  intake::move_voltage(-6000);
  pros::delay(1000);
  intake::move_voltage(0);


  // second tower---------------------------------------------------------------

  // start moving to second tower
  chassis::move_by(-24 * units::INCHES);

  // rotate to cube
  chassis::rotate_to(8 * units::DEGREES);
  chassis::rotate_to(0 * units::DEGREES);
  chassis::move_by(-6 * units::INCHES);

  // reset lift
  lift::goto_sync(lift::POS_MIN);

  // intake cube
  macros::notify(macros::CODE_INTAKE_TOWER);
  chassis::move_by(12 * units::INCHES);
  chassis::move_by(-2 * units::INCHES);
  intake::move_voltage(0);

  // rotate to tower
  chassis::rotate_to(-35 * units::DEGREES);
  chassis::rotate_to(-45 * units::DEGREES);

  // set lift position
  lift::goto_sync(lift::POS_LOW_TOWER);

  // move to tower
  chassis::move_by(8 * units::INCHES);

  // deposit cube
  intake::move_voltage(-5000);
  pros::delay(500);
  intake::move_voltage(0);


  // first stack----------------------------------------------------------------

  // reset lift
  chassis::move_by(-4 * units::INCHES);
  lift::goto_sync(lift::POS_MIN);

  // reset angler
  angler::m_motor.move_absolute(0, 200);

  // calibrate orientation
  chassis::move_by(-12 * units::INCHES);
  chassis::rotate_to(0 * units::DEGREES);
  chassis::move_by(-10 * units::INCHES);
  chassis::move_voltage(-8000);
  pros::delay(1500);
  chassis::move_voltage(0);
  chassis::tare_orientation(0);

  // intake cubes for stack
  intake::move_voltage(12000);
  chassis::move_by(60 * units::INCHES);
  intake::move_voltage(0);

  // rotate to goal
  chassis::rotate_to(-45 * units::DEGREES);

  // move to goal
  chassis::move_by(12 * units::DEGREES);
  chassis::hold();

  // dump load
  intake::move_voltage(-1500);
  while (angler::pos > angler::POS_DEPOSIT + 9 * units::DEGREES) {
    angler::update_auto_deposit(true);
    pros::delay(10);
  }
  intake::move_voltage(0);

  // make sure load is fully in place
  if (pros::millis() - start_time < 13750) chassis::move_by(3.5 * units::INCHES, 300, 4000);

  // back out
  chassis::move_voltage(-12000);
  pros::delay(9999);


  // third tower----------------------------------------------------------------

}
