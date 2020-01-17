//
// Created by gal on 06/01/2020.
//

#ifndef EX4_CACHEMANAGER_H
#define EX4_CACHEMANAGER_H

/**
 * a cacheManager interface
 */
template<typename Problem, typename Solution>
class CacheManager {
public:
    /**
     * is there a solution in the cache
     */
    virtual bool isExists(Problem p)=0;
    /**
     * returns a solution given a problem
     * @return
     */
    virtual Solution get(Problem p)=0;
    /**
     * save the problem in the cache
     * @param p
     * @param s
     */
    virtual void insert(Problem p,Solution s)=0;
    virtual CacheManager<Problem,Solution>* getClone()=0;

};


#endif //EX4_CACHEMANAGER_H