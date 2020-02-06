#include "lib/motion_profile.hpp"

MotionProfile::MotionProfile(double dist, double accel, double decel, double start_vel, double end_vel, double max_vel):
  m_dist{dist},
  m_accel{accel},
  m_decel{decel},
  m_start_vel{start_vel},
  m_end_vel{end_vel},
  m_max_vel{max_vel} {
    
  // calculate thing
}

double MotionProfile::get_value() {
  return m_calculation;
}

double MotionProfile::update() {

  return m_calculation;
}