
/************************************************************
 * cp: audio.c
 *
 * Licensed under GPLv2.
 * ABSOLUTELY NO WARRANTY!
 *
 * Copyright (C) eXerigumo Clanjor (哆啦比猫/兰威举).
 ************************************************************/

#include "audio.h"
#include "seq.h"
#include "music.h"
#include <stdio.h>
#include <pthread.h>
#include <assert.h>

u32 audio_bitrate = 8000;
u8  audio_playing = 0;

static FILE * dsp;
static u8 buf[AUDIO_BUF_SIZE];

static pthread_t thread_play;
static void play_thread();
inline static void fillbuf();




void audio_open()
{
	dsp = fopen("/dev/dsp", "w");
	assert(dsp && "Can not open /dev/dsp");

	seq_init();
	music_init();
}

void audio_close()
{
	audio_stop();
	fclose(dsp);
}

void audio_play()
{
	if (audio_playing) return;

	audio_playing = 1;
	pthread_create(&thread_play, PTHREAD_CREATE_JOINABLE,
			(void *)&play_thread, NULL);
}

void audio_stop()
{
	void * retval;

	if (audio_playing) {
		audio_playing = 0;
		pthread_join(thread_play, &retval);
	}
}

const u8 * audio_get_buf()
{
	return (const u8 *)buf;
}




static void play_thread()
{
	float time_start = ticks();
	u32   played     = 0;

	while (audio_playing) {
		fillbuf();
		fwrite(buf, sizeof(buf), 1, dsp);
		fflush(dsp);
		time_adjust(time_start + 1000.0f*(++played) *
				AUDIO_BUF_SIZE / audio_bitrate);
	}
}

inline static void fillbuf()
{
	float s = 1000.0f / audio_bitrate;
	float t = ticks();
	int i;
	for (i=0; i<AUDIO_BUF_SIZE; i++)
		buf[i] = (u8)lerp(seq_mix_all(t + s*i), -1, 1, 0, 0xFF);
}

