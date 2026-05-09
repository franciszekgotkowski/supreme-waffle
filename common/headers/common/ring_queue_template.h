#include <common/typedefs.h>
#include <common/errors.h>
#include <assert.h>
// #include "typedefs.h"
// #include "errors.h"

#ifndef TYPE
#define TYPE u32
#endif

#define CONCAT(a, b) a##b
#define RING_QUEUE RingQueue_##TYPE
#define METHOD_RING_QUEUE(a) RingQueue_##TYPE##_##a

typedef struct {
	u32 maxCapacity;			// maximum amount of elements that can be stored
	u32 currentAmountOfElements;					// amount of elements currently inside
	u32 firstElementOffset;
	TYPE* ptr;
} CONCAT(RingQueue_, TYPE);

// Function initialized struct for ring queue.
// ptr has to point to memory region that will be managed by queue
RING_QUEUE METHOD_RING_QUEUE(Initialize)(
	u32 maxCapacity,
	void* ptr
);

// Can return errors:
// 	- OUT_OF_MEMORY		if there is no more space to put new variable in queue
// 	- OK
Error METHOD_RING_QUEUE(Enqueue)(
	TYPE data,
	RING_QUEUE* queue
);

// Can return errors:
// 	- EMPTY				if there is nothing inside queue
// 	- OK
TYPE METHOD_RING_QUEUE(Dequeue)(
	Error* err
);

#ifdef RING_QUEUE_IMPLEMENTATION

RING_QUEUE METHOD_RING_QUEUE(Initialize)(
	u32 maxCapacity,
	void* ptr
) {
	assert(ptr);

	RING_QUEUE queue = {
		.maxCapacity = maxCapacity,
		.currentAmountOfElements = 0,
		.firstElementOffset = 0,
		.ptr = ptr
	};

	return queue;
}

Error METHOD_RING_QUEUE(Enqueue)(
	TYPE data,
	RING_QUEUE* queue
) {
	assert(queue);

	if ( queue->currentAmountOfElements >= queue->maxCapacity ) {
		return OUT_OF_MEMORY;
	}

	u32 lastElementOffset = (queue->firstElementOffset + queue->currentAmountOfElements)%queue->maxCapacity;
	queue->ptr[lastElementOffset] = data;
	queue->currentAmountOfElements += 1;

	assert(queue->currentAmountOfElements <= queue->firstElementOffset);

	return OK;
}


TYPE METHOD_RING_QUEUE(Dequeue)(
	Error* err
) {
	assert(err);
	assert(queue->currentAmountOfElements <= queue->firstElementOffset);

	if (queue->currentAmountOfElements == 0) {
		*err = EMPTY;
		return (TYPE){};
	}

	TYPE value = queue->firstElementOffset;
	queue->currentAmountOfElements -= 1;
	queue->firstElementOffset = (queue->firstElementOffset + 1) % queue->maxCapacity;
	*err = OK;
	return value;
}

#endif

#undef TYPE
