#include "main.h"
#include "macros.hpp"
#include "lib/joystick.hpp"
#include "lib/generic.hpp"
#include "subsystems/chassis.hpp"
#include "subsystems/lift.hpp"
#include "subsystems/intake.hpp"
#include "subsystems/angler.hpp"

// import subsystems into current namespace
using namespace subsystems;

// declare and define controller
Joystick controller;

void opcontrol() {

  // line tracker
  pros::ADIAnalogIn cube_detect('H');

	// lift control data
	int lift_index = 0;
	units::Angle lift_angles[] = {lift::POS_MIN, lift::POS_LOW_TOWER, lift::POS_HIGH_TOWER, lift::POS_MAX};

  int start_time = pros::millis();
  units::Angle lift_target = lift::POS_MIN;

  // lift::move_voltage(-6000);
  // while (angler::pos > angler::POS_RETRACTED - 25 * units::DEGREES && pros::millis() - start_time < 600) angler::move_voltage(12000);
  // while (angler::pos < angler::POS_RETRACTED && pros::millis() - start_time < 1500) angler::move_voltage(-12000);
  // angler::hold();
  // lift::move_voltage(0);
  // lift::hold();
  // pros::delay(100);
  // while (lift::pos < lift::POS_MIN + 10 * units::DEGREES && pros::millis() - start_time < 1500) lift::move_voltage(12000);
  // lift::move_voltage(-8000);
  // pros::delay(350);
  // lift::move_voltage(-3000);


	while (true) {

		// update controller
		controller.update();

		// dirty hack to disable angler
		if (macros::current == macros::CODE_ANGLER_LIFT && (controller.btn_r1 || controller.btn_r2 || controller.btn_x || controller.btn_b || controller.btn_a)) {
			macros::notify(macros::CODE_INTERRUPT);
			pros::delay(2);
		}

		// drive
		if (controller.btn_left) chassis::hold();
		else {

			// exponential drive
			double left  = (.25 * pow(5, fabs(controller.analog_left_y))  - .25) * generic::sign(controller.analog_left_y);
			double right = (.25 * pow(5, fabs(controller.analog_right_y)) - .25) * generic::sign(controller.analog_right_y);

			chassis::move_voltage(left * 12000.0, right * 12000.0);
		}

		// lift
		if (controller.btn_l1_new == 1) {

			++lift_index;
			if (lift_index > 3) lift_index = 3;
      lift_target = lift_angles[lift_index];
      lift::goto_async(lift_target);
		}
		else if (controller.btn_l2_new == 1) {

			lift_index = 0;
      lift_target = lift_angles[lift_index];
      lift::goto_async(lift_target);
		}
    else if (
      lift_target > lift::POS_MIN &&
      lift::pos > lift::POS_MIN + 20*units::DEGREES &&
      controller.analog_left_y < -.1 &&
      controller.analog_right_y < -.1 &&
      lift_target <= lift_angles[lift_index]
    ) {
      lift_target = lift_angles[lift_index] + 10 * units::DEGREES;
      lift::goto_async(lift_target);
    }
    else if (
      lift::pos > lift::POS_MIN + 20*units::DEGREES &&
      controller.analog_left_y >= -.1 &&
      controller.analog_right_y >= -.1 &&
      lift_target > lift_angles[lift_index]
    ) {
      lift_target = lift_angles[lift_index];
      lift::goto_async(lift_target);
    }

		if (macros::current != macros::CODE_ANGLER_LIFT) {

			// intake
			if (controller.btn_r1 && controller.btn_r2) intake::move_voltage(-12000);
      else if (lift::pos > lift::POS_LOW_TOWER + 20 * units::DEGREES && controller.btn_r2) intake::move_voltage(-5500);
			else if (lift::pos > lift::POS_MIN + 20 * units::DEGREES && controller.btn_r2) intake::move_voltage(-7000);
			else if (controller.btn_r1 - controller.btn_r2) intake::move_voltage((controller.btn_r1 - controller.btn_r2) * 12000);
			else if (controller.btn_a) intake::move_voltage(-1000);
			else if (controller.btn_b - controller.btn_x) intake::move_voltage((controller.btn_b - controller.btn_x) * 1000);
			else intake::hold();

			// angler
			if (controller.btn_a) angler::update_auto_deposit();
			else if (controller.btn_a_new == -1) angler::hold();
			else if (controller.btn_b_new == 1 && lift::pos) angler::m_motor.move_absolute(0, 200);
		}

		// debug
		// if (controller.btn_left) chassis::tare_orientation(90 * units::DEGREES);
		if (true && pros::millis() % 250 <= 10) {

			std::cout << "Angler angle:  " << angler::pos / units::DEGREES << "°" << std::endl;
			std::cout << "Lift angle:    " << angler::pos / units::DEGREES << "°" << std::endl;
			std::cout << "Chassis Left:  " << chassis::dist_l << "\"" << std::endl;
			std::cout << "Chassis Right: " << chassis::dist_r << "\"" << std::endl;
			std::cout << "Chassis Angle: " << chassis::orientation / units::DEGREES << "°" << std::endl;
      std::cout << "Cube int tray: " << (cube_detect.get_value() < 1700) << std::endl << std::endl;
		}

    if (pros::millis() >= 250 && cube_detect.get_value() < 1700) std::cout << "CUBE" << std::endl;
    else if (pros::millis() % 250 <= 10) std::cout << std::endl;

		pros::delay(10);
	}
}
