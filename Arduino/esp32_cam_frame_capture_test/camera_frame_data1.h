//#include "camera_pins.h"
#include <esp_camera.h>


#define PWDN_GPIO_NUM     32
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM      0
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27

#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM        5
#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM     23
#define PCLK_GPIO_NUM     22

void initCam1();
int getFrame1();

void initCameracam_configuration1();

camera_config_t cam_conf1;
boolean cam_start_flg1=false;
camera_fb_t *framecam1;
uint8_t frame_flg1='E';

void initCam1()
{
  initCameracam_configuration1();
  if(esp_camera_init(&cam_conf1)==ESP_OK)
  {
    sensor_t *sensor_conf = esp_camera_sensor_get();
    //sensor_conf->set_hmirror(sensor_conf,1);
    cam_start_flg1=true;
    Serial.println("INIT");
  }
  else
  {
    cam_start_flg1=false;
    Serial.println("NOT INIT");
  }
}

int getFrame1()
{
  frame_flg1='E';
  if(cam_start_flg1)
  {
    framecam1=NULL;
    framecam1=esp_camera_fb_get();
    if(framecam1)
    {
      frame_flg1='F';
    }
  }
  return (frame_flg1=='F')?1:0;
}

void initCameracam_configuration1()
{
  cam_conf1.pin_pwdn = PWDN_GPIO_NUM;
  cam_conf1.pin_reset = RESET_GPIO_NUM;
  cam_conf1.pin_xclk = XCLK_GPIO_NUM;
  cam_conf1.pin_sscb_sda = SIOD_GPIO_NUM;
  cam_conf1.pin_sscb_scl = SIOC_GPIO_NUM;
  
  cam_conf1.pin_d7 = Y9_GPIO_NUM;
  cam_conf1.pin_d6 = Y8_GPIO_NUM;
  cam_conf1.pin_d6 = Y8_GPIO_NUM;
  cam_conf1.pin_d5 = Y7_GPIO_NUM;
  cam_conf1.pin_d4 = Y6_GPIO_NUM;
  cam_conf1.pin_d3 = Y5_GPIO_NUM;
  cam_conf1.pin_d2 = Y4_GPIO_NUM;
  cam_conf1.pin_d1 = Y3_GPIO_NUM;
  cam_conf1.pin_d0 = Y2_GPIO_NUM;
  cam_conf1.pin_vsync = VSYNC_GPIO_NUM;
  cam_conf1.pin_href = HREF_GPIO_NUM;
  cam_conf1.pin_pclk = PCLK_GPIO_NUM;
  
  cam_conf1.ledc_channel = LEDC_CHANNEL_0;
  cam_conf1.ledc_timer = LEDC_TIMER_0;
  cam_conf1.xclk_freq_hz = 12000000;
  cam_conf1.pixel_format = PIXFORMAT_JPEG;

  cam_conf1.frame_size = FRAMESIZE_QQVGA;
  cam_conf1.jpeg_quality = 10;
  cam_conf1.fb_count = 1;

  cam_conf1.fb_location=CAMERA_FB_IN_DRAM;
}
