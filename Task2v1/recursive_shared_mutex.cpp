#include "recursive_shared_mutex.h"

void recursive_shared_mutex::do_exclusive_lock(unique_lock &lock)
{
    while (someone_has_exclusive_lock())
    {
        m_exclusive_release.wait(lock);
    }

    take_exclusive_lock();

    while (number_of_readers() > 0)
    {
        m_shared_release.wait(lock);
    }
}

bool recursive_shared_mutex::do_exclusive_trylock(unique_lock &lock)
{
    if (lock.owns_lock() && no_one_has_any_lock())
    {
        take_exclusive_lock();
        return true;
    }
    return false;
}

void recursive_shared_mutex::do_lock_shared(unique_lock& lock)
{
    while (someone_has_exclusive_lock() || maximal_number_of_readers_reached())
    {
        m_exclusive_release.wait(lock);
    }
    increment_readers();
}

bool recursive_shared_mutex::do_try_lock_shared(unique_lock& lock)
{
    if (lock.owns_lock() && !someone_has_exclusive_lock() && !maximal_number_of_readers_reached())
    {
        increment_readers();
        return true;
    }
    return false;
}

void recursive_shared_mutex::do_unlock_shared()
{
    decrement_readers();

    if (someone_has_exclusive_lock())
    {
        if (number_of_readers() == 0)
        {
            m_shared_release.notify_one();
        }
    }
    else
    {
        if (number_of_readers() == m_num_readers - 1)
            m_exclusive_release.notify_one();
    }
}

void recursive_shared_mutex::take_exclusive_lock()
{
    m_state |= m_write_entered;
}

bool recursive_shared_mutex::someone_has_exclusive_lock() const
{
    return (m_state & m_write_entered) != 0;
}

bool recursive_shared_mutex::no_one_has_any_lock() const
{
    return m_state != 0;
}

unsigned recursive_shared_mutex::number_of_readers() const
{
    return m_state & m_num_readers;
}

bool recursive_shared_mutex::maximal_number_of_readers_reached() const
{
    return number_of_readers() == m_num_readers;
}

void recursive_shared_mutex::clear_lock_status()
{
    m_state = 0;
}

void recursive_shared_mutex::increment_readers()
{
    unsigned num_readers = number_of_readers() + 1;
    m_state &= ~m_num_readers;
    m_state |= num_readers;
}

void recursive_shared_mutex::decrement_readers()
{
    unsigned num_readers = number_of_readers() - 1;
    m_state &= ~m_num_readers;
    m_state |= num_readers;
}

///////////////////////////////////////////////////////////////////////////

void recursive_shared_mutex::lock() {
    std::unique_lock<std::recursive_mutex> lock(m_mutex);
    if (m_write_recurses == 0)
    {
        do_exclusive_lock(lock);
    }
    else
    {
        if (m_write_thread == std::this_thread::get_id())
        {
            if (m_write_recurses == std::numeric_limits<decltype(m_write_recurses)>::max())
            {
                throw std::system_error(EOVERFLOW, std::system_category(), "Recursions overflow!");
            }
        }
        else
        {
            do_exclusive_lock(lock);//Another thread lock
            assert(m_write_recurses == 0);
        }
    }
    m_write_recurses++;
    m_write_thread = std::this_thread::get_id();
}

bool recursive_shared_mutex::try_lock()
{
    std::unique_lock<std::recursive_mutex> lock(m_mutex, std::try_to_lock);
    if ((lock.owns_lock() && m_write_recurses > 0 && m_write_thread == std::this_thread::get_id()) || do_exclusive_trylock(lock))
    {
        m_write_recurses++;
        m_write_thread = std::this_thread::get_id();
        return true;
    }
    return false;
}

void recursive_shared_mutex::unlock()
{
    bool notify_them = false;
    {
        std::lock_guard<std::recursive_mutex> lg(m_mutex);
        if (m_write_recurses == 0)
        {
            throw std::system_error(ENOLCK, std::system_category(), "Unlocking an unlocked mutex!");
        }
        m_write_recurses--;
        if (m_write_recurses == 0)
        {
            clear_lock_status();// Releasing an exclusive lock, no one else has a lock.
            notify_them = true;
        }
    }
    if (notify_them)
    {
        m_exclusive_release.notify_all();
    }
}

void recursive_shared_mutex::lock_shared()
{
    std::unique_lock<std::recursive_mutex> lock(m_mutex);
    do_lock_shared(lock);
}

bool recursive_shared_mutex::try_lock_shared()
{
    std::unique_lock<std::recursive_mutex> lock(m_mutex, std::try_to_lock);
    return do_try_lock_shared(lock);
}

void recursive_shared_mutex::unlock_shared()
{
    std::lock_guard<std::recursive_mutex> lock(m_mutex);
    return do_unlock_shared();
}

int recursive_shared_mutex::num_write_locks()
{
    std::lock_guard<std::recursive_mutex> lock(m_mutex);
    return m_write_recurses;
}

bool recursive_shared_mutex::is_locked_by_me()
{
    std::lock_guard<std::recursive_mutex> lock(m_mutex);
    return m_write_recurses > 0 && m_write_thread == std::this_thread::get_id();
}
