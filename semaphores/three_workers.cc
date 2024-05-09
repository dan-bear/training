///Stone producer:
while true:
    stoneFormed.signal();    
    stoneIsNeeded.wait();
    
///Wood producer:
while true:
    woodFormed.signal();
    woodIsNeeded.wait();

///Metal producer:
while true:
    metalFormed.signal();
    metalIsNeeded.wait();


///Wood and Metal consumer
while true:
    woodFormed.wait();
    countsLock.wait();
    if(metalCount == 0){
        woodCount = 1;
        woodFromed.signal();
        countsLock.signal();
        metalFormed.wait();
        woodFormed.wait();
    }else if(stoneCount == 1){
        woodCount == 1;
        woodFormed.signal();
        stoneFormed.signal();
        countsLock.signal();
    }else{
        metalCount = 0;
        countsLock.signal();  
    }
    
    useWoodAndMetal();
    woodIsNeeded.signal();
    metalIsNeeded.signal();
///Stone and Metal consumer


///Wood and Stone consumer








