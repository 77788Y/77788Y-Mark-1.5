#include "main.h"
#include "macros.hpp"
#include "subsystems/async_control.hpp"
#include "auton_selector.hpp"
#include <memory>

void initialize() {

  // initialize subsystem controllers
  macros::init();
  subsystems::task = std::make_unique<pros::Task>(pros::Task(subsystems::update_controllers, nullptr, "subsystems"));
  subsystems::lift::task = std::make_unique<pros::Task>(pros::Task(subsystems::lift::task_update, nullptr, "lift"));

  // initialize display
  // display::init();
  auton_selector::create_display();
}

void disabled() {

}

void competition_initialize() {

}
