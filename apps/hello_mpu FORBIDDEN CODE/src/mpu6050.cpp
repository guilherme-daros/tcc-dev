#include "mpu6050.h"

// By default these devices  are on bus address 0x68
int addr = 0x68;
i2c_inst_t *i2c = i2c0;
const uint sda_pin = 31;
const uint scl_pin = 32;

void mpu6050_reset() {
  // Two byte reset. First byte register, second byte data
  // There are a load more options to set up the device in different ways that
  // could be added here
  uint8_t buf[] = {0x6B, 0x80};
  i2c_write_blocking(i2c, addr, buf, 2, false);
}

void mpu6050_read_raw(int16_t accel[3], int16_t gyro[3], int16_t *temp) {
  uint8_t buffer[6];

  // Start reading acceleration registers from register 0x3B for 6 bytes
  uint8_t val = 0x3B;
  i2c_write_blocking(i2c, addr, &val, 1,
                     true); // true to keep master control of bus
  i2c_read_blocking(i2c, addr, buffer, 6, false);

  for (int i = 0; i < 3; i++) {
    accel[i] = (buffer[i * 2] << 8 | buffer[(i * 2) + 1]);
  }

  // Now gyro data from reg 0x43 for 6 bytes
  // The register is auto incrementing on each read
  val = 0x43;
  i2c_write_blocking(i2c, addr, &val, 1, true);
  i2c_read_blocking(i2c, addr, buffer, 6,
                    false); // False - finished with bus

  for (int i = 0; i < 3; i++) {
    gyro[i] = (buffer[i * 2] << 8 | buffer[(i * 2) + 1]);
    ;
  }

  // Now temperature from reg 0x41 for 2 bytes
  // The register is auto incrementing on each read
  val = 0x41;
  i2c_write_blocking(i2c, addr, &val, 1, true);
  i2c_read_blocking(i2c, addr, buffer, 2,
                    false); // False - finished with bus

  *temp = buffer[0] << 8 | buffer[1];
}