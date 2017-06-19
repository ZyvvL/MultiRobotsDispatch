;; Auto-generated. Do not edit!


(when (boundp 'test2::robot_dispatch)
  (if (not (find-package "TEST2"))
    (make-package "TEST2"))
  (shadow 'robot_dispatch (find-package "TEST2")))
(unless (find-package "TEST2::ROBOT_DISPATCH")
  (make-package "TEST2::ROBOT_DISPATCH"))

(in-package "ROS")
;;//! \htmlinclude robot_dispatch.msg.html


(defclass test2::robot_dispatch
  :super ros::object
  :slots (_Instruct _PausePosition ))

(defmethod test2::robot_dispatch
  (:init
   (&key
    ((:Instruct __Instruct) 0)
    ((:PausePosition __PausePosition) 0)
    )
   (send-super :init)
   (setq _Instruct (round __Instruct))
   (setq _PausePosition (round __PausePosition))
   self)
  (:Instruct
   (&optional __Instruct)
   (if __Instruct (setq _Instruct __Instruct)) _Instruct)
  (:PausePosition
   (&optional __PausePosition)
   (if __PausePosition (setq _PausePosition __PausePosition)) _PausePosition)
  (:serialization-length
   ()
   (+
    ;; uint16 _Instruct
    2
    ;; uint16 _PausePosition
    2
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint16 _Instruct
       (write-word _Instruct s)
     ;; uint16 _PausePosition
       (write-word _PausePosition s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint16 _Instruct
     (setq _Instruct (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; uint16 _PausePosition
     (setq _PausePosition (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;;
   self)
  )

(setf (get test2::robot_dispatch :md5sum-) "c35d7c7ecbf7a8c67d04da8680b52741")
(setf (get test2::robot_dispatch :datatype-) "test2/robot_dispatch")
(setf (get test2::robot_dispatch :definition-)
      "uint16 Instruct
uint16 PausePosition

")



(provide :test2/robot_dispatch "c35d7c7ecbf7a8c67d04da8680b52741")


