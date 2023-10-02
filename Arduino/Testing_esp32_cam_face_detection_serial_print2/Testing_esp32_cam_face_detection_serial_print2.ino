#include "camera_frame_data.h"
#include "fd_forward.h"
#include "fr_forward.h"
#include "fr_flash.h"

mtmn_config_t mtmn_config = mtmn_init_config();

void setup()
{
  Serial.begin(115200);
  initCam();
  Serial.println("STARTED");
}

void loop()
{
  if (detectFace() == true)
  {
    Serial.println("Face Detected !!! ___________________________________");
  }
  else
  {
    Serial.println("Face Not Detected !!!");
  }
}

boolean detectFace()
{
  if (!getFrame())
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
  Serial.println("check"+String(res));
  
  if(!res)
  {
    dl_matrix3du_free(image_matrix);
    Serial.println("Conversion error");
    return false;
  }
  
  box_array_t *net_boxes = net_boxes = face_detect(image_matrix, &mtmn_config);
  if (net_boxes)
  {
    free(net_boxes);
    dl_matrix3du_free(image_matrix);
    return true;
  }
  else
  {
    free(net_boxes);
    dl_matrix3du_free(image_matrix);
    return false;
  }
}
