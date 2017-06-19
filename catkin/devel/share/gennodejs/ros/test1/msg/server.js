// Auto-generated. Do not edit!

// (in-package test1.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class server {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.IsStart = null;
    }
    else {
      if (initObj.hasOwnProperty('IsStart')) {
        this.IsStart = initObj.IsStart
      }
      else {
        this.IsStart = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type server
    // Serialize message field [IsStart]
    bufferOffset = _serializer.uint8(obj.IsStart, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type server
    let len;
    let data = new server(null);
    // Deserialize message field [IsStart]
    data.IsStart = _deserializer.uint8(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 1;
  }

  static datatype() {
    // Returns string type for a message object
    return 'test1/server';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'f943cc528f6d0372715159c657f91c2e';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    uint8 IsStart
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new server(null);
    if (msg.IsStart !== undefined) {
      resolved.IsStart = msg.IsStart;
    }
    else {
      resolved.IsStart = 0
    }

    return resolved;
    }
};

module.exports = server;
