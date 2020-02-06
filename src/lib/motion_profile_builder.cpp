#include "lib/motion_profile.hpp"

MotionProfileBuilder::MotionProfileBuilder(double dist):
  m_dist{dist},
  m_accel{1},
  m_decel{1},
  m_start_vel(0),
  m_end_vel{0},
  m_max_vel{200} {}

MotionProfile MotionProfileBuilder::build() {
  return {m_dist, m_accel, m_decel, m_start_vel, m_end_vel, m_max_vel};
}

MotionProfileBuilder& MotionProfileBuilder::with_accel(double accel) {
  m_accel = accel;
  return *this;
}

MotionProfileBuilder& MotionProfileBuilder::with_decel(double decel) {
  m_decel = decel;
  return *this;
}

MotionProfileBuilder& MotionProfileBuilder::with_start_vel(double vel) {
  m_start_vel = vel;
  return *this;
}

MotionProfileBuilder& MotionProfileBuilder::with_end_vel(double vel) {
  m_end_vel = vel;
  return *this;
}

MotionProfileBuilder& MotionProfileBuilder::with_max_vel(double vel) {
  m_max_vel = vel;
  return *this;
}