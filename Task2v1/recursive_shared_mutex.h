#ifndef RECURSIVE_SHARED_MUTEX_H
#define RECURSIVE_SHARED_MUTEX_H

#include <mutex>
#include <condition_variable>
#include <thread>
#include <cassert>

class recursive_shared_mutex
{
public:
    recursive_shared_mutex() = default;
    ~recursive_shared_mutex() = default;

    //Disable Copy
    recursive_shared_mutex(const recursive_shared_mutex&) = delete;
    recursive_shared_mutex& operator = (const recursive_shared_mutex&) = delete;

    void lock();
    bool try_lock();
    void unlock();
    void lock_shared();
    bool try_lock_shared();
    void unlock_shared();

    int num_write_locks();
    bool is_locked_by_me();

private:
    using unique_lock = std::unique_lock < std::recursive_mutex >;
    using scoped_lock = std::lock_guard < std::recursive_mutex >;

    std::recursive_mutex m_mutex;
    std::condition_variable_any m_exclusive_release;
    std::condition_variable_any m_shared_release;
    unsigned m_state = 0;

    void do_exclusive_lock(unique_lock& lock);
    bool do_exclusive_trylock(unique_lock& lock);
    void do_lock_shared(unique_lock& lock);
    bool do_try_lock_shared(unique_lock& lock);
    void do_unlock_shared();

    void take_exclusive_lock();
    bool someone_has_exclusive_lock() const;
    bool no_one_has_any_lock() const;
    unsigned number_of_readers() const;
    bool maximal_number_of_readers_reached() const;
    void clear_lock_status();
    void increment_readers();
    void decrement_readers();

    static const unsigned m_write_entered = 1U << (sizeof(unsigned)*CHAR_BIT - 1);
    static const unsigned m_num_readers = ~m_write_entered;

    std::thread::id m_write_thread;
    int m_write_recurses = 0;
};

#endif // RECURSIVE_SHARED_MUTEX_H
