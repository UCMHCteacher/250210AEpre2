#include"BootSequence.hpp"
#include"BootSequenceList.hpp"
#include"ThreadPool.hpp"





void 
BootSequence() {
    ThreadPool bootTaskPool(8);
    bootTaskPool.enqueue_void(RTVarRegister);
    ; // TODO: Boot tasks
}