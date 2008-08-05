/*
 * Copyright (C) 2005 Milan Svoboda <milan.svoboda@centrum.cz>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General
 * Public License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#ifndef LOG_H
#define LOG_H

// ------------------- Logs -------------------------

#include <syslog.h>

#ifndef DEBUG
#define DEBUG_(fmt,...)
#else
#include <stdio.h>
#define DEBUG_(fmt,...) \
        fprintf(stderr, "DEBUG %s %d: " fmt "\n", __PRETTY_FUNCTION__, __LINE__, ## __VA_ARGS__);
#endif

#define WARN_(fmt,...)				\
	syslog(LOG_WARNING, "WARN %s %d: " fmt, __PRETTY_FUNCTION__, __LINE__, ## __VA_ARGS__);

#define ERR_(fmt,...)				\
	syslog(LOG_ERR, "ERR %s %d: " fmt, __PRETTY_FUNCTION__, __LINE__, ## __VA_ARGS__);

#define CRIT_(fmt,...)				\
	syslog(LOG_CRIT, "CRIT: %s %d: " fmt, __PRETTY_FUNCTION__, __LINE__, ## __VA_ARGS__);
	
#define INFO_(fmt,...)				\
	syslog(LOG_INFO, "INFO: %s %d: " fmt, __PRETTY_FUNCTION__, __LINE__, ## __VA_ARGS__);

// ------------------- Statistics -------------------------

#ifdef DEBUG

#include <pthread.h>

#define STAT_GETATTR			1
#define STAT_UNLINK			2
#define STAT_RENAME			3
#define STAT_TRUNCATE			4
#define STAT_OPEN			5
#define STAT_RELEASE			6
#define STAT_READ			7
#define STAT_WRITE			8
#define STAT_DECOMPRESS			9
#define STAT_BACKGROUND_COMPRESS	10
#define STAT_BACKGROUND_COMPRESS_QUEUE	11
#define STAT_DIRECT_OPEN_ALLOC		12
#define STAT_DIRECT_READ		13
#define STAT_DIRECT_WRITE		14
#define STAT_FALLBACK			15
#define STAT_COMPRESS			16

#define STAT_MAX			16

#define STAT_(index)	statistics[index-1].count++;

typedef struct
{
	unsigned int count;
	const char *name;
} statistic_t;

// The statistics array is not protected with mutex, this is only
// statistics, it's nothing too important...
//
extern volatile statistic_t statistics[];

extern void statistics_print(void);

#else

#define STAT_(index)

static inline void statistics_print(void) {}

#endif

#endif