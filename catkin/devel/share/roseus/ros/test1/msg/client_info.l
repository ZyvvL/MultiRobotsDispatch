;; Auto-generated. Do not edit!


(when (boundp 'test1::client_info)
  (if (not (find-package "TEST1"))
    (make-package "TEST1"))
  (shadow 'client_info (find-package "TEST1")))
(unless (find-package "TEST1::CLIENT_INFO")
  (make-package "TEST1::CLIENT_INFO"))

(in-package "ROS")
;;//! \htmlinclude client_info.msg.html


(defclass test1::client_info
  :super ros::object
  :slots (_client_serial ))

(defmethod test1::client_info
  (:init
   (&key
    ((:client_serial __client_serial) 0)
    )
   (send-super :init)
   (setq _client_serial (round __client_serial))
   self)
  (:client_serial
   (&optional __client_serial)
   (if __client_serial (setq _client_serial __client_serial)) _client_serial)
  (:serialization-length
   ()
   (+
    ;; uint32 _client_serial
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint32 _client_serial
       (write-long _client_serial s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint32 _client_serial
     (setq _client_serial (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get test1::client_info :md5sum-) "67bbc1d16de51fe473a2b7db355db7a0")
(setf (get test1::client_info :datatype-) "test1/client_info")
(setf (get test1::client_info :definition-)
      "uint32 client_serial

")



(provide :test1/client_info "67bbc1d16de51fe473a2b7db355db7a0")


