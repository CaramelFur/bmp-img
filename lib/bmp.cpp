#include <node.h>
#include <node_api.h>

#include "bmpxx.hpp"

namespace bmp_node
{
  // First argument is a Buffer
  // Second argument is width
  // Third argument is height
  // Fourth argument is channels
  napi_value Encode(napi_env env, napi_callback_info args)
  {
    uint32_t status;

    napi_value argv[4];
    size_t argc = 4;
    status = napi_get_cb_info(env, args, &argc, argv, nullptr, nullptr);

    if (status != napi_ok || argc != 4)
    {
      napi_throw_error(env, nullptr, "Invalid argument count");
      return nullptr;
    }

    uint8_t *pixels_arr;
    size_t pixels_length;
    uint32_t width = 0;
    uint32_t height = 0;
    uint32_t channels = 0;

    status = napi_get_buffer_info(env, argv[0], (void **)&pixels_arr, &pixels_length);
    status += napi_get_value_uint32(env, argv[1], &width);
    status += napi_get_value_uint32(env, argv[2], &height);
    status += napi_get_value_uint32(env, argv[3], &channels);

    if (status != napi_ok)
    {
      napi_throw_error(env, nullptr, "Invalid argument type");
      return nullptr;
    }

    const auto options = bmpxx::BmpDesc(width, height, channels);

    std::vector<uint8_t> pixels(pixels_arr, pixels_arr + pixels_length);

    std::vector<uint8_t> image;
    try
    {
      image = bmpxx::bmp::encode(pixels, options);
    }
    catch (const std::exception &e)
    {
      napi_throw_error(env, nullptr, e.what());
      return nullptr;
    }

    napi_value result;
    status = napi_create_buffer_copy(env, image.size(), image.data(), nullptr, &result);

    if (status != napi_ok)
    {
      napi_throw_error(env, nullptr, "Failed to create buffer");
      return nullptr;
    }

    return result;
  }

  // First argument is a Buffer
  napi_value Decode(napi_env env, napi_callback_info args)
  {
    uint32_t status;

    napi_value argv[1];
    size_t argc = 1;
    status = napi_get_cb_info(env, args, &argc, argv, nullptr, nullptr);

    if (status != napi_ok || argc != 1)
    {
      napi_throw_error(env, nullptr, "Invalid argument count");
      return nullptr;
    }

    uint8_t *image_arr;
    size_t image_length;

    status = napi_get_buffer_info(env, argv[0], (void **)&image_arr, &image_length);

    if (status != napi_ok)
    {
      napi_throw_error(env, nullptr, "Invalid argument type");
      return nullptr;
    }

    std::vector<uint8_t> image(image_arr, image_arr + image_length);

    std::pair<std::vector<uint8_t>, bmpxx::BmpDesc> decoded_image;
    try
    {
      decoded_image = bmpxx::bmp::decode(image);
    }
    catch (const std::exception &e)
    {
      napi_throw_error(env, nullptr, e.what());
      return nullptr;
    }

    napi_value result_pixels;
    napi_value result_width;
    napi_value result_height;
    napi_value result_channels;

    status = napi_create_buffer_copy(env, decoded_image.first.size(), decoded_image.first.data(), nullptr, &result_pixels);
    status += napi_create_uint32(env, decoded_image.second.width, &result_width);
    status += napi_create_uint32(env, decoded_image.second.height, &result_height);
    status += napi_create_uint32(env, (uint32_t)decoded_image.second.channels, &result_channels);

    if (status != napi_ok)
    {
      napi_throw_error(env, nullptr, "Failed to create result");
      return nullptr;
    }

    napi_value result_desc;
    status = napi_create_object(env, &result_desc);
    status += napi_set_named_property(env, result_desc, "pixels", result_pixels);
    status += napi_set_named_property(env, result_desc, "width", result_width);
    status += napi_set_named_property(env, result_desc, "height", result_height);
    status += napi_set_named_property(env, result_desc, "channels", result_channels);

    if (status != napi_ok)
    {
      napi_throw_error(env, nullptr, "Failed to create result");
      return nullptr;
    }

    return result_desc;
  }

  napi_value init(napi_env env, napi_value exports)
  {
    napi_status status;
    napi_value encode;
    napi_value decode;

    status = napi_create_function(env, nullptr, 0, Encode, nullptr, &encode);
    if (status != napi_ok)
      return nullptr;

    status = napi_set_named_property(env, exports, "encode", encode);
    if (status != napi_ok)
      return nullptr;

    status = napi_create_function(env, nullptr, 0, Decode, nullptr, &decode);
    if (status != napi_ok)
      return nullptr;

    status = napi_set_named_property(env, exports, "decode", decode);
    if (status != napi_ok)
      return nullptr;

    return exports;
  }

  NAPI_MODULE(NODE_GYP_MODULE_NAME, init)
}
