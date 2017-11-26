#pragma once

#include <memory>
#include <mutex>
#include <queue>

#include "knet/KNetTypes.h"
#include "knet/kafka/Callback.h"

namespace knet {

class UniformNetwork;

namespace detail {

class AsyncReceivedMsgCB : public ConsumerReceiveMessageCB
{
public:
    AsyncReceivedMsgCB(UniformNetwork& un);
    virtual ~AsyncReceivedMsgCB();

    virtual void onError(int32_t err_no, const std::string& err_str) override;
    virtual void onReceived(const void* p, size_t p_len, const void* key, size_t key_len) override;

private:
    UniformNetwork& m_un;
};

} // detail

} // knet
