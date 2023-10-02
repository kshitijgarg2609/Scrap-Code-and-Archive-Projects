#include "camera_frame_data.h"
#include "fd_forward.h"
#include "fr_forward.h"
#include "fr_flash.h"

static inline mtmn_config_t app_mtmn_config()
{
  mtmn_config_t mtmn_config = {0};
  mtmn_config.type = FAST;
  mtmn_config.min_face = 80;
  mtmn_config.pyramid = 0.707;
  mtmn_config.pyramid_times = 4;
  mtmn_config.p_threshold.score = 0.6;
  mtmn_config.p_threshold.nms = 0.7;
  mtmn_config.p_threshold.candidate_number = 20;
  mtmn_config.r_threshold.score = 0.7;
  mtmn_config.r_threshold.nms = 0.7;
  mtmn_config.r_threshold.candidate_number = 10;
  mtmn_config.o_threshold.score = 0.7;
  mtmn_config.o_threshold.nms = 0.7;
  mtmn_config.o_threshold.candidate_number = 1;
  return mtmn_config;
}
mtmn_config_t mtmn_config = app_mtmn_config();
//dl_matrix3du_t *aligned_face = dl_matrix3du_alloc(1, FACE_WIDTH, FACE_HEIGHT, 3);


void setup()
{
  Serial.begin(115200);
  initCam();
  Serial.println("STARTED");
}

void loop()
{
    if(detectFace()==true)
    {
      Serial.println("Face Detected !!!");
    }
    else
    {
      Serial.println("Face Not Detected !!!");
    }
}

boolean detectFace()
{
  if(!getFrame())
  {
    Serial.println("Frame Error !!!");
    return false;
  }
  else
  {
    Serial.println("Frame Captured !!!");
  }
  dl_matrix3du_t *image_matrix = dl_matrix3du_alloc(1, frame->width, frame->height, 3);
  
  uint32_t res = fmt2rgb888(frame->buf, frame->len, frame->format, image_matrix->item);
  if (!res)
  {
    dl_matrix3du_free(image_matrix);
    return false;
  }
  
  box_array_t *net_boxes = face_detect(image_matrix, &mtmn_config);
  if (net_boxes)
  {
   //if (align_face(net_boxes, image_matrix, aligned_face) == ESP_OK)
   //{
    
   //}
   free(net_boxes->box);
   free(net_boxes->landmark);
   free(net_boxes);
   dl_matrix3du_free(image_matrix);
   return true;
  }
  else
  {
    dl_matrix3du_free(image_matrix);
    return false;
  }
}
