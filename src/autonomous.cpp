#include "main.h"
#include "subsystems/lift.hpp"
#include "subsystems/angler.hpp"
#include "subsystems/chassis.hpp"
#include "subsystems/intake.hpp"
#include "autons.hpp"

using namespace subsystems;

void flip_out(){
  lift::move_voltage(-6000);
  while (angler::pos > angler::POS_RETRACTED - 25 * units::DEGREES) angler::move_voltage(12000);
  while (angler::pos < angler::POS_RETRACTED) angler::move_voltage(-12000);
  angler::hold();
  lift::move_voltage(0);
  lift::hold();
  pros::delay(100);
  while (lift::pos < lift::POS_MIN + 10 * units::DEGREES) lift::move_voltage(12000);
  lift::move_voltage(-8000);
  pros::delay(350);
  lift::hold();
}


void autonomous() {

  chassis::move_voltage(-5000);
  flip_out();

  // red_fivecube();
  // blue_fivecube();
  // red_wide_zone();
  red_wide_four();
  // blue_wide_zone();
  // skills_auton();
}
