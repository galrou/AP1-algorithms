//
// Created by gal on 06/01/2020.
//

#ifndef EX4_FILECACHEMANAGER_H
#define EX4_FILECACHEMANAGER_H

#include <list>
#include <unordered_map>
#include <fstream>
#include <string>
#include <iostream>
#include "CacheManager.h"
using namespace std;
template<class T>
class FileCacheManager: public CacheManager<string,T> {
private:
    //how many items can exist at once in memory
    const int SIZE_LIMIT;
    //list of objects-the most recently used will be first and the lru will be last
    list<pair<string, T>> objects;
    //HOLDS THE GIVEN KEY AND THE VALUE IS A POINTER TO THE POSITION OF THE VALUE IN THE LIST
    unordered_map<string, typename list<pair<string, T>>::iterator> mapper;
public:
    FileCacheManager(int capacity) : SIZE_LIMIT(capacity) {};
    /**
    * is there a solution saved in the cache
    */
    virtual bool isExists(string problem){
        //if its in the map-then its in the cache -return true
        if (!(mapper.find(problem) == mapper.end())) {
            return true;
        }
        return false;
    };
    /**
     * returns a solution given a problem
     * @return
     */
    virtual string get(string key){
        //string filename = T::class_name;
        string filename="";
        filename.append(key);
        //if the object  exists in map
        if (!(mapper.find(key) == mapper.end())) {
            auto it=mapper[key];;
            objects.erase(it);
            objects.push_front({key, it->second});
            return (*it).second;
        }
            //the object in the filesystem but not in the map
        else {
            //remove the lru from the list
            auto it = objects.back();
            auto lrukey = (it).first;
            auto obj2 = (it).second;
            int size= objects.size();

            T mru=readFromFile(obj2,filename);
            objects.push_front({key,mru});
            mapper[key]=objects.begin();
            if (size>= SIZE_LIMIT){
                objects.pop_back();//O(1)
                mapper.erase(lrukey);
            }

            return mru;
        }


    };
    /**
     * save the problem in the cache-gets problem-key and solution-obj
     * and inserts them to the cache
     * @param p
     * @param s
     */
    virtual void insert(string key,T obj){
        //string fileName = T::class_name;
        string fileName="";
        fileName.append(key);

        //update in cache-move it to be the first in the list
        //if its in the map
        if (!(mapper.find(key) == mapper.end())) {
            //if its in the map then its in the list-erease this element and hen ill push it to the front
            auto it = mapper[key];//the iterator
            objects.erase(it);//delete the
            //push the item to the front of the list
            objects.push_front({key, obj});
            //update it in the map
            mapper[key] = objects.begin();
        }

            //if its not in the map-add it to the map and to the objects
        else {
            //push the item to the front of the list
            objects.push_front({key, obj});
            //add it to the map
            mapper[key] = objects.begin();
        }
        int size=objects.size();
        if (size> SIZE_LIMIT) {
            //deletes the lru from the list and the map
            auto it = objects.back();
            objects.pop_back();
            mapper.erase(it.first);
        }
        //update it in the file system
        ofstream out;
        out.open(fileName,ofstream::binary|ofstream::trunc);
        if(out.is_open()){
            out.write((char*)(&obj),sizeof(obj));
            out.close();
        }
        else{
            throw "an error in cache file manager";
        }
    };
    T readFromFile(T obj,string filename){
        ifstream inputFile;
        inputFile.open(filename, ifstream::binary);
        if (inputFile.is_open()) {
            inputFile.read((char *) &obj, sizeof(obj));
            //   ((obj)).print();
            inputFile.close();
        } else {
            throw "an error";
        }
        return  obj;
    };
    virtual CacheManager<string,T>* getClone(){
       //cout<<"befor cm"<<endl;
        return new FileCacheManager<string>(5);
    }
};

#endif //EX4_FILECACHEMANAGER_H