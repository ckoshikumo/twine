#ifndef INCLUDE_TWINE_H
#define INCLUDE_TWINE_H

typedef SDL_Thread twn_thread_s;
typedef SDL_Mutex twn_mutex_s;
typedef SDL_RWLock twn_lock_s;
typedef SDL_AtomicInt twn_atomic_s;
typedef SDL_Condition twn_cond_s;

#define twn_mutex_lock SDL_LockMutex
#define twn_mutex_release SDL_UnlockMutex
#define twn_mutex_destroy SDL_DestroyMutex

#define twn_atomic_set SDL_SetAtomicInt
#define twn_atomic_get SDL_GetAtomicInt
#define twn_atomic_add SDL_AddAtomicInt
#define twn_atomic_inc(a) SDL_AddAtomicInt(a, 1)
#define twn_atomic_dec(a) SDL_AddAtomicInt(a, -1)
#define twn_atomic_decref(a) (SDL_AddAtomicInt(a, -1) == 1)

#define twn_lock_read SDL_LockRWLockForReading
#define twn_lock_write SDL_LockRWLockForWriting
#define twn_lock_release SDL_UnlockRWLock
#define twn_lock_destroy SDL_DestroyRWLock

#define twn_thread_create SDL_CreateThread
#define twn_thread_wait SDL_WaitThread

#define twn_cond_wait SDL_WaitCondition
#define twn_cond_signal SDL_SignalCondition
#define twn_cond_broadcast SDL_BroadcastCondition
#define twn_cond_destroy SDL_DestroyCondition

#define twn_with_mutex(mut_, block_)                                           \
	do {                                                                       \
		twn_mutex_lock(mut_);                                                  \
		block_;                                                                \
		twn_mutex_release(mut_);                                               \
	} while (0)

#define twn_with_lock_read(lock_, block_)                                      \
	do {                                                                       \
		twn_lock_read(lock_);                                                  \
		block_;                                                                \
		twn_lock_release(lock_);                                               \
	} while (0)

#define twn_with_lock_write(lock_, block_)                                     \
	do {                                                                       \
		twn_lock_write(lock_);                                                 \
		block_;                                                                \
		twn_lock_release(lock_);                                               \
	} while (0)

static inline twn_mutex_s *twn_mutex_create(void) {
	twn_mutex_s *mutex = SDL_CreateMutex();
	guard_exit(mutex, "SDL CreateMutex failed: %s", SDL_GetError());
	return mutex;
}

static inline twn_lock_s *twn_lock_create(void) {
	twn_lock_s *lock = SDL_CreateRWLock();
	guard_exit(lock, "SDL CreateRWLock failed: %s", SDL_GetError());
	return lock;
}

static inline twn_cond_s *twn_condition_create(void) {
	twn_cond_s *condition = SDL_CreateCondition();
	guard_exit(condition, "SDL CreateCondition failed: %s", SDL_GetError());
	return condition;
}

#endif // INCLUDE_TWINE_H
