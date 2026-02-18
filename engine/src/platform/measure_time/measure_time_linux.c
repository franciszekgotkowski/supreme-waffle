#include <engine/memory_pool.h>
#include <engine/platform/measure_time.h>

#include <assert.h>
#include <stdio.h>
#include <time.h>

extern PointerTable* GameMemory;

inline TimeStamp InitializeTimeStamp() {
	struct timespec spec;
	i32 errno = clock_gettime(CLOCK_REALTIME, &spec);
	assert(errno == 0);

	return (TimeStamp){
		.sec = spec.tv_sec,
		.nsec = spec.tv_nsec
	};
}

inline DoubleTimeStamp InitializeDoubleTimeStamp(){
	struct timespec spec;
	i32 errno = clock_gettime(CLOCK_REALTIME, &spec);
	assert(errno == 0);

	return (DoubleTimeStamp){
		.then = {
			.sec = spec.tv_sec,
			.nsec = spec.tv_nsec
		}
	};
}

inline void UpdateDoubleTimeStamp(DoubleTimeStamp *ptr) {
	assert(ptr);

	struct timespec spec;
	i32 errno = clock_gettime(CLOCK_REALTIME, &spec);
	assert(errno == 0);

	ptr->then = ptr->now;
	ptr->now = (TimeStamp) {
		.sec = spec.tv_sec,
		.nsec = spec.tv_nsec
	};

	return;
}

inline TimeStamp TimeSince(TimeStamp stamp) {
		struct timespec spec;
		i32 errno = clock_gettime(CLOCK_REALTIME, &spec);
		assert(errno == 0);

		return (TimeStamp) {
			.sec = spec.tv_sec - stamp.sec,
			.nsec = spec.tv_nsec - stamp.nsec
		};
}
inline TimeStamp PrintTimeSince(TimeStamp stamp) {
	TimeStamp diff = TimeSince(stamp);
	printf("Time elapsed: %llus %llums\n", (llu)diff.sec, (llu)diff.nsec);
	return diff;
}

inline i8 Smaller(TimeStamp a, TimeStamp b) {
	if (a.sec < b.sec) {
		return -1;
	} else if (a.sec > b.sec) {
		return 1;
	} else {
		if (a.nsec < b.nsec) {
			return -1;
		} else if (a.nsec > b.nsec) {
			return 1;
		} else {
			return 0;
		}
	}
}

inline void MatchFrametime(TimeStamp frameTime, TimeStamp lastStamp) {
	TimeStamp elapsed = TimeSince(lastStamp);

	if (Smaller(elapsed, frameTime) == 1) {
		printf("FRAMETIME MISSED!!!\tFRAME TOOK %llus %llums\n", (llu)elapsed.sec, (llu)elapsed.nsec);
		return;
	}

	struct timespec diff = {
		.tv_sec = frameTime.sec - elapsed.sec,
		.tv_nsec = frameTime.nsec - elapsed.nsec
	};
	struct timespec remaining;

	i32 errno = nanosleep(&diff, &remaining);
	assert(errno == 0);
}