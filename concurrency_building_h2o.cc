/**
 * https://leetcode.com/problems/building-h2o/
 */
//#include <semaphore>
//using namespace std;
class H2O {
public:
    H2O() {
        
    }

    void hydrogen(function<void()> releaseHydrogen) {
        m_countMut.acquire();
        if(m_hCount >= 1 && m_oCount >= 1){
            m_turnstile.acquire();
            m_hCount -= 1;
            m_oCount -= 1;
            m_hQueue.release();
            m_oQueue.release();
            m_countMut.release();
        }else{
            m_hCount += 1;
            m_countMut.release();
            m_hQueue.acquire();
        }
    
        // releaseHydrogen() outputs "H". Do not change or remove this line.
        releaseHydrogen();

        m_creationMut.acquire();
        if(m_hPassed == 1 && m_oPassed == 1){
            m_hPassed = 0;
            m_oPassed= 0;
            m_turnstile.release();
        }else{
            m_hPassed += 1;
        }
        m_creationMut.release();
    }

    void oxygen(function<void()> releaseOxygen) {
        m_countMut.acquire();
        if(m_hCount >= 2){
            m_turnstile.acquire();
            m_hCount -= 2;
            m_hQueue.release();
            m_hQueue.release();
            m_countMut.release();
        }else{
            m_oCount += 1;
            m_countMut.release();
            m_oQueue.acquire();
        }
        
        // releaseOxygen() outputs "O". Do not change or remove this line.
        releaseOxygen();

        m_creationMut.acquire();
        if(m_hPassed == 2){
            m_hPassed = 0;
            m_turnstile.release();
        }else{
            m_oPassed = 1;
        }
        m_creationMut.release();
    }
    
private:
    int m_hCount{0};
    int m_oCount{0};
    int m_hPassed{0};
    int m_oPassed{0};
    
    std::binary_semaphore m_countMut{1};
    std::binary_semaphore m_creationMut{1};
    std::binary_semaphore m_turnstile{1};
    std::binary_semaphore m_hQueue{0};
    std::binary_semaphore m_oQueue{0};
};
