#pragma once

#include <memory>
#include <mutex>
#include <unordered_set>
#include <queue>

#include "knet/KNetTypes.h"

namespace knet {

class EventManager;
class TimerManager;

class Timer : public std::enable_shared_from_this<Timer>
{
    friend class TimerManager;
public:
    Timer() = default;
    ~Timer() = default;
    Timer(const Timer&) = delete;
    Timer& operator=(const Timer&) = delete;
    Timer(Timer&&) = delete;
    Timer& operator=(Timer&&) = delete;

private:
    void                Call();
    void                SetCallback(Callback cb);
    void                SetEventTimer(EventTimerPtr et);
private:
    Callback            m_sync_cb;
    EventTimerPtr       m_et;
};

class TimerManager
{
public:
    TimerManager(EventManager& event_manager);
    ~TimerManager();
    TimerManager(const TimerManager&) = delete;
    TimerManager& operator=(const TimerManager&) = delete;
    TimerManager(TimerManager&&) = delete;
    TimerManager& operator=(TimerManager&&) = delete;

    bool                Init();
    void                Tick(DiffTime diff);
    TimerHdl            AddTimer(Callback sync_cb, Duration d);
    void                CancelTimer(TimerHdl hdl);

private:
    void                CB_Event(TimerHdl hdl);
private:
    EventManager&                m_event_manager;
    std::unordered_set<TimerPtr> m_timers;
    std::mutex                   m_mtx;
    std::queue<TimerHdl>         m_timeout_timers;
};

} // knet
