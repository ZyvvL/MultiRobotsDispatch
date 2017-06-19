;; Auto-generated. Do not edit!


(when (boundp 'test1::robot_dispatch)
  (if (not (find-package "TEST1"))
    (make-package "TEST1"))
  (shadow 'robot_dispatch (find-package "TEST1")))
(unless (find-package "TEST1::ROBOT_DISPATCH")
  (make-package "TEST1::ROBOT_DISPATCH"))

(in-package "ROS")
;;//! \htmlinclude robot_dispatch.msg.html


(defclass test1::robot_dispatch
  :super ros::object
  :slots (_Robot_Serial _Instruct _PausePosition ))

(defmethod test1::robot_dispatch
  (:init
   (&key
    ((:Robot_Serial __Robot_Serial) 0)
    ((:Instruct __Instruct) 0)
    ((:PausePosition __PausePosition) 0)
    )
   (send-super :init)
   (setq _Robot_Serial (round __Robot_Serial))
   (setq _Instruct (round __Instruct))
   (setq _PausePosition (round __PausePosition))
   self)
  (:Robot_Serial
   (&optional __Robot_Serial)
   (if __Robot_Serial (setq _Robot_Serial __Robot_Serial)) _Robot_Serial)
  (:Instruct
   (&optional __Instruct)
   (if __Instruct (setq _Instruct __Instruct)) _Instruct)
  (:PausePosition
   (&optional __PausePosition)
   (if __PausePosition (setq _PausePosition __PausePosition)) _PausePosition)
  (:serialization-length
   ()
   (+
    ;; uint16 _Robot_Serial
    2
    ;; uint16 _Instruct
    2
    ;; uint16 _PausePosition
    2
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint16 _Robot_Serial
       (write-word _Robot_Serial s)
     ;; uint16 _Instruct
       (write-word _Instruct s)
     ;; uint16 _PausePosition
       (write-word _PausePosition s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint16 _Robot_Serial
     (setq _Robot_Serial (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; uint16 _Instruct
     (setq _Instruct (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; uint16 _PausePosition
     (setq _PausePosition (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;;
   self)
  )

(setf (get test1::robot_dispatch :md5sum-) "45ae8b3befd8df4adf441be85bfd7b86")
(setf (get test1::robot_dispatch :datatype-) "test1/robot_dispatch")
(setf (get test1::robot_dispatch :definition-)
      "uint16 Robot_Serial
uint16 Instruct
uint16 PausePosition

")



(provide :test1/robot_dispatch "45ae8b3befd8df4adf441be85bfd7b86")


