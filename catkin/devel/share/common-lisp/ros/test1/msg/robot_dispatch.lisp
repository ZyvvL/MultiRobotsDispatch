; Auto-generated. Do not edit!


(cl:in-package test1-msg)


;//! \htmlinclude robot_dispatch.msg.html

(cl:defclass <robot_dispatch> (roslisp-msg-protocol:ros-message)
  ((Robot_Serial
    :reader Robot_Serial
    :initarg :Robot_Serial
    :type cl:fixnum
    :initform 0)
   (Instruct
    :reader Instruct
    :initarg :Instruct
    :type cl:fixnum
    :initform 0)
   (PausePosition
    :reader PausePosition
    :initarg :PausePosition
    :type cl:fixnum
    :initform 0))
)

(cl:defclass robot_dispatch (<robot_dispatch>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <robot_dispatch>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'robot_dispatch)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name test1-msg:<robot_dispatch> is deprecated: use test1-msg:robot_dispatch instead.")))

(cl:ensure-generic-function 'Robot_Serial-val :lambda-list '(m))
(cl:defmethod Robot_Serial-val ((m <robot_dispatch>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader test1-msg:Robot_Serial-val is deprecated.  Use test1-msg:Robot_Serial instead.")
  (Robot_Serial m))

(cl:ensure-generic-function 'Instruct-val :lambda-list '(m))
(cl:defmethod Instruct-val ((m <robot_dispatch>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader test1-msg:Instruct-val is deprecated.  Use test1-msg:Instruct instead.")
  (Instruct m))

(cl:ensure-generic-function 'PausePosition-val :lambda-list '(m))
(cl:defmethod PausePosition-val ((m <robot_dispatch>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader test1-msg:PausePosition-val is deprecated.  Use test1-msg:PausePosition instead.")
  (PausePosition m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <robot_dispatch>) ostream)
  "Serializes a message object of type '<robot_dispatch>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'Robot_Serial)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'Robot_Serial)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'Instruct)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'Instruct)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'PausePosition)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'PausePosition)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <robot_dispatch>) istream)
  "Deserializes a message object of type '<robot_dispatch>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'Robot_Serial)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'Robot_Serial)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'Instruct)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'Instruct)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'PausePosition)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'PausePosition)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<robot_dispatch>)))
  "Returns string type for a message object of type '<robot_dispatch>"
  "test1/robot_dispatch")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'robot_dispatch)))
  "Returns string type for a message object of type 'robot_dispatch"
  "test1/robot_dispatch")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<robot_dispatch>)))
  "Returns md5sum for a message object of type '<robot_dispatch>"
  "45ae8b3befd8df4adf441be85bfd7b86")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'robot_dispatch)))
  "Returns md5sum for a message object of type 'robot_dispatch"
  "45ae8b3befd8df4adf441be85bfd7b86")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<robot_dispatch>)))
  "Returns full string definition for message of type '<robot_dispatch>"
  (cl:format cl:nil "uint16 Robot_Serial~%uint16 Instruct~%uint16 PausePosition~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'robot_dispatch)))
  "Returns full string definition for message of type 'robot_dispatch"
  (cl:format cl:nil "uint16 Robot_Serial~%uint16 Instruct~%uint16 PausePosition~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <robot_dispatch>))
  (cl:+ 0
     2
     2
     2
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <robot_dispatch>))
  "Converts a ROS message object to a list"
  (cl:list 'robot_dispatch
    (cl:cons ':Robot_Serial (Robot_Serial msg))
    (cl:cons ':Instruct (Instruct msg))
    (cl:cons ':PausePosition (PausePosition msg))
))
