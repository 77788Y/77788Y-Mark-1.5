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
  while (angler::pos < angler::POS_RETRACTED && pros::millis() - start_time < 1000) angler::move_voltage(-12000);
  pros::delay(50);
  angler::m_motor.tare_position();
  angler::hold();
  lift::move_voltage(0);
  lift::hold();
  pros::delay(50);
  while (lift::pos < lift::POS_MIN + 10 * units::DEGREES && pros::millis() - start_time < 1500) lift::move_voltage(12000);
  lift::move_voltage(-8000);
  pros::delay(350);
  lift::move_voltage(-3000);
  pros::delay(200);
  lift::m_motor.tare_position();
  lift::hold();
}


void autonomous() {
  // line tracker
  pros::ADIAnalogIn cube_detect('H');

  chassis::tare_position(0);
  chassis::tare_orientation(0);
  chassis::move_voltage(-5000);
  flip_out();

  // try {if (autons::selected != nullptr) autons::selected();}
  // catch (...) {}

// red
  // autons::red_unprotected_six();
  // autons::red_protected_four();
  // autons::red_unprotected_seven();

// blue
  // autons::blue_unprotected_six();
  // autons::blue_protected_four();
  // autons::blue_unprotected_seven();

// skills
  autons::skills_auton();
}
