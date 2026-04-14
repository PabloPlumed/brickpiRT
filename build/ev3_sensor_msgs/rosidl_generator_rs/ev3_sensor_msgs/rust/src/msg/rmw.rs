#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};


#[link(name = "ev3_sensor_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__ev3_sensor_msgs__msg__Button() -> *const std::ffi::c_void;
}

#[link(name = "ev3_sensor_msgs__rosidl_generator_c")]
extern "C" {
    fn ev3_sensor_msgs__msg__Button__init(msg: *mut Button) -> bool;
    fn ev3_sensor_msgs__msg__Button__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<Button>, size: usize) -> bool;
    fn ev3_sensor_msgs__msg__Button__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<Button>);
    fn ev3_sensor_msgs__msg__Button__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<Button>, out_seq: *mut rosidl_runtime_rs::Sequence<Button>) -> bool;
}

// Corresponds to ev3_sensor_msgs__msg__Button
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct Button {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::rmw::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub state: u8,

}

impl Button {

    // This constant is not documented.
    #[allow(missing_docs)]
    pub const RELEASED: u8 = 0;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const PRESSED: u8 = 1;

}


impl Default for Button {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !ev3_sensor_msgs__msg__Button__init(&mut msg as *mut _) {
        panic!("Call to ev3_sensor_msgs__msg__Button__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for Button {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { ev3_sensor_msgs__msg__Button__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { ev3_sensor_msgs__msg__Button__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { ev3_sensor_msgs__msg__Button__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for Button {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for Button where Self: Sized {
  const TYPE_NAME: &'static str = "ev3_sensor_msgs/msg/Button";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__ev3_sensor_msgs__msg__Button() }
  }
}


#[link(name = "ev3_sensor_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__ev3_sensor_msgs__msg__Color() -> *const std::ffi::c_void;
}

#[link(name = "ev3_sensor_msgs__rosidl_generator_c")]
extern "C" {
    fn ev3_sensor_msgs__msg__Color__init(msg: *mut Color) -> bool;
    fn ev3_sensor_msgs__msg__Color__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<Color>, size: usize) -> bool;
    fn ev3_sensor_msgs__msg__Color__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<Color>);
    fn ev3_sensor_msgs__msg__Color__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<Color>, out_seq: *mut rosidl_runtime_rs::Sequence<Color>) -> bool;
}

// Corresponds to ev3_sensor_msgs__msg__Color
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct Color {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::rmw::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub color: rosidl_runtime_rs::String,

}



impl Default for Color {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !ev3_sensor_msgs__msg__Color__init(&mut msg as *mut _) {
        panic!("Call to ev3_sensor_msgs__msg__Color__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for Color {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { ev3_sensor_msgs__msg__Color__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { ev3_sensor_msgs__msg__Color__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { ev3_sensor_msgs__msg__Color__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for Color {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for Color where Self: Sized {
  const TYPE_NAME: &'static str = "ev3_sensor_msgs/msg/Color";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__ev3_sensor_msgs__msg__Color() }
  }
}


