#pragma once

#include <engine/typedefs.h>

// universal type for point in time
typedef struct {
	u64 sec;
	u64 nsec;
} TimeStamp;

typedef struct {
	TimeStamp then;
	TimeStamp now;
} DoubleTimeStamp;

TimeStamp InitializeTimeStamp();

DoubleTimeStamp InitializeDoubleTimeStamp();

// Last .now is now .then and it gets new value for .now
void UpdateDoubleTimeStamp(DoubleTimeStamp* ptr);

// returns time since timestamp
TimeStamp TimeSince(TimeStamp stamp);
//same as TimeSince but also prints it
TimeStamp PrintTimeSince(TimeStamp stamp);

// will return -1 if a is earlier and 1 if b is earlier.
// If they are equal function will return 0
i8 Smaller(TimeStamp a, TimeStamp b);

// function will wait (using system time and busy wait) to match frametime.
// If time since lastStamp is bigger than frameTime function will just printf
// It will not update windows timestamp for frame
void MatchFrametime(TimeStamp frameTime, TimeStamp lastStamp);