// Auto-generated. Do not edit!

// (in-package test2.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class robot_info {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.Control_State = null;
      this.Robot_State = null;
      this.Robot_Position = null;
      this.Task_Type = null;
      this.Route_Serial = null;
    }
    else {
      if (initObj.hasOwnProperty('Control_State')) {
        this.Control_State = initObj.Control_State
      }
      else {
        this.Control_State = 0;
      }
      if (initObj.hasOwnProperty('Robot_State')) {
        this.Robot_State = initObj.Robot_State
      }
      else {
        this.Robot_State = 0;
      }
      if (initObj.hasOwnProperty('Robot_Position')) {
        this.Robot_Position = initObj.Robot_Position
      }
      else {
        this.Robot_Position = 0;
      }
      if (initObj.hasOwnProperty('Task_Type')) {
        this.Task_Type = initObj.Task_Type
      }
      else {
        this.Task_Type = 0;
      }
      if (initObj.hasOwnProperty('Route_Serial')) {
        this.Route_Serial = initObj.Route_Serial
      }
      else {
        this.Route_Serial = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type robot_info
    // Serialize message field [Control_State]
    bufferOffset = _serializer.uint16(obj.Control_State, buffer, bufferOffset);
    // Serialize message field [Robot_State]
    bufferOffset = _serializer.uint16(obj.Robot_State, buffer, bufferOffset);
    // Serialize message field [Robot_Position]
    bufferOffset = _serializer.uint16(obj.Robot_Position, buffer, bufferOffset);
    // Serialize message field [Task_Type]
    bufferOffset = _serializer.uint16(obj.Task_Type, buffer, bufferOffset);
    // Serialize message field [Route_Serial]
    bufferOffset = _serializer.uint16(obj.Route_Serial, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type robot_info
    let len;
    let data = new robot_info(null);
    // Deserialize message field [Control_State]
    data.Control_State = _deserializer.uint16(buffer, bufferOffset);
    // Deserialize message field [Robot_State]
    data.Robot_State = _deserializer.uint16(buffer, bufferOffset);
    // Deserialize message field [Robot_Position]
    data.Robot_Position = _deserializer.uint16(buffer, bufferOffset);
    // Deserialize message field [Task_Type]
    data.Task_Type = _deserializer.uint16(buffer, bufferOffset);
    // Deserialize message field [Route_Serial]
    data.Route_Serial = _deserializer.uint16(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 10;
  }

  static datatype() {
    // Returns string type for a message object
    return 'test2/robot_info';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'ec4a3f57734c2b806790604232e483b2';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    uint16 Control_State
    uint16 Robot_State
    uint16 Robot_Position
    uint16 Task_Type
    uint16 Route_Serial
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new robot_info(null);
    if (msg.Control_State !== undefined) {
      resolved.Control_State = msg.Control_State;
    }
    else {
      resolved.Control_State = 0
    }

    if (msg.Robot_State !== undefined) {
      resolved.Robot_State = msg.Robot_State;
    }
    else {
      resolved.Robot_State = 0
    }

    if (msg.Robot_Position !== undefined) {
      resolved.Robot_Position = msg.Robot_Position;
    }
    else {
      resolved.Robot_Position = 0
    }

    if (msg.Task_Type !== undefined) {
      resolved.Task_Type = msg.Task_Type;
    }
    else {
      resolved.Task_Type = 0
    }

    if (msg.Route_Serial !== undefined) {
      resolved.Route_Serial = msg.Route_Serial;
    }
    else {
      resolved.Route_Serial = 0
    }

    return resolved;
    }
};

module.exports = robot_info;
