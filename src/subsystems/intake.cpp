#include "subsystems/intake.hpp"

namespace subsystems {
  namespace intake {

    ////
    // motors, sensors, etc

    // motor
    pros::Motor m_left  (11, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
    pros::Motor m_right (8, pros::E_MOTOR_GEARSET_18, true,  pros::E_MOTOR_ENCODER_DEGREES);



    ////
    // control functions

    // move voltage
    void move_voltage(int l, int r) {
      if (m_left.get_brake_mode() != pros::E_MOTOR_BRAKE_COAST) m_left.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
      if (m_right.get_brake_mode() != pros::E_MOTOR_BRAKE_COAST) m_right.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
      m_left.move_voltage(l);
      m_right.move_voltage(r);
    }
    void move_voltage(int val) {
      move_voltage(val, val);
    }

    // hold position
    void hold() {
      if (m_left.get_brake_mode() != pros::E_MOTOR_BRAKE_HOLD) {
        m_left.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
         m_left.move_velocity(0);
      }
      if (m_right.get_brake_mode() != pros::E_MOTOR_BRAKE_HOLD) {
        m_right.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
        m_right.move_velocity(0);
      }
    }
  }
}
