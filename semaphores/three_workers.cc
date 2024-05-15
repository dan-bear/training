/**
 * There are three agents providing resources:
 * noWoodAgent provides stone and steel.
 * noStoneAgent provides steel and wood.
 * noSteelAgent provides stone and wood.
 * Each agent is a thread running in infinite loop
 * (see the functions below). 
 * - The agents sync over a single semaphore, once the
 *   semaphore is taken two resources are allocated and 
 *   the workers can use them.
 * - A worker need to get 2 resources to do its work.
 *   while the third resource is in abundance.
 *   - For example, the WoodWorker has wood and needs to
 *     get stone and steel from the agent.
 * - Once a worker complete its work it signals the agents' 
 *   semaphore and gets back waiting
 *   for more resources.
 * The problem is to complete the workers code such that
 * the work progresses and no dead-lock occurs.
 * (see code below for more details).
 */
class ThreeWorkers{
private:
    ///Given:
    Semaphore m_agentsSem{1};
    Semaphore m_woodSem{0};
    Semaphore m_stoneSem{0};
    Semaphore m_steelSem{0};
public:    
    ///A single thread runs the no-wood agent.
    static void sNoWoodAgent(){
        while(true){
            m_agentsSem.wait();
            m_stoneSem.signal();
            m_steelSem.signal();
        }
    }

    ///A single thread runs the no-stone agent.
    static void sNoStoneAgent(){   
        while(true){
            m_agentsSem.wait();
            m_woodSem.signal();
            m_steelSem.signal();
        }
    }

    ///A single thread runs the no-steel agent.
    static void sNoSteelAgent(){
        while(true){
            m_agentsSem.wait();
            m_stoneSem.signal();
            m_woodSem.signal();
        }
    }

    ///Complete the workers code, so no deadlock occurs and
    ///the work progresses.
    static void sSteelWorker(){
        while(true){
            ///Do something to get both the stoneSem and woodSem.
            ///(write your code here)
            sWork();
            m_agnetsSem.signal(); //Ask for more resources.
        }
    }

    static void sWoodWorker(){
        while(true){
            ///Do something to get both the stoneSem and steelSem.
            ///(write your code here).
            sWork();
            m_agnetsSem.signal(); //Ask for more resources.
        }
    }

    static void sStoneWorker(){
        while(true){
            ///Do something to get both the woodSem and steelSem.
            ///(write your code here)
            sWork();
            m_agnetsSem.signal(); //Ask for more resources.
        }
    }

    ///First solution - determine the semaphores-acquiring order such
    ///that it eliminates dead-locks.
    ///WoodWorker             StoneWorker             SteelWorker
    ///steelSem.wait();       steelSem.wait();        woodSem.wait();
    ///stoneSem.wait();       woodSem.wait();         stoneSem.wait();
    ///
    ///In order for a deadlock to occur, a waiting cycle needs to be
    ///formed. 
    ///Let's assume there is a cycle between the threads, let's start
    ///with the steelSem:
    ///case1: steelSem is held by the woodWorker.
    ///       wood worker waits for stoneSem.
    ///       stoneSem held by steelWorker.
    ///       It contradicts the cycle existance since
    ///       by holding the stoneSem, it means the
    ///       steelWorker already holds the woodSem.
    ///
    ///case2: steelSem is held by the StoneWorker
    ///       StoneWorker waits on woodSem.
    ///       woodSem is held by steelWorker
    ///       steelWorker waits on stoneSem.
    ///       stoneSem held by WoodWorker
    ///       It contradicts that fact that the WoodWorker cannot
    ///       hold the stoneSem since it does not hold the 
    ///       steelSem.

    ///How to generalize is to more than 3 resources? Let's have a look
    ///On 6 resources, the pattern can be generalized to any n.
    ///r0Worker    r1Worker    r2Worker    r3Worker    r4Worker    r5Worker
    ///r5.wait()   r5.wait()   r5.wait()   r5.wait()   r5.wait()   r0.wait()
    ///r4.wait()   r4.wait()   r4.wait()   r4.wait()   r0.wait()   r1.wait()
    ///r3.wait()   r3.wait()   r3.wait()   r0.wait()   r1.wait()   r2.wait()
    ///r2.wait()   r2.wait()   r0.wait()   r1.wait()   r2.wait()   r3.wait()
    ///r1.wait()   r0.wait()   r1.wait()   r2.wait()   r3.wait()   r4.wait()
private:
};






