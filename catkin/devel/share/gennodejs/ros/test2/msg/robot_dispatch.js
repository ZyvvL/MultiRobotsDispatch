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

class robot_dispatch {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.Instruct = null;
      this.PausePosition = null;
    }
    else {
      if (initObj.hasOwnProperty('Instruct')) {
        this.Instruct = initObj.Instruct
      }
      else {
        this.Instruct = 0;
      }
      if (initObj.hasOwnProperty('PausePosition')) {
        this.PausePosition = initObj.PausePosition
      }
      else {
        this.PausePosition = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type robot_dispatch
    // Serialize message field [Instruct]
    bufferOffset = _serializer.uint16(obj.Instruct, buffer, bufferOffset);
    // Serialize message field [PausePosition]
    bufferOffset = _serializer.uint16(obj.PausePosition, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type robot_dispatch
    let len;
    let data = new robot_dispatch(null);
    // Deserialize message field [Instruct]
    data.Instruct = _deserializer.uint16(buffer, bufferOffset);
    // Deserialize message field [PausePosition]
    data.PausePosition = _deserializer.uint16(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 4;
  }

  static datatype() {
    // Returns string type for a message object
    return 'test2/robot_dispatch';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'c35d7c7ecbf7a8c67d04da8680b52741';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    uint16 Instruct
    uint16 PausePosition
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new robot_dispatch(null);
    if (msg.Instruct !== undefined) {
      resolved.Instruct = msg.Instruct;
    }
    else {
      resolved.Instruct = 0
    }

    if (msg.PausePosition !== undefined) {
      resolved.PausePosition = msg.PausePosition;
    }
    else {
      resolved.PausePosition = 0
    }

    return resolved;
    }
};

module.exports = robot_dispatch;
