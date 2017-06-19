; Auto-generated. Do not edit!


(cl:in-package test1-msg)


;//! \htmlinclude client_info.msg.html

(cl:defclass <client_info> (roslisp-msg-protocol:ros-message)
  ((client_serial
    :reader client_serial
    :initarg :client_serial
    :type cl:integer
    :initform 0))
)

(cl:defclass client_info (<client_info>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <client_info>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'client_info)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name test1-msg:<client_info> is deprecated: use test1-msg:client_info instead.")))

(cl:ensure-generic-function 'client_serial-val :lambda-list '(m))
(cl:defmethod client_serial-val ((m <client_info>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader test1-msg:client_serial-val is deprecated.  Use test1-msg:client_serial instead.")
  (client_serial m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <client_info>) ostream)
  "Serializes a message object of type '<client_info>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'client_serial)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'client_serial)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'client_serial)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'client_serial)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <client_info>) istream)
  "Deserializes a message object of type '<client_info>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'client_serial)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'client_serial)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'client_serial)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'client_serial)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<client_info>)))
  "Returns string type for a message object of type '<client_info>"
  "test1/client_info")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'client_info)))
  "Returns string type for a message object of type 'client_info"
  "test1/client_info")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<client_info>)))
  "Returns md5sum for a message object of type '<client_info>"
  "67bbc1d16de51fe473a2b7db355db7a0")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'client_info)))
  "Returns md5sum for a message object of type 'client_info"
  "67bbc1d16de51fe473a2b7db355db7a0")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<client_info>)))
  "Returns full string definition for message of type '<client_info>"
  (cl:format cl:nil "uint32 client_serial~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'client_info)))
  "Returns full string definition for message of type 'client_info"
  (cl:format cl:nil "uint32 client_serial~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <client_info>))
  (cl:+ 0
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <client_info>))
  "Converts a ROS message object to a list"
  (cl:list 'client_info
    (cl:cons ':client_serial (client_serial msg))
))
