#include "main.h"
#include "subsystems/lift.hpp"
#include "subsystems/angler.hpp"
#include "subsystems/chassis.hpp"
#include "subsystems/intake.hpp"
#include "autons.hpp"

using namespace subsystems;

void flip_out(){
  int start_time = pros::millis();

  lift::move_voltage(-6000);
  while (angler::pos > angler::POS_RETRACTED - 25 * units::DEGREES && pros::millis() - start_time < 600) angler::move_voltage(12000);
  while (angler::pos < angler::POS_RETRACTED && pros::millis() - start_time < 1500) angler::move_voltage(-12000);
  pros::delay(100);
  angler::m_motor.tare_position();
  angler::hold();
  lift::move_voltage(0);
  lift::hold();
  pros::delay(100);
  while (lift::pos < lift::POS_MIN + 10 * units::DEGREES && pros::millis() - start_time < 1500) lift::move_voltage(12000);
  lift::move_voltage(-8000);
  pros::delay(350);
  lift::move_voltage(-3000);
  pros::delay(200);
  lift::m_motor.tare_position();
  lift::hold();
}


void autonomous() {
  chassis::tare_position(0);
  chassis::tare_orientation(0);
  chassis::move_voltage(-5000);
  flip_out();

  try {if (autons::selected != nullptr) autons::selected();}
  catch (...) {}

// red
  // red_unprotected_six();
  // red_protected_four();
  // red_protected_seven();

// blue
  // blue_unprotected_six();
  // blue_protected_four();
  // blue_unprotected_seven();

// skills
  // autons::skills_auton();
}
