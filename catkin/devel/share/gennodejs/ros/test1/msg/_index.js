
"use strict";

let server = require('./server.js');
let hello = require('./hello.js');
let client_info = require('./client_info.js');
let robot_dispatch = require('./robot_dispatch.js');
let robot_info = require('./robot_info.js');

module.exports = {
  server: server,
  hello: hello,
  client_info: client_info,
  robot_dispatch: robot_dispatch,
  robot_info: robot_info,
};
