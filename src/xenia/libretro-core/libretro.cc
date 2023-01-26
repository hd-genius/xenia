#include <math.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdio.h>
#if defined(_WIN32) && !defined(_XBOX)
#include <windows.h>
#endif
#include "libretro.h"

#define VIDEO_WIDTH 256
#define VIDEO_HEIGHT 384
#define VIDEO_PIXELS VIDEO_WIDTH* VIDEO_HEIGHT

static uint8_t* frame_buf;
static struct retro_log_callback logging;
static retro_log_printf_t log_cb;
static bool use_audio_cb;
static float last_aspect;
static float last_sample_rate;
char retro_base_directory[4096];
char retro_game_path[4096];

static void fallback_log(enum retro_log_level level, const char* fmt, ...) {}

static retro_environment_t environ_cb;

void retro_init(void) {}

void retro_deinit(void) {}

unsigned retro_api_version(void) { return RETRO_API_VERSION; }

void retro_set_controller_port_device(unsigned port, unsigned device) {}

void retro_get_system_info(struct retro_system_info* info) {}

static retro_video_refresh_t video_cb;
static retro_audio_sample_t audio_cb;
static retro_audio_sample_batch_t audio_batch_cb;
static retro_input_poll_t input_poll_cb;
static retro_input_state_t input_state_cb;

void retro_get_system_av_info(struct retro_system_av_info* info) {}

void retro_set_environment(retro_environment_t cb) {}

void retro_set_audio_sample(retro_audio_sample_t cb) {}

void retro_set_audio_sample_batch(retro_audio_sample_batch_t cb) {}

void retro_set_input_poll(retro_input_poll_t cb) {}

void retro_set_input_state(retro_input_state_t cb) {}

void retro_set_video_refresh(retro_video_refresh_t cb) {}

static unsigned phase;

void retro_reset(void) {}

static void update_input(void) {}

static void check_variables(void) {}

static void audio_callback(void) {}

static void audio_set_state(bool enable) {}

void retro_run(void) {}

bool retro_load_game(const struct retro_game_info* info) { return true; }

void retro_unload_game(void) {}

unsigned retro_get_region(void) { return RETRO_REGION_NTSC; }

bool retro_load_game_special(unsigned type, const struct retro_game_info* info,
                             size_t num) {
  return false;
}

size_t retro_serialize_size(void) { return 0; }

bool retro_serialize(void* data_, size_t size) { return false; }

bool retro_unserialize(const void* data_, size_t size) { return false; }

void* retro_get_memory_data(unsigned id) { return NULL; }

size_t retro_get_memory_size(unsigned id) { return 0; }

void retro_cheat_reset(void) {}

void retro_cheat_set(unsigned index, bool enabled, const char* code) {}
