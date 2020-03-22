#pragma once
#include "kworker.h"
#include <vector>
#include <thread>

namespace knet {

class async_worker : public workable {
public:
    explicit async_worker(conn_factory_builder& cfb);
    ~async_worker() override;

    void add_work(rawsocket_t rs) override;

    virtual bool start(size_t thread_num);
    virtual void stop();

protected:
    virtual worker* create_worker(conn_factory& cf)
    {
        return new worker(cf);
    }

private:
    struct info {
        bool r = true;
        connid_gener gener;
        async_worker* aw = nullptr;
        void* q = nullptr;
        std::thread* t = nullptr;
    };
    static void worker_thread(info* i);

private:
    conn_factory_builder& _cfb;
    std::vector<info> _infos;
    size_t _index = 0;
};

} // namespace knet