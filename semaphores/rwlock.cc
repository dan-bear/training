///Assume the next semaphore interface
class Semaphore{
public:
    Sempahore(int count) : m_count(count) {}
    void wait() {/*does whatever semaphore lock does*/};
    void signal() {/*does whatever semaphore signal does*/};
private:
    int m_count{0};
};


/** Simplest rwlock but might cause starvation */
class StarvationRWLock{
public:
    void readLock(){
        m_readersMut.wait();
        if(m_readersCount == 0){
            m_roomIsEmpty.wait();
        }
        m_readersCount++;
        m_readersMut.signal();
    }
    
    void readSignal(){
        m_readersMut.wait();
        m_readersCount--;
        if(m_readersCount == 0){
            m_roomIsEmpty.signal();
        }
        m_readersMut.signal();
    }

    void writeLock(){
        m_roomIsEmpty.wait();
    }

    void writeSignal(){
        m_roomIsEmpty.signal();
    }
private:
    Semaphore m_roomIsEmpty{1};
    Semaphore m_readersMut{1};
    int m_readersCount{0};
};

/**
 * When a writer arrives, the existing readers can finish,
 * but no additional readers may enter.
 */
class NoStravationRWLock{
public:
    void readLock(){
       m_turnstile.wait();
       m_turnstile.signal();
      
       m_readersMut.wait();
        if(m_readersCount == 0){
            m_roomIsEmpty.wait();
        }
        m_readersCount++;
        m_readersMut.signal();
    }
    
    void readSignal(){
        m_readersMut.wait();
        m_readersCount--;
        if(m_readersCount == 0){
            m_roomIsEmpty.signal();
        }
        m_readersMut.signal();
    }

    void writeLock(){
        m_turnstile.wait();
        m_roomIsEmpty.wait();
    }

    void writeSignal(){
        m_roomIsEmpty.signal();
        m_turnstile.signal();
    }
private:
    Sempahore m_readersMut{1};
    Sempahore m_turnstile{1};
    Semaphore m_roomIsEmpty{1};
};


class FavorWritersRWLock{
public:
    void readWait(){
        m_readersTurnstile.wait();
        
        m_readersMut.wait();
        m_readersCount++;
        if(m_readersCount == 1){
            m_roomIsEmpty.wait();
        }
        m_readersMut.signal()
        
        m_readresTurnstile.signal();
    }

    void readSignal(){
        m_readersMut.wait();
        m_readersCount--;
        if(m_readersCount == 0){
            m_roomIsEmpty.signal();
        }
        m_readersMut.signal();
    }

    void writeWait(){
        m_writersMut.wait();
        m_writersCount++;
        if(m_writersCount == 1){
            m_readersTurnstile.wait();
        }
        m_writersMut.signal();

        m_roomIsEmpty.wait();
    }

    void writeSignal(){
        m_roomIsEmpty.signal();
        
        m_writersMut.wait();
        m_writersCount--;
        if(m_writersCount == 0){
            m_readersTurnstile.signal();
        }
        m_writersMut.signal();
    }

private:
    Sempahore m_readersTurnstile{1};
    Semphoare m_roomIsEmpty{1};
    Sempahore m_readersMut{1};
    Sempahore m_writerssMut{1};
    int m_readersCount{0};
    int m_writersCount{0};
};


/**
 * Generalize the concept of light switch
 */
class LightSwitch{
public:
    void wait(Semaphore* pSem){
        m_mut.wait();
        m_count++;
        if(m_count == 1){
            pSem->wait();
        }
        m_mut.signal();
    }

    void signal(Semaphore* pSem){
        m_mut.wait();
        m_count--;
        if(m_count == 0){
            pSem->signal();
        }
        m_mut.signal();
    }

private:
   int m_count{0};
   Sempahore m_mut{1};
};

class WritePrioritizeRWLockWithLightSwitch{
public:
    void readWait(){
        m_readersTurnstile.wait();
        m_readersLS.wait(&m_roomIsEmpty);
        m_readersTurnstile.signal();
    }

    void readSignal(){
        m_readersLS.signal(&m_roomIsEmpty);
    }

    void writeWait(){
        m_writersLS.wait(&m_readersTurnstile);
        m_roomIsEmpty.wait();
    }

    void writeSignal(){
        m_roomIsEmpty.signal();
        m_writersLS.signal(&m_readersTurnstile);
    }

private:
    Semaphore m_roomIsEmpty{1};
    Semaphore m_readtersTurnstile{1};
    LightSwitch m_readersLS;
    LightSwitch m_writersLS;
};



