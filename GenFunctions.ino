#undef F
#define F(s) (s)

int32_t w, h, n, n1, cx, cy, cx1, cy1, cn, cn1;
uint8_t tsa, tsb, tsc, ds;

bool screenpressed = 0;

void InitDevice(){
  Serial.begin(115200);

  // Init Display
  if (!gfx->begin())
  // if (!gfx->begin(80000000)) /* specify data bus speed */
  {
    Serial.println("gfx->begin() failed!");
  }
  
  // fill screen black
  gfx->fillScreen(RGB565_BLACK);
// JC3248W535 Module
// Arduino_GFX with Touch
// NO LVGL
// Stephen Butler - Jan 2025

// General Functions

  w = gfx->width();
  h = gfx->height();
  n = min(w, h);
  n1 = n - 1;
  cx = w / 2;
  cy = h / 2;
  cx1 = cx - 1;
  cy1 = cy - 1;
  cn = min(cx1, cy1);
  cn1 = cn - 1;

  // enable backlight
  pinMode(GFX_BL, OUTPUT);
  digitalWrite(GFX_BL, HIGH);

  pinMode(TOUCH_PIN_NUM_RST, OUTPUT);
  digitalWrite(TOUCH_PIN_NUM_RST, HIGH); delay(2);
  digitalWrite(TOUCH_PIN_NUM_RST, LOW); delay(10);
  digitalWrite(TOUCH_PIN_NUM_RST, HIGH); delay(2);

  // Init Touch Interrupt
  Wire.begin(TOUCH_PIN_NUM_I2C_SDA, TOUCH_PIN_NUM_I2C_SCL);
  pinMode(TOUCH_PIN_NUM_INT, INPUT);
  attachInterrupt(digitalPinToInterrupt(TOUCH_INT), tpress, CHANGE);
}

void printtxy(){
  // Output x/y if screen pressed
  if (screenpressed == 1){
    uint8_t buff[20] = {0};
    Wire.beginTransmission(ALS_ADDRESS);
    Wire.write(read_touchpad_cmd, 8);
    Wire.endTransmission();
    Wire.requestFrom(ALS_ADDRESS, AXS_TOUCH_TWO_POINT_LEN);
    while (!Wire.available());
    Wire.readBytes(buff, AXS_TOUCH_TWO_POINT_LEN);
    uint8_t num = AXS_GET_POINT_NUM(buff);
    uint16_t type = AXS_GET_GESTURE_TYPE(buff);
    
      if (num && !type) {
        Serial.printf("num:%d \n", num);
        for (int i = 0; i < num; ++i) {
            Serial.print("x"); Serial.print(i); Serial.print(":"); Serial.print(AXS_GET_POINT_X(buff, i));
            Serial.print("y"); Serial.print(i); Serial.print(":"); Serial.print(AXS_GET_POINT_Y(buff, i));
        }
        Serial.println();
    }
    screenpressed = 0;
 }
}

void hello(){
  gfx->fillScreen(RGB565_BLACK);
  gfx->setCursor(10, 10);
  gfx->setTextColor(RGB565_RED);
  gfx->println("Hello World!");
  gfx->flush();
}

// Touch Interrupt Function
void tpress() {
  screenpressed = 1;
}