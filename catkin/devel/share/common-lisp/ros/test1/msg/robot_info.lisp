; Auto-generated. Do not edit!


(cl:in-package test1-msg)


;//! \htmlinclude robot_info.msg.html

(cl:defclass <robot_info> (roslisp-msg-protocol:ros-message)
  ((Robot_Serial
    :reader Robot_Serial
    :initarg :Robot_Serial
    :type cl:fixnum
    :initform 0)
   (Control_State
    :reader Control_State
    :initarg :Control_State
    :type cl:fixnum
    :initform 0)
   (Robot_State
    :reader Robot_State
    :initarg :Robot_State
    :type cl:fixnum
    :initform 0)
   (Robot_Position
    :reader Robot_Position
    :initarg :Robot_Position
    :type cl:fixnum
    :initform 0)
   (Task_Type
    :reader Task_Type
    :initarg :Task_Type
    :type cl:fixnum
    :initform 0)
   (Route_Serial
    :reader Route_Serial
    :initarg :Route_Serial
    :type cl:fixnum
    :initform 0))
)

(cl:defclass robot_info (<robot_info>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <robot_info>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'robot_info)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name test1-msg:<robot_info> is deprecated: use test1-msg:robot_info instead.")))

(cl:ensure-generic-function 'Robot_Serial-val :lambda-list '(m))
(cl:defmethod Robot_Serial-val ((m <robot_info>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader test1-msg:Robot_Serial-val is deprecated.  Use test1-msg:Robot_Serial instead.")
  (Robot_Serial m))

(cl:ensure-generic-function 'Control_State-val :lambda-list '(m))
(cl:defmethod Control_State-val ((m <robot_info>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader test1-msg:Control_State-val is deprecated.  Use test1-msg:Control_State instead.")
  (Control_State m))

(cl:ensure-generic-function 'Robot_State-val :lambda-list '(m))
(cl:defmethod Robot_State-val ((m <robot_info>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader test1-msg:Robot_State-val is deprecated.  Use test1-msg:Robot_State instead.")
  (Robot_State m))

(cl:ensure-generic-function 'Robot_Position-val :lambda-list '(m))
(cl:defmethod Robot_Position-val ((m <robot_info>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader test1-msg:Robot_Position-val is deprecated.  Use test1-msg:Robot_Position instead.")
  (Robot_Position m))

(cl:ensure-generic-function 'Task_Type-val :lambda-list '(m))
(cl:defmethod Task_Type-val ((m <robot_info>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader test1-msg:Task_Type-val is deprecated.  Use test1-msg:Task_Type instead.")
  (Task_Type m))

(cl:ensure-generic-function 'Route_Serial-val :lambda-list '(m))
(cl:defmethod Route_Serial-val ((m <robot_info>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader test1-msg:Route_Serial-val is deprecated.  Use test1-msg:Route_Serial instead.")
  (Route_Serial m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <robot_info>) ostream)
  "Serializes a message object of type '<robot_info>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'Robot_Serial)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'Robot_Serial)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'Control_State)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'Control_State)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'Robot_State)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'Robot_State)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'Robot_Position)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'Robot_Position)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'Task_Type)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'Task_Type)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'Route_Serial)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'Route_Serial)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <robot_info>) istream)
  "Deserializes a message object of type '<robot_info>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'Robot_Serial)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'Robot_Serial)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'Control_State)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'Control_State)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'Robot_State)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'Robot_State)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'Robot_Position)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'Robot_Position)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'Task_Type)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'Task_Type)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'Route_Serial)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'Route_Serial)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<robot_info>)))
  "Returns string type for a message object of type '<robot_info>"
  "test1/robot_info")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'robot_info)))
  "Returns string type for a message object of type 'robot_info"
  "test1/robot_info")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<robot_info>)))
  "Returns md5sum for a message object of type '<robot_info>"
  "f7468c010c81fc0248bb003b9877aa15")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'robot_info)))
  "Returns md5sum for a message object of type 'robot_info"
  "f7468c010c81fc0248bb003b9877aa15")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<robot_info>)))
  "Returns full string definition for message of type '<robot_info>"
  (cl:format cl:nil "uint16 Robot_Serial~%uint16 Control_State~%uint16 Robot_State~%uint16 Robot_Position~%uint16 Task_Type~%uint16 Route_Serial~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'robot_info)))
  "Returns full string definition for message of type 'robot_info"
  (cl:format cl:nil "uint16 Robot_Serial~%uint16 Control_State~%uint16 Robot_State~%uint16 Robot_Position~%uint16 Task_Type~%uint16 Route_Serial~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <robot_info>))
  (cl:+ 0
     2
     2
     2
     2
     2
     2
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <robot_info>))
  "Converts a ROS message object to a list"
  (cl:list 'robot_info
    (cl:cons ':Robot_Serial (Robot_Serial msg))
    (cl:cons ':Control_State (Control_State msg))
    (cl:cons ':Robot_State (Robot_State msg))
    (cl:cons ':Robot_Position (Robot_Position msg))
    (cl:cons ':Task_Type (Task_Type msg))
    (cl:cons ':Route_Serial (Route_Serial msg))
))
