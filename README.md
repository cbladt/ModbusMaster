# ModbusMaster
One Modbus Master implementation to rule them all!  

# Initial specification
* ModbusMaster must support following modbus functions codes.
  * Read Input Registers (4)
  * Read Holding Registers (3)
  * Write Single Register (6)
  * Write Multiple Registers (10)

* ModbusMaster must be designed in a way that makes it easy to add further function codes.

* ModbusMaster shall not be specifc to any hardware.

* ModbusMaster shall not use dynamic memory, as it is not available on all targeted platforms.
