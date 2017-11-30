#pragma once

#include <string>
#include <thread>
#include <chrono>
#include <atomic>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <unordered_map>

#include <rdkafkacpp.h>

#include "knet/KNetTypes.h"
#include "knet/detail/kafka/KafkaTypes.h"

namespace knet {

class SendMessage;

namespace detail {

struct ProducerConf
{
    std::string m_broker_list{};
};

struct ProducerCB 
{
    EventCBUPtr          m_event_cb{};
    DeliveryReportCBUPtr m_dr_cb{};
};

class Producer
{
public:
    Producer();
    ~Producer();
    Producer(const Producer&) = delete;
    Producer& operator=(const Producer&) = delete;
    Producer(Producer&&) = delete;
    Producer& operator=(Producer&&) = delete;

    bool Init(std::unique_ptr<ProducerConf> p_conf, std::unique_ptr<ProducerCB> client_cb);
    void Stop();
    void WaitThreadExit();
    void Flush();
    void SendTo(std::shared_ptr<SendMessage> send_msg);

private:
    void StartPollThread();
    void StartSendThread();
    void SendMessageInternal(const SendMessage& msg);
    ::RdKafka::Topic* FindOrCreate(const ServiceID& sid);

private:
    std::unique_ptr<ProducerConf>               m_p_conf;
    std::thread                                 m_poll_thread;  // poll�߳�
    std::thread                                 m_send_thread;  // �����߳�
    std::queue<std::shared_ptr<SendMessage>>    m_queue;
    std::mutex                                  m_mtx;
    std::condition_variable                     m_cond;
    std::atomic<bool>                           m_run;
    std::unique_ptr<::RdKafka::Producer>        m_producer;
    std::unique_ptr<ProducerCB>                 m_producer_cb;
    std::unordered_map<ServiceID, std::unique_ptr<::RdKafka::Topic>> m_topics;
};

} // detail

} // knet