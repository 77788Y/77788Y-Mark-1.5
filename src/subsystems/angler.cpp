#include "subsystems/angler.hpp"
#include <cmath>
#include <iostream>

namespace subsystems {
  namespace angler {

    ////
    // motors, sensors, etc

    // motor
    pros::Motor m_motor (2, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);



    ////
    // control functions

    // update sensors
    void sensors_update() {
      pos = -m_motor.get_position() * units::DEGREES * 3.0 / 35.0 + POS_RETRACTED;
    }

    // move voltage (same left/right)
    void move_voltage(int val) {
      // if (m_motor.get_brake_mode() != pros::E_MOTOR_BRAKE_COAST) m_motor.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
      m_motor.move_voltage(val);
    }

    // move velocity
    void move_velocity(int val) {
      // if (m_motor.get_brake_mode() != pros::E_MOTOR_BRAKE_COAST) m_motor.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
      if (abs(val) > 5) m_motor.move_velocity(val);
      else m_motor.move_velocity(0);
    }

    // update auto deposit
    void update_auto_deposit(int speedy) {
      if (m_motor.get_current_draw() > 8000) {
      if (m_motor.get_brake_mode() != pros::E_MOTOR_BRAKE_COAST) m_motor.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
        move_voltage(0);
      }
      else if (pos > POS_DEPOSIT - 2 * units::DEGREES) move_velocity((pos - POS_DEPOSIT) * (175 + (speedy * 75)));
      else move_voltage(0);
    }

    // hold position
    void hold() {
      if (m_motor.get_brake_mode() != pros::E_MOTOR_BRAKE_HOLD) {
        m_motor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
        m_motor.move_velocity(0);
      }
    }
  }
}
