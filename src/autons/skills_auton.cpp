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

  // rotate to tower
  chassis::rotate_to_bang(86 * units::DEGREES);
  chassis::rotate_to_bang(90 * units::DEGREES);

  // set lift position
  lift::goto_sync(lift::POS_HIGH_TOWER);

  // move to tower
  chassis::move_by(11 * units::INCHES);

  // deposit cube
  intake::move_voltage(-7000);
  pros::delay(800);
  intake::move_voltage(0);


  // second tower---------------------------------------------------------------

  // start moving to second tower
  chassis::move_by(-28 * units::INCHES);

  // rotate to cube
  chassis::rotate_to_bang(4 * units::DEGREES);
  chassis::rotate_to_bang(0 * units::DEGREES);
  chassis::move_by(-4 * units::INCHES);
  chassis::move_voltage(-8000);
  pros::delay(1500);
  chassis::move_voltage(0);

  // reset lift
  lift::goto_sync(lift::POS_MIN);

  // intake cube
  macros::notify(macros::CODE_INTAKE_TOWER);
  chassis::move_by(12 * units::INCHES);
  chassis::move_by(-2 * units::INCHES);
  intake::move_voltage(0);

  // rotate to tower
  chassis::rotate_to_bang(-52 * units::DEGREES);
  chassis::rotate_to_bang(-60 * units::DEGREES);

  // set lift position
  lift::goto_sync(lift::POS_LOW_TOWER);

  // move to tower
  chassis::move_by(8.5 * units::INCHES);

  // deposit cube
  intake::move_voltage(-6000);
  pros::delay(1000);
  intake::move_voltage(0);


  // first stack----------------------------------------------------------------

  // reset lift
  chassis::move_by(-5.5 * units::INCHES);
  lift::goto_sync(lift::POS_MIN);

  // reset angler
  angler::m_motor.move_absolute(0, 200);

  // calibrate orientation
  chassis::move_by(-2 * units::INCHES);
  chassis::rotate_to_bang(0 * units::DEGREES);
  chassis::move_by(-7 * units::INCHES);
  chassis::move_voltage(-8000);
  pros::delay(1200);
  chassis::move_voltage(0);
  chassis::tare_orientation(0);

  // intake cubes for stack
  intake::move_voltage(12000);
  chassis::move_by(109 * units::INCHES, 11000, 5000, 4000, 8 * units::INCHES);
  intake::hold();

  // rotate to goal
  chassis::rotate_to_bang(-45 * units::DEGREES);

  // move to goal
  chassis::move_by(9.5 * units::INCHES);
  chassis::hold();

  // make sure load is fully in place
  chassis::move_voltage(0, 5800);
  pros::delay(250);
  chassis::move_voltage(0, 0);
  pros::delay(100);
  chassis::hold();

  // dump load
  intake::move_voltage(-1000);
  while (angler::pos > angler::POS_DEPOSIT + 9 * units::DEGREES) {
    angler::update_auto_deposit();
    pros::delay(10);
  }
  intake::move_voltage(0);

  // back out
  chassis::move_by_bang(1.5 * units::INCHES, 4000);
  pros::delay(100);
  chassis::move_by(-26.5 * units::INCHES, 3000, 9000, 1500, 3.5 * units::INCHES);


  // third tower----------------------------------------------------------------

  // rotate to cube
  chassis::rotate_to_bang(-170 * units::DEGREES);
  chassis::rotate_to_bang(-180 * units::DEGREES);

  // calibrate angle
  chassis::move_by(-9 * units::INCHES);
  chassis::move_voltage(-6000);
  pros::delay(1000);
  chassis::move_voltage(0);
  chassis::tare_orientation(-180);

  // reset angler
  angler::m_motor.move_absolute(0, 200);

  // move by
  macros::notify(macros::CODE_INTAKE_TOWER);
  chassis::move_by(30 * units::INCHES);
  chassis::move_by(-6 * units::INCHES);
  lift::goto_sync(lift::POS_LOW_TOWER);
  intake::move_voltage(-7000);
  pros::delay(800);
  intake::move_voltage(0);

}
