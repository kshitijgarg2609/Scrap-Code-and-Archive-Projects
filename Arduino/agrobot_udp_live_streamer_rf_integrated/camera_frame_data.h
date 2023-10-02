#include <esp_camera.h>
#define CAMERA_MODEL_AI_THINKER
#include "camera_pins.h"

void initCam();
int getFrame();

void initCameracam_confuration();

static camera_config_t cam_conf;
boolean cam_start=false;
camera_fb_t *frame;
uint8_t frame_flg='E';

void initCam()
{
  initCameracam_confuration();
  if(esp_camera_init(&cam_conf)==ESP_OK)
  {
    sensor_t *sensor_conf = esp_camera_sensor_get();
    //sensor_conf->set_hmirror(sensor_conf,1);
    cam_start=true;
  }
  else
  {
    cam_start=false;
  }
}

int getFrame()
{
  frame_flg='E';
  if(cam_start)
  {
    frame=esp_camera_fb_get();
    if(frame)
    {
      frame_flg='F';
    }
  }
  return (frame_flg=='F')?1:0;
}

void initCameracam_confuration()
{
  cam_conf.pin_pwdn = PWDN_GPIO_NUM;
  cam_conf.pin_reset = RESET_GPIO_NUM;
  cam_conf.pin_xclk = XCLK_GPIO_NUM;
  cam_conf.pin_sscb_sda = SIOD_GPIO_NUM;
  cam_conf.pin_sscb_scl = SIOC_GPIO_NUM;
  
  cam_conf.pin_d7 = Y9_GPIO_NUM;
  cam_conf.pin_d6 = Y8_GPIO_NUM;
  cam_conf.pin_d6 = Y8_GPIO_NUM;
  cam_conf.pin_d5 = Y7_GPIO_NUM;
  cam_conf.pin_d4 = Y6_GPIO_NUM;
  cam_conf.pin_d3 = Y5_GPIO_NUM;
  cam_conf.pin_d2 = Y4_GPIO_NUM;
  cam_conf.pin_d1 = Y3_GPIO_NUM;
  cam_conf.pin_d0 = Y2_GPIO_NUM;
  cam_conf.pin_vsync = VSYNC_GPIO_NUM;
  cam_conf.pin_href = HREF_GPIO_NUM;
  cam_conf.pin_pclk = PCLK_GPIO_NUM;
  
  cam_conf.ledc_channel = LEDC_CHANNEL_0;
  cam_conf.ledc_timer = LEDC_TIMER_0;
  cam_conf.xclk_freq_hz = 20000000;
  cam_conf.pixel_format = PIXFORMAT_JPEG;

  cam_conf.frame_size = FRAMESIZE_QVGA;
  cam_conf.jpeg_quality = 10;
  cam_conf.fb_count = 1;
}
