// This file implements vertical rotation animation.

void ShiftVertical(const int leds_per_strip,
                   const int* colors,
                   const int colors_len,
                   const double color_shift) {
  // Set color for the vertical strips.
  for (int led_strip = 0; led_strip < kVerticalStripCount; led_strip++) {
    // Upper segment.
    const double proj_factor_upper =
      kUpperHeightRatio * colors_len / kUpperVerticalStripLen;
    const double color_shift_upper = color_shift;
    const int led_offset_upper = led_strip * leds_per_strip; 
    for (int led_index = 0; led_index < kUpperVerticalStripLen; led_index++) {
      const int color_index =
        (int) (color_shift_upper + led_index * proj_factor_upper) % colors_len;
      leds.setPixel(led_index + led_offset_upper, colors[color_index]);
    }
    // Lower segment.
    const double proj_factor_lower =
      (1 - kUpperHeightRatio) * colors_len / kLowerVerticalStripLen;
    const double color_shift_lower =
      kUpperHeightRatio * colors_len + color_shift;
    const int led_offset_lower =
      kUpperVerticalStripLen + led_strip * leds_per_strip;
    for (int led_index = 0; led_index < kLowerVerticalStripLen; led_index++) {
      const int color_index =
        (int) (color_shift_lower + led_index * proj_factor_lower) % colors_len;
      leds.setPixel(led_index + led_offset_lower, colors[color_index]);
    }
  }
  // Set color for the mid strip.
  for (int led_index = 0; led_index < kMidStripLen; led_index++) {
    const int color_index =
      (int) (color_shift + kUpperHeightRatio * colors_len) % colors_len;
    leds.setPixel(led_index + kMidStripIndex * leds_per_strip, colors[color_index]);
  }
  // Set color for the top strip.
  for (int led_index = 0; led_index < leds_per_strip; led_index++) {
    const int color_index =
      (int) (color_shift) % colors_len;
    leds.setPixel(led_index + kTopStripIndex * leds_per_strip, Colors[color_index]);
  }
}

void RotateVertical(const double rotate_freq,
                    const double refresh_freq,
                    const int leds_per_strip,
                    const int* colors,
                    const int colors_len) {
  const double color_delta =
    colors_len * rotate_freq / refresh_freq * 2;
  // Move up;
  for (double color_shift = 0; color_shift < colors_len;
       color_shift += color_delta) {
    ShiftVertical(leds_per_strip, colors, colors_len, color_shift);
    leds.show();
    delayMicroseconds(1000000 / refresh_freq);
  }
  // Move down;
  for (double color_shift = colors_len; color_shift > 0;
       color_shift -= color_delta) {
    ShiftVertical(leds_per_strip, colors, colors_len, color_shift);
    leds.show();
    delayMicroseconds(1000000 / refresh_freq);
  }
}
