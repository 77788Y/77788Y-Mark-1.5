#include "subsystems/chassis.hpp"

#ifdef USE_VELOCITY

#include "lib/sine_profile.hpp"
#include "lib/generic.hpp"
#include <iostream>

namespace subsystems {
  namespace chassis {

    ////
    // move a distance

    // relative motion
    void move_by(units::Distance dist, units::Time timeout, int max_vel, int start_vel, units::Distance accel_dist, int end_vel, units::Distance decel_dist, double angle_correct_weight) {

      // calculate scale
      double scale = accel_dist + decel_dist > fabs(dist) ? fabs(dist / (accel_dist + decel_dist)) : 1;

      // scale all values to be possible
      units::Distance actual_accel_dist = accel_dist * scale;
      units::Distance actual_decel_dist = decel_dist * scale;
      int actual_max_vel = start_vel < end_vel ?
        (max_vel - start_vel) * scale + start_vel :
        (max_vel - end_vel)   * scale + end_vel;

      // correct signs in case of backwards movement
      int sign = generic::sign(dist);
      int actual_start_vel = start_vel * sign;
      int actual_end_vel   = end_vel   * sign;
      actual_accel_dist *= sign;
      actual_decel_dist *= sign;
      actual_max_vel *= sign;

      // generate profiles
      SineProfile accel_profile(actual_start_vel, actual_max_vel, actual_accel_dist);
      SineProfile decel_profile(actual_max_vel,   actual_end_vel, actual_decel_dist);

      // calculate motion parameters
      units::Distance starting_pos = dist_avg;
      units::Angle starting_orientation = orientation;
      units::Distance target_dist = dist_avg + dist;
      units::Time interrupt_time = timeout >= 0 ? pros::millis() + timeout : timeout;

      // follow accel profile
      while ((pros::millis() < interrupt_time || interrupt_time < 0) && sign * (actual_accel_dist - (dist_avg - starting_pos)) > 0) {

        // calculate raw vel
        double speed = accel_profile.get_at(dist_avg - starting_pos);

        // correct angle
        double correct_vel = (starting_orientation - orientation) * angle_correct_weight;

        // move motors
        move_velocity(speed - correct_vel, speed + correct_vel);
        pros::delay(10);
      }

      // move at constant speed
      while ((pros::millis() < interrupt_time || interrupt_time < 0) && sign * ((target_dist - actual_decel_dist) - dist_avg) > 0) {

        double correct_vel = (starting_orientation - orientation) * angle_correct_weight;
        move_velocity(actual_max_vel - correct_vel, actual_max_vel + correct_vel);
        pros::delay(10);
      }

      // follow decel profile
      while ((pros::millis() < interrupt_time || interrupt_time < 0) && sign * (target_dist - dist_avg) > 0) {

        // calculate raw vel
        double speed = decel_profile.get_at(actual_decel_dist - (target_dist - dist_avg));

        std::cout << speed << std::endl;

        // correct angle
        double correct_vel = (starting_orientation - orientation) * angle_correct_weight;

        // move motors
        move_velocity(speed - correct_vel, speed + correct_vel);
        pros::delay(10);
      }

      // brake
      hold();
    }

  ////
  // rotate

  // relative motion
    void rotate_by(units::Angle angle, Side side, units::Time timeout, int max_vel, int start_vel, units::Angle accel_angle, int end_vel, units::Angle decel_angle) {

      // hold if applicable
      switch (side) {
        case (Side::RIGHT): hold(Side::LEFT); break;
        case (Side::LEFT): hold(Side::RIGHT); break;
        case (Side::BOTH): break;
      }

      // calculate scale
      double scale = accel_angle + decel_angle > fabs(angle) ? fabs(angle / (accel_angle + decel_angle)) : 1;

      // scale all values to be possible
      units::Angle actual_accel_angle = accel_angle * scale;
      units::Angle actual_decel_angle = accel_angle * scale;
      int actual_max_vel = start_vel < end_vel ?
        (max_vel - start_vel) * scale + start_vel :
        (max_vel - end_vel)   * scale + end_vel;

      // correct signs in case of backwards movement
      int sign = generic::sign(angle);
      int actual_start_vel = start_vel * sign;
      int actual_end_vel   = end_vel   * sign;
      actual_accel_angle *= sign;
      actual_decel_angle *= sign;
      actual_max_vel *= sign;

      // generate profiles
      SineProfile accel_profile(actual_start_vel, actual_max_vel, actual_accel_angle);
      SineProfile decel_profile(actual_max_vel,   actual_end_vel, actual_decel_angle);

      // calculate exit parameters
      units::Distance starting_pos = orientation;
      units::Distance target_angle = orientation + angle;
      units::Time interrupt_time = timeout >= 0 ? pros::millis() + timeout : timeout;

      // follow accel profile
      while ((pros::millis() < interrupt_time || interrupt_time < 0) && sign * (actual_accel_angle - (orientation - starting_pos)) > 0) {

        double speed = accel_profile.get_at(orientation - starting_pos);
        switch (side) {
          case (Side::RIGHT): move_velocity(0, speed, true); break;
          case (Side::LEFT): move_velocity(-speed, 0, true); break;
          case (Side::BOTH): move_velocity(-speed, speed); break;
        }
        if (pros::millis() % 100 < 10) std::cout << speed << std::endl;
        pros::delay(10);
      }

      // move at constant speed
        switch (side) {
          case (Side::RIGHT): move_velocity(0, actual_max_vel, true); break;
          case (Side::LEFT): move_velocity(-actual_max_vel, 0, true); break;
          case (Side::BOTH): move_velocity(-actual_max_vel, actual_max_vel); break;
        }
      std::cout << actual_max_vel << std::endl;
      while ((pros::millis() < interrupt_time || interrupt_time < 0) && sign * ((target_angle - actual_decel_angle) - orientation) > 0) pros::delay(10);

      // follow decel profile
      while ((pros::millis() < interrupt_time || interrupt_time < 0) && sign * (target_angle - orientation) > 0) {

        double speed = decel_profile.get_at(actual_decel_angle - (target_angle - orientation));
        if (pros::millis() % 100 < 10) std::cout << speed << std::endl;
        switch (side) {
          case (Side::LEFT): move_velocity(0, speed, true); break;
          case (Side::RIGHT): move_velocity(-speed, 0, true); break;
          case (Side::BOTH): move_velocity(-speed, speed); break;
        }
        pros::delay(10);
      }

      // brake
      hold();
    }
  }
}

#endif
