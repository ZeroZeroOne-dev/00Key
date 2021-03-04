#include "usb_names.h"

#define PRODUCT_NAME		{'0','0','K','e','y'}
#define PRODUCT_NAME_LEN	5

struct usb_string_descriptor_struct usb_string_product_name = {
  2 + PRODUCT_NAME_LEN * 2,
  3,
  PRODUCT_NAME
};