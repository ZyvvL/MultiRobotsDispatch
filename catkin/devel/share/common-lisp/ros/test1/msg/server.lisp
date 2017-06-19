; Auto-generated. Do not edit!


(cl:in-package test1-msg)


;//! \htmlinclude server.msg.html

(cl:defclass <server> (roslisp-msg-protocol:ros-message)
  ((IsStart
    :reader IsStart
    :initarg :IsStart
    :type cl:fixnum
    :initform 0))
)

(cl:defclass server (<server>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <server>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'server)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name test1-msg:<server> is deprecated: use test1-msg:server instead.")))

(cl:ensure-generic-function 'IsStart-val :lambda-list '(m))
(cl:defmethod IsStart-val ((m <server>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader test1-msg:IsStart-val is deprecated.  Use test1-msg:IsStart instead.")
  (IsStart m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <server>) ostream)
  "Serializes a message object of type '<server>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'IsStart)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <server>) istream)
  "Deserializes a message object of type '<server>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'IsStart)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<server>)))
  "Returns string type for a message object of type '<server>"
  "test1/server")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'server)))
  "Returns string type for a message object of type 'server"
  "test1/server")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<server>)))
  "Returns md5sum for a message object of type '<server>"
  "f943cc528f6d0372715159c657f91c2e")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'server)))
  "Returns md5sum for a message object of type 'server"
  "f943cc528f6d0372715159c657f91c2e")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<server>)))
  "Returns full string definition for message of type '<server>"
  (cl:format cl:nil "uint8 IsStart~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'server)))
  "Returns full string definition for message of type 'server"
  (cl:format cl:nil "uint8 IsStart~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <server>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <server>))
  "Converts a ROS message object to a list"
  (cl:list 'server
    (cl:cons ':IsStart (IsStart msg))
))
