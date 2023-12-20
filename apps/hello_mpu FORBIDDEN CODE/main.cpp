#include "config.h"
#include "log.h"
#include "mpu6050.h"

#include "pico/stdlib.h"

int main() {
  i2c_inst_t *i2c = i2c0;

  stdio_init_all();

  sleep_ms(5000);

  printf("Hello, MPU6050! Reading raw data from registers...\n");

  // This example will use I2C0 on the default SDA and SCL pins (4, 5 on a Pico)
  i2c_init(i2c, 400 * 1000);
  gpio_set_function(sda_pin, GPIO_FUNC_I2C);
  gpio_set_function(scl_pin, GPIO_FUNC_I2C);
  gpio_pull_up(sda_pin);
  gpio_pull_up(scl_pin);
  // Make the I2C pins available to picotool
  // bi_decl(bi_2pins_with_func(sda_pin, scl_pin, GPIO_FUNC_I2C));

  mpu6050_reset();

  int16_t acceleration[3] = {0};
  int16_t gyro[3] = {0};
  int16_t temp = 0;

  while (1) {
    mpu6050_read_raw(acceleration, gyro, &temp);

    // These are the raw numbers from the chip, so will need tweaking to be
    // really useful. See the datasheet for more information
    printf("Acc. X = %d, Y = %d, Z = %d\n", acceleration[0], acceleration[1],
           acceleration[2]);
    printf("Gyro. X = %d, Y = %d, Z = %d\n", gyro[0], gyro[1], gyro[2]);
    // Temperature is simple so use the datasheet calculation to get deg C.
    // Note this is chip temperature.
    printf("Temp. = %f\n", (temp / 340.0) + 36.53);

    sleep_ms(1000);
  }
}
