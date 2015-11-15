;; Auto-generated. Do not edit!


(when (boundp 'smart_battery_msgs::SmartBatteryStatus)
  (if (not (find-package "SMART_BATTERY_MSGS"))
    (make-package "SMART_BATTERY_MSGS"))
  (shadow 'SmartBatteryStatus (find-package "SMART_BATTERY_MSGS")))
(unless (find-package "SMART_BATTERY_MSGS::SMARTBATTERYSTATUS")
  (make-package "SMART_BATTERY_MSGS::SMARTBATTERYSTATUS"))

(in-package "ROS")
;;//! \htmlinclude SmartBatteryStatus.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(intern "*DISCHARGING*" (find-package "SMART_BATTERY_MSGS::SMARTBATTERYSTATUS"))
(shadow '*DISCHARGING* (find-package "SMART_BATTERY_MSGS::SMARTBATTERYSTATUS"))
(defconstant smart_battery_msgs::SmartBatteryStatus::*DISCHARGING* 0)
(intern "*CHARGING*" (find-package "SMART_BATTERY_MSGS::SMARTBATTERYSTATUS"))
(shadow '*CHARGING* (find-package "SMART_BATTERY_MSGS::SMARTBATTERYSTATUS"))
(defconstant smart_battery_msgs::SmartBatteryStatus::*CHARGING* 1)
(intern "*CHARGED*" (find-package "SMART_BATTERY_MSGS::SMARTBATTERYSTATUS"))
(shadow '*CHARGED* (find-package "SMART_BATTERY_MSGS::SMARTBATTERYSTATUS"))
(defconstant smart_battery_msgs::SmartBatteryStatus::*CHARGED* 2)
(defclass smart_battery_msgs::SmartBatteryStatus
  :super ros::object
  :slots (_header _voltage _rate _charge _capacity _design_capacity _percentage _charge_state _present ))

(defmethod smart_battery_msgs::SmartBatteryStatus
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:voltage __voltage) 0.0)
    ((:rate __rate) 0.0)
    ((:charge __charge) 0.0)
    ((:capacity __capacity) 0.0)
    ((:design_capacity __design_capacity) 0.0)
    ((:percentage __percentage) 0)
    ((:charge_state __charge_state) 0)
    ((:present __present) nil)
    )
   (send-super :init)
   (setq _header __header)
   (setq _voltage (float __voltage))
   (setq _rate (float __rate))
   (setq _charge (float __charge))
   (setq _capacity (float __capacity))
   (setq _design_capacity (float __design_capacity))
   (setq _percentage (round __percentage))
   (setq _charge_state (round __charge_state))
   (setq _present __present)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:voltage
   (&optional __voltage)
   (if __voltage (setq _voltage __voltage)) _voltage)
  (:rate
   (&optional __rate)
   (if __rate (setq _rate __rate)) _rate)
  (:charge
   (&optional __charge)
   (if __charge (setq _charge __charge)) _charge)
  (:capacity
   (&optional __capacity)
   (if __capacity (setq _capacity __capacity)) _capacity)
  (:design_capacity
   (&optional __design_capacity)
   (if __design_capacity (setq _design_capacity __design_capacity)) _design_capacity)
  (:percentage
   (&optional __percentage)
   (if __percentage (setq _percentage __percentage)) _percentage)
  (:charge_state
   (&optional __charge_state)
   (if __charge_state (setq _charge_state __charge_state)) _charge_state)
  (:present
   (&optional __present)
   (if __present (setq _present __present)) _present)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; float32 _voltage
    4
    ;; float32 _rate
    4
    ;; float32 _charge
    4
    ;; float32 _capacity
    4
    ;; float32 _design_capacity
    4
    ;; int32 _percentage
    4
    ;; uint8 _charge_state
    1
    ;; bool _present
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; float32 _voltage
       (sys::poke _voltage (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _rate
       (sys::poke _rate (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _charge
       (sys::poke _charge (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _capacity
       (sys::poke _capacity (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _design_capacity
       (sys::poke _design_capacity (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; int32 _percentage
       (write-long _percentage s)
     ;; uint8 _charge_state
       (write-byte _charge_state s)
     ;; bool _present
       (if _present (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; float32 _voltage
     (setq _voltage (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _rate
     (setq _rate (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _charge
     (setq _charge (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _capacity
     (setq _capacity (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _design_capacity
     (setq _design_capacity (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; int32 _percentage
     (setq _percentage (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; uint8 _charge_state
     (setq _charge_state (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; bool _present
     (setq _present (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(setf (get smart_battery_msgs::SmartBatteryStatus :md5sum-) "201bffbb268bdae8f8389acae4ae6db2")
(setf (get smart_battery_msgs::SmartBatteryStatus :datatype-) "smart_battery_msgs/SmartBatteryStatus")
(setf (get smart_battery_msgs::SmartBatteryStatus :definition-)
      "uint8 DISCHARGING = 0
uint8 CHARGING    = 1
uint8 CHARGED     = 2

Header  header
float32 voltage          # Voltage in Volts
float32 rate             # Negative when discharging (A)
float32 charge           # Current charge in Ah
float32 capacity         # Capacity in Ah (last full capacity)
float32 design_capacity  # Capacity in Ah (design capacity)
int32   percentage       # Charge percentage
uint8   charge_state     # Enum 
bool    present          # Should be an error if battery is not present
================================================================================
MSG: std_msgs/Header
# Standard metadata for higher-level stamped data types.
# This is generally used to communicate timestamped data 
# in a particular coordinate frame.
# 
# sequence ID: consecutively increasing ID 
uint32 seq
#Two-integer timestamp that is expressed as:
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
# time-handling sugar is provided by the client library
time stamp
#Frame this data is associated with
# 0: no frame
# 1: global frame
string frame_id

")



(provide :smart_battery_msgs/SmartBatteryStatus "201bffbb268bdae8f8389acae4ae6db2")


