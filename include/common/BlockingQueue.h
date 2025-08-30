// Arquivo: include/common/BlockingQueue.h

#ifndef BLOCKING_QUEUE_H
#define BLOCKING_QUEUE_H

#include <queue>
#include <mutex>
#include <condition_variable>

template <typename T>
class BlockingQueue {
private:
    std::queue<T> m_queue;
    std::mutex m_mutex;
    std::condition_variable m_cond_var;
    bool m_done = false;

public:
    // Adiciona um item à fila e notifica uma thread que está esperando
    void push(T item) {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_queue.push(item);
        lock.unlock();
        m_cond_var.notify_one();
    }

    // Pega um item da fila. Se estiver vazia, espera até um item chegar.
    bool pop(T& item) {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_cond_var.wait(lock, [this] { return !m_queue.empty() || m_done; });

        if (m_queue.empty() && m_done) {
            return false; // Fila vazia e produtor terminou
        }

        item = m_queue.front();
        m_queue.pop();
        return true;
    }

    // Sinaliza que a produção de itens terminou
    void done() {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_done = true;
        lock.unlock();
        m_cond_var.notify_all(); // Acorda todas as threads esperando
    }
};

#endif // BLOCKING_QUEUE_H