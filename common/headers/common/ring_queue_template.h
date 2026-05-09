#include <common/typedefs.h>
#include <common/errors.h>
#include <assert.h>

#ifndef TYPE
#define TYPE u32
#endif


#ifndef CONCATS

#define CONCAT2(a, b) a##b
#define CONCAT(a, b) CONCAT2(a, b)

#define CONCAT3_2(a, b, c) a##b##c
#define CONCAT3(a, b, c) CONCAT3_2(a, b, c)

#define RING_QUEUE CONCAT(RingQueue_, TYPE)
#define METHOD_RING_QUEUE(a) CONCAT3(RingQueue_, TYPE, _##a)

#endif

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
	RING_QUEUE* queue,
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
	RING_QUEUE* queue,
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
