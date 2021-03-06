;; Auto-generated. Do not edit!


(when (boundp 'test2::robot_info)
  (if (not (find-package "TEST2"))
    (make-package "TEST2"))
  (shadow 'robot_info (find-package "TEST2")))
(unless (find-package "TEST2::ROBOT_INFO")
  (make-package "TEST2::ROBOT_INFO"))

(in-package "ROS")
;;//! \htmlinclude robot_info.msg.html


(defclass test2::robot_info
  :super ros::object
  :slots (_Control_State _Robot_State _Robot_Position _Task_Type _Route_Serial ))

(defmethod test2::robot_info
  (:init
   (&key
    ((:Control_State __Control_State) 0)
    ((:Robot_State __Robot_State) 0)
    ((:Robot_Position __Robot_Position) 0)
    ((:Task_Type __Task_Type) 0)
    ((:Route_Serial __Route_Serial) 0)
    )
   (send-super :init)
   (setq _Control_State (round __Control_State))
   (setq _Robot_State (round __Robot_State))
   (setq _Robot_Position (round __Robot_Position))
   (setq _Task_Type (round __Task_Type))
   (setq _Route_Serial (round __Route_Serial))
   self)
  (:Control_State
   (&optional __Control_State)
   (if __Control_State (setq _Control_State __Control_State)) _Control_State)
  (:Robot_State
   (&optional __Robot_State)
   (if __Robot_State (setq _Robot_State __Robot_State)) _Robot_State)
  (:Robot_Position
   (&optional __Robot_Position)
   (if __Robot_Position (setq _Robot_Position __Robot_Position)) _Robot_Position)
  (:Task_Type
   (&optional __Task_Type)
   (if __Task_Type (setq _Task_Type __Task_Type)) _Task_Type)
  (:Route_Serial
   (&optional __Route_Serial)
   (if __Route_Serial (setq _Route_Serial __Route_Serial)) _Route_Serial)
  (:serialization-length
   ()
   (+
    ;; uint16 _Control_State
    2
    ;; uint16 _Robot_State
    2
    ;; uint16 _Robot_Position
    2
    ;; uint16 _Task_Type
    2
    ;; uint16 _Route_Serial
    2
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint16 _Control_State
       (write-word _Control_State s)
     ;; uint16 _Robot_State
       (write-word _Robot_State s)
     ;; uint16 _Robot_Position
       (write-word _Robot_Position s)
     ;; uint16 _Task_Type
       (write-word _Task_Type s)
     ;; uint16 _Route_Serial
       (write-word _Route_Serial s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint16 _Control_State
     (setq _Control_State (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; uint16 _Robot_State
     (setq _Robot_State (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; uint16 _Robot_Position
     (setq _Robot_Position (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; uint16 _Task_Type
     (setq _Task_Type (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; uint16 _Route_Serial
     (setq _Route_Serial (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;;
   self)
  )

(setf (get test2::robot_info :md5sum-) "ec4a3f57734c2b806790604232e483b2")
(setf (get test2::robot_info :datatype-) "test2/robot_info")
(setf (get test2::robot_info :definition-)
      "uint16 Control_State
uint16 Robot_State
uint16 Robot_Position
uint16 Task_Type
uint16 Route_Serial

")



(provide :test2/robot_info "ec4a3f57734c2b806790604232e483b2")


