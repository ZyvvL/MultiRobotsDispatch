;; Auto-generated. Do not edit!


(when (boundp 'test1::server)
  (if (not (find-package "TEST1"))
    (make-package "TEST1"))
  (shadow 'server (find-package "TEST1")))
(unless (find-package "TEST1::SERVER")
  (make-package "TEST1::SERVER"))

(in-package "ROS")
;;//! \htmlinclude server.msg.html


(defclass test1::server
  :super ros::object
  :slots (_IsStart ))

(defmethod test1::server
  (:init
   (&key
    ((:IsStart __IsStart) 0)
    )
   (send-super :init)
   (setq _IsStart (round __IsStart))
   self)
  (:IsStart
   (&optional __IsStart)
   (if __IsStart (setq _IsStart __IsStart)) _IsStart)
  (:serialization-length
   ()
   (+
    ;; uint8 _IsStart
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint8 _IsStart
       (write-byte _IsStart s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint8 _IsStart
     (setq _IsStart (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;;
   self)
  )

(setf (get test1::server :md5sum-) "f943cc528f6d0372715159c657f91c2e")
(setf (get test1::server :datatype-) "test1/server")
(setf (get test1::server :definition-)
      "uint8 IsStart

")



(provide :test1/server "f943cc528f6d0372715159c657f91c2e")


