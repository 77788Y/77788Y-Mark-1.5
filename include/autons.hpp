#pragma once

#include <memory>

namespace autons {

  inline void (*selected)() = nullptr;

  void blue_unprotected_six();
  void red_unprotected_six();

  void red_protected_four();
  void blue_protected_four();

  void skills_auton();
}
