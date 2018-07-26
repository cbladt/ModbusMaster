# ModbusMaster
One Modbus Master implementation to rule them all!  

# Class Diagram
Simple diagram which should my initial thoughts.
Can be edited with https://draw.io

# Initial specification notes
* ModbusMaster must support following modbus functions codes.
  * Read Input Registers (4)
  * Read Holding Registers (3)
  * Write Single Register (6)
  * Write Multiple Registers (10)

* ModbusMaster must be designed in a way that makes it easy to add further function codes.

* ModbusMaster shall not be specifc to any hardware.
