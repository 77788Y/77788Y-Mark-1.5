#include "main.h"
#include "subsystems/lift.hpp"
#include "subsystems/angler.hpp"
#include "subsystems/chassis.hpp"
#include "subsystems/intake.hpp"
#include "autons.hpp"

using namespace subsystems;

void red_wide_zone() {

  int start_time = pros::millis();

  // tare orientation
  chassis::tare_orientation(0);

  // get first purple cube
  intake::move_voltage(12000);
  chassis::move_to(10 * units::INCHES, 3000);
  pros::delay(300);
  intake::move_voltage(0);
  chassis::move_to(3 * units::INCHES, 2500);

  // rotate to right angle
  chassis::rotate_by(45 * units::DEGREES, 1200);

  // intake orange cube while moving to next cube
  intake::move_voltage(12000);
  chassis::move_by(25 * units::INCHES, 5000);

  

}
