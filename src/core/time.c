
/************************************************************
 * cp: time.c
 *
 * Licensed under GPLv2.
 * ABSOLUTELY NO WARRANTY!
 *
 * Copyright (C) eXerigumo Clanjor (哆啦比猫/兰威举).
 ************************************************************/

#include "time.h"
#include <time.h>

static float time_begin;
static float elapsed();




float ticks()
{
	return elapsed() - time_begin;
}

void time_adjust(float time_should_be)
{
	time_begin += ticks() - time_should_be;
}




static float elapsed()
{
	struct timespec tp;
	clock_gettime(CLOCK_MONOTONIC, &tp);
	return tp.tv_sec * 1e3f + tp.tv_nsec / 1e6f;
}

