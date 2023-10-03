/* Copyright 2019 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#include "output_handler.h"

#include "pico/stdlib.h"
#include "pico/time.h"

#include "constants.h"

namespace {

int g_led_brightness = 0;

// For details on what this code is doing, see
// https://github.com/raspberrypi/pico-examples/blob/master/pwm/led_fade

} // namespace

void HandleOutput(tflite::ErrorReporter *error_reporter, float x_value,
                  float y_value) {
  // Do this only once
  static bool is_initialized = false;
  if (!is_initialized) {
    is_initialized = true;
  }

  // Calculate the brightness of the LED such that y=-1 is fully off
  // and y=1 is fully on. The LED's brightness can range from 0-255.
  g_led_brightness = (int)(127.5f * (y_value + 1));

  // Log the current brightness value for display in the console.
  TF_LITE_REPORT_ERROR(error_reporter, "%d\n", g_led_brightness);

  // By default the sine wave is too fast to see in the LED, so slow
  // down the whole program deliberately so it's more visible.
  sleep_ms(10);
}