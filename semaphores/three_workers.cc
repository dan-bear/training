/**
 * There are three agents providing resources:
 * noWoodAgent provides stone and steel.
 * noStoneAgent provides steel and wood.
 * noSteelAgent provides stone and wood.
 * Each agent is a thread running in an infinite loop
 * (see the functions below). 
 * - The agents sync over a single semaphore, once the
 *   semaphore is taken two resources are allocated and 
 *   the workers can use them.
 * - A worker needs to get 2 resources to do its work and
 *   the third resource is in abundance.
 *   - For example, the WoodWorker has wood and needs to
 *     get stone and steel from the agents.
 * - Once a worker completes its work it signals the agents' 
 *   semaphore and gets back waiting for additional resources.
 * The problem is to complete the workers code such that
 * the workers progress and no dead-lock occurs.
 * (see code below for more details).
 */
class ThreeWorkers{
private:
    ///Given:
    static Semaphore s_gentsSem{1};
    static Semaphore s_woodSem{0};
    static Semaphore s_stoneSem{0};
    static Semaphore s_steelSem{0};
public:    
    ///A single thread runs the no-wood agent.
    static void sNoWoodAgent(){
        while(true){
            s_agentsSem.wait();
            s_stoneSem.signal();
            s_steelSem.signal();
        }
    }

    ///A single thread runs the no-stone agent.
    static void sNoStoneAgent(){   
        while(true){
            s_agentsSem.wait();
            s_woodSem.signal();
            s_steelSem.signal();
        }
    }

    ///A single thread runs the no-steel agent.
    static void sNoSteelAgent(){
        while(true){
            s_agentsSem.wait();
            s_stoneSem.signal();
            s_woodSem.signal();
        }
    }

    ///Complete the workers code, so no deadlock occurs and
    ///the work progresses.
    static void sSteelWorker(){
        while(true){
            ///Do something to get both the stoneSem and woodSem.
            ///(write your code here)
            sWork();
            s_agnetsSem.signal(); //Ask for more resources.
        }
    }

    static void sWoodWorker(){
        while(true){
            ///Do something to get both the stoneSem and steelSem.
            ///(write your code here).
            sWork();
            s_agnetsSem.signal(); //Ask for more resources.
        }
    }

    static void sStoneWorker(){
        while(true){
            ///Do something to get both the woodSem and steelSem.
            ///(write your code here)
            sWork();
            s_agnetsSem.signal(); //Ask for more resources.
        }
    }

    ///First solution - determine the semaphores-acquirment order such
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
    ///
    ///How to generalize it to more than 3 resources? Let's have a look
    ///on 6 resources, the pattern can be generalized to any n.
    ///r0Worker    r1Worker    r2Worker    r3Worker    r4Worker    r5Worker
    ///r5.wait()   r5.wait()   r5.wait()   r5.wait()   r5.wait()   r0.wait()
    ///r4.wait()   r4.wait()   r4.wait()   r4.wait()   r0.wait()   r1.wait()
    ///r3.wait()   r3.wait()   r3.wait()   r0.wait()   r1.wait()   r2.wait()
    ///r2.wait()   r2.wait()   r0.wait()   r1.wait()   r2.wait()   r3.wait()
    ///r1.wait()   r0.wait()   r1.wait()   r2.wait()   r3.wait()   r4.wait()



    ///Another solutuion uses intermidiate threads, called pushers.
private:
    ///Additional semaphores.
    static Semaphore s_countMut{1};
    static Semaphore s_stoneWorkerSem{0};
    static Semaphore s_woodWorkerSem{0};
    static Semaphore s_steelWorkerSem{0};
    ///Counters
    static int s_woodCount{0};
    static int s_stoneCount{0};
    static int s_steelCount{0};

public:
    ///Each pushed is ran by a thread. There are three pushers,
    ///corresponding to each resource.
    static void sWoodPusher(){
        while(true){
            s_woodSem.wait();
            ///Oh yeah, the agent gave me some wood.
            s_countMut.wait();
            if(s_steelCount == 1){
                ///cool, let the stoneWorker work.
                s_steelCount = 0;
                s_stoneWorkerSem.signal();
            }else if(s_stoneCount == 1){
                ///nice, let the steelWorker work.
                s_stoneCount = 0;
                s_steelWorkerSem.signal();
            }else{
                ///dang! no body can use the wood now.
                s_woodCount = 1;
            }
            s_countMut.signal();
            ///Note: don't signale the agents (woodSem),
            ///      that's deligatedto the workers!.
        }
    }

    ///Note the sStonePusher and sSteelPusher are symmetric, so 
    ///their code is not re-written here.

    static void sStonePusher(){/* .. */}

    static void sSteelPusher(){/* .. */}

    ///Now for the workers.
    static void sWoodWorker2(){
        while(true){
            ///Wait to be pushed by the pushers!
            s_woodWorkerSem.wait();
            sWork();
            ///Tell the agnets to work!
            s_agentSem.signal();
        }
    }

    ///The only different line between the workers is the
    ///semaphore they are waiting on.
    static void sSteelWorker2(){/*... s_steelWorkerSem.wait(); ...*/}

    static void sStoneWorker2(){/*... s_stoneWorkerSem.wait(); ...*/}

private:
};






