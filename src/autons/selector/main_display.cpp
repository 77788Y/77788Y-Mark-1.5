#include "auton_selector.hpp"

namespace auton_selector {


  // declare buttons
  lv_obj_t* btn_red_prot;
  lv_obj_t* btn_red_unprot;
  lv_obj_t* btn_blue_prot;
  lv_obj_t* btm_blue_unprot;
  lv_obj_t* btn_no_auton;


  // callbacks
  // lv_res_t btn_click_action_red_prot(lv_obj_t * btn) {autons::selected = autons::auto_red_prot; chassis_interface::reset_orientation(); return LV_RES_OK;}
  lv_res_t btn_click_action_red_prot(lv_obj_t * btn) {autons::selected = autons::red_protected_four; return LV_RES_OK;}
  lv_res_t btn_click_action_red_unprot(lv_obj_t * btn) {autons::selected = autons::red_unprotected_six; return LV_RES_OK;}
  lv_res_t btn_click_action_blue_prot(lv_obj_t * btn) {autons::selected = autons::blue_protected_four; return LV_RES_OK;}
  lv_res_t btn_click_action_blue_unprot(lv_obj_t * btn) {autons::selected = autons::blue_unprotected_six; return LV_RES_OK;}
  lv_res_t btn_click_action_no_auton(lv_obj_t * btn) {autons::selected = nullptr; return LV_RES_OK;}


  // create all display objects
  void create_display() {

    // initialize styles
    styles_init();

    // create red prot button
    lv_obj_t* btn_red_prot = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_set_pos(btn_red_prot, 16, 16);
    lv_obj_set_size(btn_red_prot, 96, 96);
    lv_btn_set_style(btn_red_prot, LV_BTN_STYLE_PR, &style_button_red_pressed);
    lv_btn_set_style(btn_red_prot, LV_BTN_STYLE_REL, &style_button_red);
    lv_btn_set_style(btn_red_prot, LV_BTN_STYLE_TGL_PR, &style_button_red_pressed);
    lv_btn_set_style(btn_red_prot, LV_BTN_STYLE_TGL_REL, &style_button_red);
    lv_btn_set_action(btn_red_prot, LV_BTN_ACTION_PR, btn_click_action_red_prot);

    // create red unprot button
    lv_obj_t* btn_red_unprot = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_set_pos(btn_red_unprot, 16, 128);
    lv_obj_set_size(btn_red_unprot, 96, 96);
    lv_btn_set_style(btn_red_unprot, LV_BTN_STYLE_PR, &style_button_red_pressed);
    lv_btn_set_style(btn_red_unprot, LV_BTN_STYLE_REL, &style_button_red);
    lv_btn_set_style(btn_red_unprot, LV_BTN_STYLE_TGL_PR, &style_button_red_pressed);
    lv_btn_set_style(btn_red_unprot, LV_BTN_STYLE_TGL_REL, &style_button_red);
    lv_btn_set_action(btn_red_unprot, LV_BTN_ACTION_PR, btn_click_action_red_unprot);

    // create blue prot button
    lv_obj_t* btn_blue_prot = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_set_pos(btn_blue_prot, 128, 16);
    lv_obj_set_size(btn_blue_prot, 96, 96);
    lv_btn_set_style(btn_blue_prot, LV_BTN_STYLE_PR, &style_button_blue_pressed);
    lv_btn_set_style(btn_blue_prot, LV_BTN_STYLE_REL, &style_button_blue);
    lv_btn_set_style(btn_blue_prot, LV_BTN_STYLE_TGL_PR, &style_button_blue_pressed);
    lv_btn_set_style(btn_blue_prot, LV_BTN_STYLE_TGL_REL, &style_button_blue);
    lv_btn_set_action(btn_blue_prot, LV_BTN_ACTION_PR, btn_click_action_blue_prot);

    // create blue unprot button
    lv_obj_t* btn_blue_unprot = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_set_pos(btn_blue_unprot, 128, 128);
    lv_obj_set_size(btn_blue_unprot, 96, 96);
    lv_btn_set_style(btn_blue_unprot, LV_BTN_STYLE_PR, &style_button_blue_pressed);
    lv_btn_set_style(btn_blue_unprot, LV_BTN_STYLE_REL, &style_button_blue);
    lv_btn_set_style(btn_blue_unprot, LV_BTN_STYLE_TGL_PR, &style_button_blue_pressed);
    lv_btn_set_style(btn_blue_unprot, LV_BTN_STYLE_TGL_REL, &style_button_blue);
    lv_btn_set_action(btn_blue_unprot, LV_BTN_ACTION_PR, btn_click_action_blue_unprot);

    // create no auton button
    lv_obj_t* btn_no_auton = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_set_pos(btn_no_auton, 256, 16);
    lv_obj_set_size(btn_no_auton, 208, 72);
    lv_btn_set_style(btn_no_auton, LV_BTN_STYLE_PR, &style_button_neutral_pressed);
    lv_btn_set_style(btn_no_auton, LV_BTN_STYLE_REL, &style_button_neutral);
    lv_btn_set_style(btn_no_auton, LV_BTN_STYLE_TGL_PR, &style_button_neutral_pressed);
    lv_btn_set_style(btn_no_auton, LV_BTN_STYLE_TGL_REL, &style_button_neutral);
    lv_btn_set_action(btn_no_auton, LV_BTN_ACTION_PR, btn_click_action_no_auton);

  }
}
