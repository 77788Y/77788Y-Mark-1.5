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
  chassis::rotate_to_bang(86 * units::DEGREES, 5000);
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
  chassis::rotate_to_bang(10 * units::DEGREES, 5000);
  chassis::rotate_to_bang(0 * units::DEGREES);

  // calibrate orientation
  chassis::move_by(-4 * units::INCHES);
  chassis::move_voltage(-8000);
  pros::delay(1000);
  chassis::move_voltage(0);

  // reset lift
  lift::goto_sync(lift::POS_MIN);

  // intake cube
  macros::notify(macros::CODE_INTAKE_TOWER);
  chassis::move_by(12 * units::INCHES);
  chassis::move_by(-2 * units::INCHES);
  intake::move_voltage(0);

  // rotate to tower
  chassis::rotate_to_bang(-48 * units::DEGREES, 5000);
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
  chassis::move_by(-5.25 * units::INCHES);
  lift::goto_sync(lift::POS_MIN);

  // reset angler
  angler::m_motor.move_absolute(0, 200);

  // calibrate orientation
  chassis::move_by(-2 * units::INCHES);
  chassis::rotate_to_bang(0 * units::DEGREES, 5000);
  chassis::move_by(-7 * units::INCHES);
  chassis::move_voltage(-8000);
  pros::delay(1200);
  chassis::move_voltage(0);
  chassis::tare_orientation(0);

  // intake cubes for stack
  intake::move_voltage(12000);
  chassis::move_by(108 * units::INCHES, 11000, 5000, 4000, 8 * units::INCHES);
  intake::hold();

  // rotate to goal
  chassis::rotate_to_bang(-35 * units::DEGREES, 6000);

  // move to goal
  chassis::move_by(9.75 * units::INCHES);
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
  chassis::move_voltage(2000);
  pros::delay(750);

  // back out
  chassis::move_by(-26.5 * units::INCHES, 3000, 9000, 1500, 3.5 * units::INCHES);


  // third tower----------------------------------------------------------------

  // rotate to cube
  chassis::rotate_to_bang(-168 * units::DEGREES, 5000);
  chassis::rotate_to_bang(-185 * units::DEGREES);

  // reset angler
  angler::m_motor.move_absolute(0, 200);

  // intake cube
  macros::notify(macros::CODE_INTAKE_TOWER);
  chassis::move_by(25 * units::INCHES, 3500, 9500, 2000, 6 * units::INCHES, 1250, 10 * units::INCHES);
  chassis::move_by(-6 * units::INCHES);
  intake::hold();

  // set lift position
  lift::goto_sync(lift::POS_LOW_TOWER);

  // deposit cube
  chassis::move_by(4.5 * units::INCHES);
  intake::move_voltage(-7000);
  pros::delay(800);
  intake::move_voltage(0);


  // fourth tower---------------------------------------------------------------

  // back out
  chassis::move_by(-5 * units::INCHES);
  lift::goto_sync(lift::POS_MIN);

  // straigten out
  chassis::rotate_to_bang(-180 * units::DEGREES, 5000);

  // recalibrate
  chassis::move_voltage(-10000);
  pros::delay(550);
  chassis::move_voltage(-6500);
  pros::delay(1100);
  chassis::move_voltage(0);
  chassis::tare_orientation(-180 * units::DEGREES);

  // rotate to cube
  chassis::move_by(3 * units::INCHES);
  chassis::rotate_to_bang(-200 * units::DEGREES, 5000);

  // intake cube
  macros::notify(macros::CODE_INTAKE_TOWER);
  chassis::move_by(20 * units::INCHES);

  // back up
  chassis::move_by(-14 * units::INCHES);

  // rotate to tower
  chassis::rotate_to(-100 * units::DEGREES);

  // set lift position
  lift::goto_sync(lift::POS_LOW_TOWER);

  // drive to tower
  chassis::move_by(23.5 * units::INCHES);

  // deposit cube
  intake::move_voltage(-6000);
  pros::delay(600);
  intake::move_voltage(0);


  // fifth tower---------------------------------------------------------------

  // back out
  chassis::move_by(-11 * units::INCHES);

  // rotate to tower
  chassis::rotate_to_bang(-255 * units::DEGREES, 5000);
  chassis::rotate_to_bang(-270 * units::DEGREES);
  lift::goto_sync(lift::POS_MIN);

  // intake cube
  macros::notify(macros::CODE_INTAKE_TOWER);
  chassis::move_by(24 * units::INCHES);

  // back up to clear tower
  chassis::move_by(-8 * units::INCHES);

  // set lift position
  lift::goto_sync(lift::POS_HIGH_TOWER);

  // deposit cube
  chassis::move_by(10 * units::INCHES);
  intake::move_voltage(-6000);
  pros::delay(500);
  intake::hold();

  // back out
  chassis::move_by(-10 * units::INCHES);
}
