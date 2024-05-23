// Copyright (C) <2018> Intel Corporation
//
// SPDX-License-Identifier: Apache-2.0
#ifndef OWT_BASE_VIDEODECODERINTERFACE_H_
#define OWT_BASE_VIDEODECODERINTERFACE_H_
#include <memory>
#include "owt/base/commontypes.h"
namespace owt {
namespace base {
/**
 @brief Video encoded frame definition
*/
struct OWT_EXPORT VideoEncodedFrame {
  /// Encoded frame buffer
  const uint8_t* buffer;
  /// Encoded frame buffer length
  size_t length;
  /// Frame timestamp (90kHz).
  int64_t rtp_timestamp;
  int64_t render_timestamp;
  /// Key frame flag
  bool is_key_frame;
};

struct OWT_EXPORT VideoDecodedFrame {
  const uint8_t *buffer;
  size_t length;
  int64_t rtp_timestamp;
  int64_t render_timestamp;
  bool is_key_frame;
  int width;
  int height;
};

class VideoFrameDecodedCallback {
public:
  virtual void OnVideoDecodedFrame(VideoDecodedFrame frame) = 0;

};

enum class VideoDecodedType {
  kI420,  // 暂不支持
  kARGB,  // 暂不支持
  kVP8,
  kVP9,
  kH264,
  kH265,
  kUnknown,
};

/**
 @brief Video decoder interface
 @details Encoded frames will be passed for further customized decoding
*/
class OWT_EXPORT VideoDecoderInterface {
 public:
  /**
   @brief Destructor
   */
  virtual ~VideoDecoderInterface() {}
  /**
   @brief This function initializes the customized video decoder
   @param video_codec Video codec of the encoded video stream
   @return true if successful or false if failed
   */
  virtual bool InitDecodeContext(VideoCodec video_codec) = 0;
  /**
   @brief This function releases the customized video decoder
   @return true if successful or false if failed
   */
  virtual bool Release() = 0;
  /**
   @brief This function receives the encoded frame for the further decoding
   @param frame Video encoded frame to be decoded
   @return true if successful or false if failed
   */
  virtual bool OnEncodedFrame(std::unique_ptr<VideoEncodedFrame> frame) = 0;
  /**
   @brief This function generates the customized decoder for each peer connection
   */
  virtual void RegistDecodedCallback(VideoFrameDecodedCallback *callback) = 0;
  virtual void UnRegistDecodedCallback() = 0;

  virtual VideoDecodedType Type() = 0;

  virtual VideoDecoderInterface* Copy() = 0;
};
}
}
#endif // OWT_BASE_VIDEODECODERINTERFACE_H_
