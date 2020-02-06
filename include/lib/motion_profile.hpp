#include "lib/units.hpp"

class MotionProfile {

  friend class MotionProfileBuilder;

  public:
  MotionProfile(double dist, double accel, double decel, double start_vel, double end_vel, double max_vel);
  double get_value();
  double update();

  private:
  double m_calculation;
  double m_dist;
  double m_accel;
  double m_decel;
  double m_start_vel;
  double m_end_vel;
  double m_max_vel;
  double m_coast_vel;
  double m_start_time;
  int m_duration;
  std::pair<double, double> m_accel_period;
  std::pair<double, double> m_decel_period;
  std::pair<double, double> m_coast_period;

  void generate_profile();
};

class MotionProfileBuilder {

  public:
  MotionProfileBuilder(double dist);
  MotionProfile build();
  MotionProfileBuilder& with_accel(double accel);
  MotionProfileBuilder& with_decel(double decel);
  MotionProfileBuilder& with_start_vel(double vel);
  MotionProfileBuilder& with_end_vel(double vel);
  MotionProfileBuilder& with_max_vel(double vel);

  private:
  double m_dist;
  double m_accel;
  double m_decel;
  double m_start_vel;
  double m_end_vel;
  double m_max_vel;
};