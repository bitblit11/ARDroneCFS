/*==============================================================================
Copyright (c) 2015, Windhover Labs
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

* Neither the name of EIM nor the names of its
  contributors may be used to endorse or promote products derived from
  this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "common_types.h"

#define NB_CORNER_TRACKERS_WIDTH    5      /* number of trackers in width of current picture */
#define NB_CORNER_TRACKERS_HEIGHT   4      /* number of trackers in height of current picture */
#define NAVDATA_HEADER  0x55667788

#define DEFAULT_NB_TRACKERS_WIDTH    (NB_CORNER_TRACKERS_WIDTH+1)// + ARDRONE2LIB_NB_BLOCK_TRACKERS_WIDTH)
#define DEFAULT_NB_TRACKERS_HEIGHT   (NB_CORNER_TRACKERS_HEIGHT+1)// + ARDRONE2LIB_NB_BLOCK_TRACKERS_HEIGHT)

// Define constants for accelerometers handling
typedef enum
{
	ACC_X   = 0,
	ACC_Y   = 1,
	ACC_Z   = 2,
	NB_ACCS = 3
} def_acc_t;

typedef struct
{
  float 	x;
  float		y;
  float		z;
} velocities_t;

// Define constants for gyrometers handling
typedef enum
{
	GYRO_X    = 0,
	GYRO_Y    = 1,
	GYRO_Z    = 2,
	NB_GYROS  = 3
} def_gyro_t;

typedef struct
{
	int32 	x;
	int32 	y;
} screen_point_t;


typedef struct
{
	float	m11;
	float	m12;
	float	m13;
	float	m21;
	float	m22;
	float	m23;
	float	m31;
	float	m32;
	float	m33;
} matrix33_t;

typedef struct
{
	union
	{
		float v[3];
		struct
		{
			float x;
			float y;
			float z;
		};
	};
} vector31_t;


typedef union
{
	float	v[2];
	struct
	{
		float	x;
		float	y;
	};
} vector21_t;
