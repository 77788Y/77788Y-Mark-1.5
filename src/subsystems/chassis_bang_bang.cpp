#include "subsystems/chassis.hpp"
#include "lib/generic.hpp"
#include <iostream>

namespace subsystems {
  namespace chassis {

    void move_to_bang(units::Distance dist, int voltage) {
      int sign = generic::sign(dist - dist_avg);
      move_voltage(voltage * sign);
      while (fabs(dist - dist_avg) > .5 * units::INCHES && generic::sign(dist - dist_avg) == sign) {
        pros::delay(10);
      }
      hold();
      pros::delay(200);
    }


    void move_by_bang(units::Distance dist, int voltage) {
      move_to_bang(dist_avg + dist, voltage);
    }
    void rotate_to_bang(units::Angle angle, int voltage) {
      int sign = generic::sign(angle - orientation);
      move_voltage(-voltage * sign, voltage * sign);
      while (fabs(angle - orientation) > 2 * units::DEGREES && generic::sign(angle - orientation) == sign) {
        pros::delay(10);
      }
      hold();
      pros::delay(200);
    }
    void rotate_by_bang(units::Angle angle, int voltage) {
      rotate_to_bang(orientation + angle, voltage);
    }
  }
}
